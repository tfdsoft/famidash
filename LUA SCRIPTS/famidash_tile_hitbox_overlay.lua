-- famidash_tile_hitbox_overlay.lua
--
-- TILE-ONLY hitbox viewer for FamiDash (Mesen2). Draws the actual collision
-- geometry of every on-screen metatile from the game's collision map
-- ($6000-$63FF) and metatiles_coll class table.
--
--   RED    = lethal regions (the exact spike/death sub-regions the game
--            tests, not the full tile)
--   YELLOW = all other collision geometry (solids, half-slabs, mini-block
--            quadrants, stairs, slope wedges, ground)
--
-- Geometry is rasterized from direct ports of the game's collision
-- predicates (bg_coll_spikes / bg_coll_mini_blocks / slabs / slopes in
-- SAUCE/functions/collision.h), so shapes are pixel-exact by construction.
-- metatiles_coll differs per ROM variant; it is resolved via debugger labels
-- when available, else by parsing the .dbg file next to the ROM.
--
-- For sprites + tiles combined, use famidash_hitbox_overlay.lua instead.
-- Drop into Mesen2 via Tools -> Lua Scripting -> Open Script.

--------------------------------------------------------------------------
-- Config
--------------------------------------------------------------------------
-- metatile ids that never get a hitbox drawn
local EXCLUDED_TILE_IDS = { [0x00] = true }

-- Screen-space calibration: the rendered background sits one pixel right of
-- where collision-world coordinates land on screen.
local TILE_OFFSET_X = 1
local TILE_OFFSET_Y = 0

local COLOR_KILL = 0x50FF3030
local COLOR_SAFE = 0x82FFFF00

--------------------------------------------------------------------------
-- RAM addresses (identical across all FamiDash ROM variants)
--------------------------------------------------------------------------
local A = {
    gameState = 0x049C,
    scroll_x  = 0x04A6,  -- u32
    scroll_y  = 0x04AA,  -- u16, lo + hi*240
    collMap   = 0x6000,  -- u8[4][256], 16x15 metatile ids per 240px room
}
local STATE_GAME = 0x02

local M = nil
local function rd8(addr) return emu.read(addr, M) or 0 end
local function rd16(addr) return emu.read16(addr, M) or 0 end
local function rd32(addr) return emu.read32(addr, M) or 0 end

--------------------------------------------------------------------------
-- Symbol resolution: debugger label -> .dbg file -> nil
--------------------------------------------------------------------------
local dbgSyms = nil

local function loadDbgFile()
    if dbgSyms ~= nil then return end
    dbgSyms = { syms = {}, segs = {} }
    local ok, romPath = pcall(function() return emu.getRomInfo().path end)
    if not ok or not romPath or #romPath == 0 then return end
    local dbgPath = romPath:gsub("%.[Nn][Ee][Ss]$", ".dbg")
    local okIo, f = pcall(io.open, dbgPath, "r")
    if not okIo or not f then return end
    for line in f:lines() do
        local name, val = line:match('^sym\tid=%d+,name="([%w_]+)",.-val=0x(%x+)')
        if name then
            dbgSyms.syms[name] = tonumber(val, 16)
        end
    end
    f:close()
end

local function resolveSymbol(name)
    local ok, label = pcall(function() return emu.getLabelAddress(name) end)
    if ok and label and label.address and label.address >= 0 and label.memType then
        return { addr = label.address, memType = label.memType }
    end
    loadDbgFile()
    local val = dbgSyms.syms[name]
    if val == nil then return nil end
    return { addr = val, memType = emu.memType.nesMemory }
end

--------------------------------------------------------------------------
-- metatiles_coll (fixed-bank ROM table, cached once)
--------------------------------------------------------------------------
local metaColl = nil
local romTried = false

local function tryLoadRomData()
    if romTried then return end
    romTried = true
    local mc = resolveSymbol("_metatiles_coll") or resolveSymbol("metatiles_coll")
    if mc then
        metaColl = {}
        for i = 0, 255 do
            metaColl[i] = emu.read(mc.addr + i, mc.memType) or 0
        end
        emu.log("tile hitbox overlay: metatiles_coll found, tile hitboxes enabled")
    else
        emu.log("tile hitbox overlay: metatiles_coll not found (no labels / .dbg)")
    end
end

