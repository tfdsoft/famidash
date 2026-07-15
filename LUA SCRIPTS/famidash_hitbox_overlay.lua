-- famidash_hitbox_overlay.lua
--
-- Combined SPRITE + TILE hitbox overlay for FamiDash (Mesen2).
--
--   * Tiles: draws the actual collision geometry of every on-screen metatile
--     from the game's collision map ($6000-$63FF) and metatiles_coll table.
--     Anything that can kill you (spike/death sub-regions, exactly as the
--     game tests them) is RED; all other collision geometry (solids, slabs,
--     quadrants, stairs, slopes, ground) is YELLOW. Metatile ids listed in
--     EXCLUDED_TILE_IDS are skipped entirely.
--   * Sprites: hitboxes of all active sprite objects using the validated
--     per-type dimension tables from the FamiDash editor/simulator
--     (Editor Test/SimulatorWindow.xaml.cs). These match the ROM tables but
--     replace the 0xFF "special" markers with the objects' real sizes, and
--     include the simulator's non-flipped-pad +8px shift.
--   * Player: real collision hitbox for both players (and probe points the
--     background collision actually samples, if enabled).
--
-- Geometry is produced by rasterizing direct ports of the game's collision
-- predicates (bg_coll_spikes / bg_coll_mini_blocks / slabs / slopes), so the
-- overlay is pixel-exact by construction.
--
-- Addresses: RAM addresses are identical across all ROM variants. ROM tables
-- (metatiles_coll, sprite_widths/...) are resolved via debugger labels when
-- available, else by parsing the .dbg file next to the ROM.
--
-- Drop into Mesen2 via Tools -> Lua Scripting -> Open Script.

--------------------------------------------------------------------------
-- Config
--------------------------------------------------------------------------
local SHOW_TILES      = true
local SHOW_SPRITES    = true
local SHOW_PLAYER     = true
local SHOW_PROBES     = false   -- dots at the game's collision probe points
local SHOW_SPRITE_IDS = false   -- draw sprite type numbers

-- metatile ids that never get a hitbox drawn
local EXCLUDED_TILE_IDS = { [0x00] = true }

-- Screen-space calibration for the tile grid: the rendered background sits
-- one pixel right of where collision-world coordinates land on screen.
local TILE_OFFSET_X = 1
local TILE_OFFSET_Y = 0

-- 0xAARRGGBB, alpha 0x00 = opaque, higher = more transparent
-- Lethal regions are red; everything non-lethal is yellow.
local COLOR_KILL      = 0x50FF3030
local COLOR_SAFE      = 0x82FFFF00
local COLOR_SPRITE    = 0x60FFFFFF
local COLOR_PLAYER1   = 0xFFFFFF
local COLOR_PLAYER2   = 0xFF9000
local COLOR_PROBE     = 0xFF00FF

--------------------------------------------------------------------------
-- Fixed RAM addresses (verified identical across all FamiDash variants)
--------------------------------------------------------------------------
local A = {
    gameState  = 0x049C,
    scroll_x   = 0x04A6,  -- u32
    scroll_y   = 0x04AA,  -- u16, lo + hi*240
    player_x   = 0x043D,  -- u16[2], hi byte = screen pixel
    player_y   = 0x0441,  -- u16[2]
    player_mini= 0x044F,  -- u8[2]
    player_grav= 0x044D,  -- u8[2]
    gamemode   = 0x007A,
    dual       = 0x0096,
    collMap    = 0x6000,  -- u8[4][256]
    spr_type   = 0x051B,  -- u8[16]
    spr_realx  = 0x054B,  -- u8[16]
    spr_realy  = 0x055B,  -- u8[16]
    spr_active = 0x056B,  -- u8[16]
}
local STATE_GAME = 0x02
local GM_SHIP, GM_WAVE, GM_SNAKE = 1, 6, 10
local CUBE_W, CUBE_H = { [0]=15, [1]=8 }, { [0]=15, [1]=7 }
local WAVE_W, WAVE_H = 8, 8

