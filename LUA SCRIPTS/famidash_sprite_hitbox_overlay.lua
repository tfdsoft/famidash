-- famidash_sprite_hitbox_overlay.lua
--
-- SPRITE-ONLY hitbox viewer for FamiDash (Mesen2). Draws the hitboxes of all
-- active sprite objects (transparent white) plus the player collision boxes.
--
-- Dimensions come from the validated tables in the FamiDash editor/simulator
-- (Editor Test/SimulatorWindow.xaml.cs): identical to the ROM tables but with
-- the 0xFF "special" markers replaced by the objects' real sizes, plus the
-- simulator's non-flipped-pad +8px shift. Types with zero size are triggers /
-- decorations and are skipped.
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

-- Non-flipped pads get their hitbox shifted 8px down (simulator rule)
local PAD_DOWN_IDS = { [0x52]=true, [0x0A]=true, [0x0D]=true, [0x25]=true, [0xFD]=true }

local M = nil
local function rd8(addr) return emu.read(addr, M) or 0 end

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
            if w > 0 and h > 0 then
                local ox, oy = SPR_OX[t + 1] or 0, SPR_OY[t + 1] or 0
                if PAD_DOWN_IDS[t] then oy = oy + 8 end
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