--------------------------------------------------------------------------
-- Collision classes (METATILES/metatiles.h) and geometry predicates,
-- ported from SAUCE/functions/collision.h
--------------------------------------------------------------------------
local COL = {
    DEATH_RIGHT=0x01, DEATH_LEFT=0x02, DEATH_TOP=0x03, DEATH_BOTTOM=0x04,
    TOP=0x05, BOTTOM=0x06, ALL=0x07, DEATH=0x08, FLOOR_CEIL=0x09,
    NO_SIDE=0x1F,
    UP_LEFT=0x20, UP_RIGHT=0x21, DOWN_LEFT=0x22, DOWN_RIGHT=0x23,
    LEFT=0x24, RIGHT=0x25, TL_BR=0x26, TR_BL=0x27,
    DOWN_LEFT_SPIKE=0x28, DOWN_RIGHT_SPIKE=0x29, DOWN_BOTH_SPIKES=0x2A,
    LEFT_SPIKE_BLOCK=0x2B, RIGHT_SPIKE_BLOCK=0x2C,
    BOTTOM_LEFT_SPIKE=0x2D, BOTTOM_RIGHT_SPIKE=0x2E, BOTTOM_SPIKES=0x2F,
    UP_LEFT_SPIKE=0x30, UP_RIGHT_SPIKE=0x31, UP_BOTH_SPIKES=0x32,
    DEATH_TOP_RIGHT=0x33, DEATH_TOP_LEFT=0x34,
    DEATH_BOTTOM_RIGHT=0x35, DEATH_BOTTOM_LEFT=0x36,
    BOTTOM_RIGHT_STAIRS=0x37, BOTTOM_LEFT_STAIRS=0x38,
    TOP_RIGHT_STAIRS=0x39, TOP_LEFT_STAIRS=0x3A,
    TOP_SPIKES=0x3B, BOTTOM_CENTER_SPIKE=0x3C, TOP_CENTER_SPIKE=0x3D,
}

local function deathBottom(ix, iy) return iy > 0x0A and ix >= 0x05 and ix <= 0x07 end
local function deathTop(ix, iy)    return iy < 0x06 and ix >= 0x05 and ix <= 0x07 end
local function deathRight(ix, iy)  return ix >= 0x0A and iy >= 0x06 and iy <= 0x08 end
local function deathLeft(ix, iy)   return ix < 0x06 and iy >= 0x06 and iy <= 0x08 end

local function killAt(class, ix, iy)
    local ix7 = ix & 0x07
    if class == COL.DEATH_LEFT   then return deathLeft(ix, iy) end
    if class == COL.DEATH_RIGHT  then return deathRight(ix, iy) end
    if class == COL.DEATH_TOP    then return deathTop(ix, iy) end
    if class == COL.TOP_CENTER_SPIKE or class == COL.TOP_SPIKES
       or class == COL.DEATH_BOTTOM then return deathBottom(ix, iy) end
    if class == COL.DEATH_BOTTOM_LEFT  then return deathBottom(ix, iy) or deathLeft(ix, iy) end
    if class == COL.DEATH_BOTTOM_RIGHT then return deathBottom(ix, iy) or deathRight(ix, iy) end
    if class == COL.DEATH_TOP_LEFT     then return deathTop(ix, iy) or deathLeft(ix, iy) end
    if class == COL.DEATH_TOP_RIGHT    then return deathTop(ix, iy) or deathRight(ix, iy) end
    if class == COL.DEATH then
        return iy >= 0x04 and iy < 0x0C and ix >= 0x04 and ix <= 0x08
    end
    if class == COL.LEFT_SPIKE_BLOCK or class == COL.BOTTOM_LEFT_SPIKE then
        return (iy & 0x08) == 0 and ix >= 0x02 and ix <= 0x05
    end
    if class == COL.RIGHT_SPIKE_BLOCK or class == COL.BOTTOM_RIGHT_SPIKE then
        return (iy & 0x08) == 0 and ix >= 0x0A and ix <= 0x0C
    end
    if class == COL.BOTTOM_CENTER_SPIKE then
        return (iy & 0x08) == 0 and ix >= 0x07 and ix <= 0x0A
    end
    if class == COL.BOTTOM_SPIKES then
        return (iy & 0x08) == 0 and ix7 >= 0x02 and ix7 <= 0x05
    end
    if class == COL.UP_LEFT_SPIKE then
        return (iy & 0x08) == 0 and ix >= 0x02 and ix <= 0x05
    end
    if class == COL.UP_RIGHT_SPIKE then
        return (iy & 0x08) == 0 and ix >= 0x0A and ix <= 0x0C
    end
    if class == COL.UP_BOTH_SPIKES then
        return (iy & 0x08) == 0 and ix7 >= 0x02 and ix7 <= 0x05
    end
    if class == COL.DOWN_LEFT_SPIKE then
        return (iy & 0x08) ~= 0 and ix >= 0x02 and ix <= 0x05
    end
    if class == COL.DOWN_RIGHT_SPIKE then
        return (iy & 0x08) ~= 0 and ix >= 0x0A and ix <= 0x0C
    end
    if class == COL.DOWN_BOTH_SPIKES then
        return (iy & 0x08) ~= 0 and ix7 >= 0x02 and ix7 <= 0x05
    end
    return false