--------------------------------------------------------------------------
-- Sprite hitbox dimension tables, taken from the FamiDash editor/simulator
-- (the validated hitbox viewer). Indexed by sprite type 0..255 (+1 in Lua).
-- Entries with width/height 0 are trigger/decoration types with no hitbox.
--------------------------------------------------------------------------
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

local M = nil  -- emu.memType.nesMemory at callback time
local function rd8(addr) return emu.read(addr, M) or 0 end
local function rd16(addr) return emu.read16(addr, M) or 0 end
local function rd32(addr) return emu.read32(addr, M) or 0 end

--------------------------------------------------------------------------
-- Symbol resolution: debugger label -> .dbg file -> nil
-- Returns { addr = <number>, memType = <memType> } or nil.
-- ROM symbols get PRG-ROM offsets (bank-independent reads).
--------------------------------------------------------------------------
local dbgSyms = nil  -- name -> {val, seg}; segs: id -> {start, ooffs}

local function loadDbgFile()
    if dbgSyms ~= nil then return end
    dbgSyms = { syms = {}, segs = {} }
    local ok, romPath = pcall(function() return emu.getRomInfo().path end)
    if not ok or not romPath or #romPath == 0 then return end
    local dbgPath = romPath:gsub("%.[Nn][Ee][Ss]$", ".dbg")
    local okIo, f = pcall(io.open, dbgPath, "r")
    if not okIo or not f then return end
    for line in f:lines() do
        local id, start, ooffs = line:match('^seg\tid=(%d+),.-start=0x(%x+),.-ooffs=(%d+)')
        if id then
            dbgSyms.segs[tonumber(id)] = { start = tonumber(start, 16), ooffs = tonumber(ooffs) }
        else
            local name, val, seg = line:match('^sym\tid=%d+,name="([%w_]+)",.-val=0x(%x+),seg=(%d+)')
            if name then
                dbgSyms.syms[name] = { val = tonumber(val, 16), seg = tonumber(seg) }
            end
        end
    end
    f:close()
end

local function resolveSymbol(name, wantRomOffset)
    local ok, label = pcall(function() return emu.getLabelAddress(name) end)
    if ok and label and label.address and label.address >= 0 and label.memType then
        return { addr = label.address, memType = label.memType }
    end
    loadDbgFile()
    local sym = dbgSyms.syms[name]
    if sym == nil then return nil end
    if wantRomOffset then
        local seg = dbgSyms.segs[sym.seg]
        if seg == nil then return nil end
        return { addr = seg.ooffs - 16 + (sym.val - seg.start), memType = emu.memType.nesPrgRom }
    end
    return { addr = sym.val, memType = emu.memType.nesMemory }
end

--------------------------------------------------------------------------
-- ROM data: metatiles_coll (cached once)
--------------------------------------------------------------------------
local metaColl = nil
local romTried = false

local function tryLoadRomData()
    if romTried then return end
    romTried = true

    -- metatiles_coll sits in the fixed $8000-$9FFF bank, so its CPU address
    -- is always readable; a PRG-ROM offset works too.
    local mc = resolveSymbol("_metatiles_coll", false) or resolveSymbol("metatiles_coll", false)
    if mc then
        metaColl = {}
        for i = 0, 255 do
            metaColl[i] = emu.read(mc.addr + i, mc.memType) or 0
        end
        emu.log("hitbox overlay: metatiles_coll found, tile hitboxes enabled")
    else
        emu.log("hitbox overlay: metatiles_coll not found - tile hitboxes disabled")
    end
end

--------------------------------------------------------------------------
-- Collision-class geometry, rasterized from ports of the game's predicates
-- (SAUCE/functions/collision.h) and merged into rectangles at load time.
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

-- bg_coll_spikes kill regions
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

