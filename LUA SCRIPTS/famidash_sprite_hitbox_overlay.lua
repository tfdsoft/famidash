-- famidash_sprite_hitbox_overlay.lua
--
-- SPRITE-ONLY hitbox viewer for FamiDash (Mesen2). Draws the hitboxes of all
-- active sprite objects (transparent white) plus the player collision boxes.
--
-- Dimensions come from the validated tables in the FamiDash editor/simulator
-- (Editor Test/SimulatorWindow.xaml.cs): identical to the ROM tables but with
-- the 0xFF "special" markers replaced by the objects' real sizes. Types with
-- zero size are triggers / decorations and are skipped. (The simulator's
-- non-flipped-pad +8px shift is not applied: the game's runtime realy
-- already positions pads correctly.)
--
-- For sprites + tiles combined, use famidash_hitbox_overlay.lua instead.
-- Drop into Mesen2 via Tools -> Lua Scripting -> Open Script.

local SHOW_PLAYER     = true
local SHOW_SPRITE_IDS = false

local COLOR_SPRITE  = 0x60FFFFFF   -- transparent white (0xAARRGGBB, 0=opaque)
local COLOR_PLAYER1 = 0xFFFFFF
local COLOR_PLAYER2 = 0xFF9000

-- RAM addresses (identical across all FamiDash ROM variants)
local A = {
    gameState  = 0x049C,
    player_x   = 0x043D,  -- u16[2], hi byte = screen pixel
    player_y   = 0x0441,  -- u16[2]
    player_mini= 0x044F,  -- u8[2]
    gamemode   = 0x007A,
    dual       = 0x0096,
    spr_type   = 0x051B,  -- u8[16]
    spr_realx  = 0x054B,  -- u8[16]
    spr_realy  = 0x055B,  -- u8[16]
    spr_active = 0x056B,  -- u8[16]
}
local STATE_GAME = 0x02
local GM_WAVE, GM_SNAKE = 6, 10
local CUBE_W, CUBE_H = { [0]=15, [1]=8 }, { [0]=15, [1]=7 }
local WAVE_W, WAVE_H = 8, 8

-- Sprite hitbox tables from the editor/simulator, indexed by type 0..255 (+1)
local SPR_H = {
    52, 52, 52, 52, 52, 18, 18, 16, 40, 40, 3, 18, 3, 3, 3, 16,
    14, 14, 14, 14, 36, 36, 36, 52, 52, 52, 16, 16, 16, 16, 16, 18,
    36, 36, 52, 52, 52, 3, 3, 18, 18, 18, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 18, 18, 18, 40, 40, 16, 16, 52, 18, 18, 48, 16,
    18, 18, 3, 3, 18, 18, 3, 3, 52, 16, 16, 18, 18, 18, 18, 52,
    52, 52, 52, 52, 52, 2, 16, 16, 16, 16, 52, 52, 52, 32, 8, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 18, 18, 18, 18, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 0, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 0, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 0, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 0, 0, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 31, 16, 16, 3, 3, 0,
}
local SPR_W = {
    16, 16, 16, 16, 16, 16, 16, 16, 14, 14, 15, 16, 15, 15, 15, 16,
    40, 40, 40, 40, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 14, 14, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 15, 15, 16, 16, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 14, 48, 48, 48, 48, 16, 16, 16, 16, 8, 16,
    16, 16, 16, 16, 16, 48, 48, 48, 48, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 27, 16, 16, 14, 14, 16,
}
local SPR_OX = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
    4, 4, 4, 4, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 8, -7, 0, 0, 0, 0, 0,
}
local SPR_OY = {
    -2, -2, -2, -2, -2, -1, -1, 0, 4, 4, 5, -1, 0, 5, 0, 0,
    1, 1, 1, 1, -2, -2, -2, -2, -2, -2, 0, 0, 0, 0, 0, -1,
    -2, -2, -2, -2, -2, 5, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, -1, -1, 4, 4, 0, 0, -2, 0, -1, -1, 0,
    -1, -1, 5, 0, -1, -1, 13, 0, -2, 0, 0, -1, -1, -1, -1, -2,
    -2, -2, -2, -2, -2, 0, 0, 0, 0, 0, -2, -2, -2, 0, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -7, 0, 0, 5, 2, 0,
}

local M = nil
local function rd8(addr) return emu.read(addr, M) or 0 end

-- Decoration and color/tile/ground-trigger sprite types have no gameplay
-- hitbox; skip them (same exclusion sets as the editor/simulator's viewer).
local function isNonGameplaySprite(t)
    if t >= 0x2A and t <= 0x3F then return true end   -- decorations
    if t == 0x49 or t == 0x4A then return true end    -- decorations
    if t >= 0x80 and t <= 0x8C then return true end   -- bg color triggers
    if t >= 0x90 and t <= 0x9C then return true end
    if t >= 0xA0 and t <= 0xAC then return true end
    if t == 0x8F or t == 0x9F or t == 0xCF then return true end
    if t == 0xAE or t == 0xAF then return true end
    if t >= 0xB0 and t <= 0xBF then return true end   -- tile triggers
    if t >= 0xC0 and t <= 0xCC then return true end   -- ground color triggers
    if t >= 0xD0 and t <= 0xDC then return true end
    if t >= 0xE0 and t <= 0xEC then return true end
    return false
end

local function drawPlayer(p, color, gamemode)
    local x = rd8(A.player_x + p * 2 + 1)
    local y = rd8(A.player_y + p * 2 + 1)
    local mini = (rd8(A.player_mini + p) ~= 0) and 1 or 0
    local w, h
    if gamemode == GM_WAVE or gamemode == GM_SNAKE then w, h = WAVE_W, WAVE_H
    else w, h = CUBE_W[mini], CUBE_H[mini] end
    local topOff = (mini ~= 0) and ((16 - h) >> 1) or 0
    emu.drawRectangle(x, y + topOff, w + 1, h + 1, color, false)
end

emu.addEventCallback(function()
    M = emu.memType.nesMemory
    if rd8(A.gameState) ~= STATE_GAME then return end

    for i = 0, 15 do
        if rd8(A.spr_active + i) > 0 then
            local t = rd8(A.spr_type + i)
            local w, h = SPR_W[t + 1] or 16, SPR_H[t + 1] or 16
            if w > 0 and h > 0 and not isNonGameplaySprite(t) then
                local ox, oy = SPR_OX[t + 1] or 0, SPR_OY[t + 1] or 0
                local x = rd8(A.spr_realx + i) + ox
                local y = rd8(A.spr_realy + i) + oy
                emu.drawRectangle(x, y, w, h, COLOR_SPRITE, true)
                if SHOW_SPRITE_IDS then
                    emu.drawString(x, y - 7, string.format("%02X", t), 0xFFFFFF, 0xFF000000)
                end
            end
        end
    end

    if SHOW_PLAYER then
        local gamemode = rd8(A.gamemode)
        drawPlayer(0, COLOR_PLAYER1, gamemode)
        if rd8(A.dual) ~= 0 then drawPlayer(1, COLOR_PLAYER2, gamemode) end
    end
end, emu.eventType.startFrame)

emu.log("famidash sprite hitbox overlay loaded")