end

local function slopeGeom(class, ix, iy)
    if class < 0x0B or class > 0x1E then return nil end
    local x2r = (ix >> 1) & 0x07
    local x2l = ((ix >> 1) | 0x08) & 0x0F
    local nY  = iy ~ 0x0F
    if class == 0x0B then return iy >= (ix ~ 0x0F) end                 -- RD45
    if class == 0x0C then return iy >= ix end                          -- LD45
    if class == 0x0D then return iy >= (x2r ~ 0x0F) end                -- RD22_RIGHT
    if class == 0x0E then return iy >= x2r end                         -- LD22_RIGHT
    if class == 0x0F then return iy >= (x2l ~ 0x0F) end                -- RD22_LEFT
    if class == 0x10 then return iy >= x2l end                         -- LD22_LEFT
    if class == 0x11 then                                              -- RD66_TOP
        if ix < 8 then return false end
        return iy >= ((((ix & 7) << 1) & 0x0F) ~ 0x0F) end
    if class == 0x12 then                                              -- LD66_TOP
        if ix >= 8 then return false end
        return iy >= (((ix & 7) << 1) & 0x0F) end
    if class == 0x13 then                                              -- RD66_BOT
        if ix >= 8 then return true end
        return iy >= (((ix << 1) & 0x0F) ~ 0x0F) end
    if class == 0x14 then                                              -- LD66_BOT
        if ix < 8 then return true end
        return iy >= ((ix << 1) & 0x0F) end
    if class == 0x15 then return nY >= (ix ~ 0x0F) end                 -- RU45
    if class == 0x16 then return nY >= ix end                          -- LU45
    if class == 0x17 then return nY >= (x2l ~ 0x0F) end                -- RU22_LEFT
    if class == 0x18 then return nY >= (x2r ~ 0x0F) end                -- RU22_RIGHT
    if class == 0x19 then return nY >= x2l end                         -- LU22_LEFT
    if class == 0x1A then return nY >= x2r end                         -- LU22_RIGHT
    if class == 0x1B then                                              -- RU66_TOP
        if ix < 8 then return false end
        return nY >= ((((ix & 7) << 1) & 0x0F) ~ 0x0F) end
    if class == 0x1C then                                              -- LU66_TOP
        if ix >= 8 then return false end
        return nY >= (((ix & 7) << 1) & 0x0F) end
    if class == 0x1D then                                              -- RU66_BOT
        if ix >= 8 then return true end
        return nY >= (((ix << 1) & 0x0F) ~ 0x0F) end
    if class == 0x1E then                                              -- LU66_BOT
        if ix < 8 then return true end
        return nY >= ((ix << 1) & 0x0F) end
    return nil
end

local function solidAt(class, ix, iy)
    if class == COL.ALL or class == COL.NO_SIDE or class == COL.FLOOR_CEIL then return true end
    if class == COL.TOP    then return iy < 8 end
    if class == COL.BOTTOM then return iy >= 8 end
    if class == COL.UP_LEFT   then return iy < 8 and ix < 8 end
    if class == COL.UP_RIGHT  then return iy < 8 and ix >= 8 end
    if class == COL.DOWN_LEFT  or class == COL.LEFT_SPIKE_BLOCK  then return iy >= 8 and ix < 8 end
    if class == COL.DOWN_RIGHT or class == COL.RIGHT_SPIKE_BLOCK then return iy >= 8 and ix >= 8 end
    if class == COL.BOTTOM_LEFT_SPIKE or class == COL.BOTTOM_RIGHT_SPIKE
       or class == COL.BOTTOM_CENTER_SPIKE or class == COL.BOTTOM_SPIKES then
        return iy >= 8 end
    if class == COL.TOP_CENTER_SPIKE or class == COL.TOP_SPIKES then return iy < 8 end
    if class == COL.LEFT  then return ix < 8 end
    if class == COL.RIGHT then return ix >= 8 end
    if class == COL.TL_BR then return (ix < 8) == (iy < 8) end
    if class == COL.TR_BL then return (ix < 8) ~= (iy < 8) end
    if class == COL.TOP_RIGHT_STAIRS    then return not (iy >= 8 and ix < 8) end
    if class == COL.TOP_LEFT_STAIRS     then return not (iy >= 8 and ix >= 8) end
    if class == COL.BOTTOM_RIGHT_STAIRS then return not (iy < 8 and ix < 8) end
    if class == COL.BOTTOM_LEFT_STAIRS  then return not (iy < 8 and ix >= 8) end
    local sl = slopeGeom(class, ix, iy)
    if sl ~= nil then return sl end
    return false