-- bg_coll_slope surface geometry ("solid" for the full-block 66deg halves)
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

-- bg_coll_U_D_checks / mini_blocks / slabs solid occupancy
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
    local open = {}   -- open[x.."_"..w] = rect being extended
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
-- Sprite pass, using the simulator's validated dimension tables
--------------------------------------------------------------------------
local function drawSprites()
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
end

--------------------------------------------------------------------------
-- Player pass: real collision hitbox (+ optional probe points)
--------------------------------------------------------------------------
local function drawPlayer(p, color, gamemode)
    local x = rd8(A.player_x + p * 2 + 1)   -- hi byte = screen pixel
    local y = rd8(A.player_y + p * 2 + 1)
    local mini = (rd8(A.player_mini + p) ~= 0) and 1 or 0
    local waveLike = (gamemode == GM_WAVE or gamemode == GM_SNAKE)

    local w, h
    if waveLike then w, h = WAVE_W, WAVE_H
    else w, h = CUBE_W[mini], CUBE_H[mini] end

    -- collision code offsets the box down only for mini icons
    local topOff = (mini ~= 0) and ((16 - h) >> 1) or 0
    emu.drawRectangle(x, y + topOff, w + 1, h + 1, color, false)

    if SHOW_PROBES then
        -- probe points used by bg_coll_D / bg_coll_U / bg_coll_death
        local genX = waveLike and (x + 4) or x
        local genY = waveLike and (y + ((mini == 0) and 4 or 0)) or y
        local woff = waveLike and 4 or 0
        local footY = genY + h + topOff
        local headY = genY + ((mini ~= 0) and topOff or 0) + (waveLike and 0 or 1)
        for _, px in ipairs({ genX + woff, genX + woff + (w >> 1), genX + w }) do
            emu.drawRectangle(px, footY, 1, 1, COLOR_PROBE, true)
            emu.drawRectangle(px, headY, 1, 1, COLOR_PROBE, true)
        end
        -- center death probe
        emu.drawRectangle(x + (w >> 1) - 1, y + (h >> 1) + topOff, 1, 1, 0xFF0000, true)
    end
end

--------------------------------------------------------------------------
-- Main callback
--------------------------------------------------------------------------
emu.addEventCallback(function()
    M = emu.memType.nesMemory
    tryLoadRomData()

    if rd8(A.gameState) ~= STATE_GAME then return end

    local scrollX = rd32(A.scroll_x)
    local syRaw = rd16(A.scroll_y)
    local scrollLin = (syRaw & 0xFF) + ((syRaw >> 8) & 0xFF) * 240
    local gamemode = rd8(A.gamemode)

    if SHOW_TILES then drawTiles(scrollX, scrollLin) end
    if SHOW_SPRITES then drawSprites() end
    if SHOW_PLAYER then
        drawPlayer(0, COLOR_PLAYER1, gamemode)
        if rd8(A.dual) ~= 0 then drawPlayer(1, COLOR_PLAYER2, gamemode) end
    end
-- startFrame, not endFrame: at endFrame the game has already computed the
-- NEXT frame's scroll/positions, which shifts every world-anchored box a few
-- pixels left of the image on screen. At startFrame RAM still matches the
-- frame being rendered (same event the original sprite hitbox script used).
end, emu.eventType.startFrame)

-- test hook (inert unless a harness defines the global first)
if _G.__FAMIDASH_HITBOX_TEST_HOOK then
    _G.__FAMIDASH_HITBOX_TEST_HOOK({
        CLASS_GEOM = CLASS_GEOM,
        rasterize = rasterize,
        solidAt = solidAt,
        killAt = killAt,
        resolveSymbol = resolveSymbol,
        SPR_W = SPR_W, SPR_H = SPR_H, SPR_OX = SPR_OX, SPR_OY = SPR_OY,
    })
end

emu.log("famidash combined sprite+tile hitbox overlay loaded")