end

-- rasterize a 16x16 predicate into merged rectangles {x, y, w, h}
local function rasterize(pred)
    local rects = {}
    local open = {}
    for iy = 0, 15 do
        local runs = {}
        local runStart = nil
        for ix = 0, 16 do
            local v = ix < 16 and pred(ix, iy) or false
            if v and runStart == nil then runStart = ix
            elseif not v and runStart ~= nil then
                runs[#runs + 1] = { x = runStart, w = ix - runStart }
                runStart = nil
            end
        end
        local newOpen = {}
        for _, run in ipairs(runs) do
            local key = run.x .. "_" .. run.w
            local prev = open[key]
            if prev and prev.y + prev.h == iy then
                prev.h = prev.h + 1
                newOpen[key] = prev
            else
                local rect = { x = run.x, y = iy, w = run.w, h = 1 }
                rects[#rects + 1] = rect
                newOpen[key] = rect
            end
        end
        open = newOpen
    end
    return rects
end

-- CLASS_GEOM[class] = { solid = {rects}, kill = {rects} }
local CLASS_GEOM = {}
for class = 0x01, 0x3D do
    local geom = {
        solid = rasterize(function(ix, iy) return solidAt(class, ix, iy) end),
        kill  = rasterize(function(ix, iy) return killAt(class, ix, iy) end),
    }
    if #geom.solid > 0 or #geom.kill > 0 then
        CLASS_GEOM[class] = geom
    end
end

--------------------------------------------------------------------------
-- Tile pass
--------------------------------------------------------------------------
local collCache = {}

local function drawTiles(scrollX, scrollLin)
    if metaColl == nil then return end
    for i = 0, 1023 do
        collCache[i] = emu.read(A.collMap + i, M) or 0
    end

    local firstColX = scrollX - (scrollX % 16)
    local firstRowY = scrollLin - (scrollLin % 16)

    for r = 0, 15 do
        local wy = firstRowY + r * 16
        if wy >= 0 then
            local screenY = wy - scrollLin + TILE_OFFSET_Y
            local inRoomY = wy % 240
            local room = (wy // 240) & 3
            local rowBase = room * 256 + (inRoomY & 0xF0)
            for c = 0, 16 do
                local wx = firstColX + c * 16
                local screenX = wx - scrollX + TILE_OFFSET_X
                local tile = collCache[rowBase + ((wx >> 4) & 0x0F)] or 0
                local geom = (not EXCLUDED_TILE_IDS[tile]) and CLASS_GEOM[metaColl[tile] or 0] or nil
                if geom then
                    for _, rc in ipairs(geom.solid) do
                        emu.drawRectangle(screenX + rc.x, screenY + rc.y, rc.w, rc.h, COLOR_SAFE, true)
                    end
                    for _, rc in ipairs(geom.kill) do
                        emu.drawRectangle(screenX + rc.x, screenY + rc.y, rc.w, rc.h, COLOR_KILL, true)
                    end
                end
            end
        end
    end
end

--------------------------------------------------------------------------
-- Main callback (startFrame: RAM matches the frame being rendered)
--------------------------------------------------------------------------
emu.addEventCallback(function()
    M = emu.memType.nesMemory
    tryLoadRomData()

    if rd8(A.gameState) ~= STATE_GAME then return end

    local scrollX = rd32(A.scroll_x)
    local syRaw = rd16(A.scroll_y)
    local scrollLin = (syRaw & 0xFF) + ((syRaw >> 8) & 0xFF) * 240

    drawTiles(scrollX, scrollLin)
end, emu.eventType.startFrame)

emu.log("famidash tile hitbox overlay loaded")
