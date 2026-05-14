-- famidash_path_overlay.lua
--
-- Standalone Mesen2 Lua script: draws a yellow trail of the player's recent
-- positions on top of the NES picture, intended for non-pathfinder gameplay
-- sessions.  Self-contained — no external files, no replay injection.
--
-- Behaviour:
--   * Only draws while gameState == STATE_GAME (0x02 at $049C).
--   * Trail is cleared on respawn (player X jumps backward / resets to 0).
--   * Trail is cleared whenever gameState leaves STATE_GAME (level end,
--     menus, death sequence, etc).
--
-- Drop into Mesen2 via Tools → Lua Scripting → Open Script.

local STATE_GAME      = 0x02
local ADDR_GAMESTATE  = 0x049C
local ADDR_SCROLL_X   = 0x04A6  -- 32-bit
local ADDR_SCROLL_Y   = 0x04AA  -- 16-bit raw (lo|hi); linearised as lo + hi*240
local ADDR_PLAYER_X   = 0x043D  -- 16-bit (hi byte is pixel)
local ADDR_PLAYER_Y   = 0x0441  -- 16-bit (hi byte is pixel)
local ADDR_JOYPAD1_HOLD = 0x0022

local PAD_A  = 0x80
local PAD_UP = 0x08

local TRAIL_MAX   = 600
local TRAIL_COLOR = 0xFFFF00     -- yellow (0xRRGGBB)

local function drawTrailSegment(ax, ay, bx, by, color, thick)
    emu.drawLine(ax, ay, bx, by, color)
    if not thick then return end

    local dx = bx - ax
    local dy = by - ay
    if math.abs(dx) >= math.abs(dy) then
        emu.drawLine(ax, ay - 1, bx, by - 1, color)
        emu.drawLine(ax, ay + 1, bx, by + 1, color)
    else
        emu.drawLine(ax - 1, ay, bx - 1, by, color)
        emu.drawLine(ax + 1, ay, bx + 1, by, color)
    end
end

local trail = {}
local trailHead = 1   -- next write slot
local trailCount = 0  -- valid entries
local prevPx = -1

local function clearTrail()
    trail = {}
    trailHead = 1
    trailCount = 0
    prevPx = -1
end

emu.addEventCallback(function()
    local M = emu.memType.nesMemory
    local gameState = emu.read(ADDR_GAMESTATE, M) or 0

    -- Clear & bail out whenever we are not in active gameplay.
    if gameState ~= STATE_GAME then
        if trailCount > 0 then clearTrail() end
        return
    end

    -- Read camera scroll (NES world coords).
    local scrollX = emu.read32(ADDR_SCROLL_X, M) or 0
    local sy_raw  = emu.read16(ADDR_SCROLL_Y, M) or 0
    local sy_lo   = sy_raw & 0xFF
    local sy_hi   = (sy_raw >> 8) & 0xFF
    local scrollY = sy_lo + sy_hi * 240

    -- Player world position (hitbox center, matching the convention used by
    -- the NES sprite-render pipeline).
    local rawX = emu.read16(ADDR_PLAYER_X, M) or 0
    local rawY = emu.read16(ADDR_PLAYER_Y, M) or 0
    local px = scrollX + (rawX >> 8) + 8
    local py = scrollY + (rawY >> 8) + 8

    -- Sanity guard: at the moment STATE_GAME first becomes active, scrollX
    -- can briefly read as garbage (e.g. 0xFFFFFF82) before the level scroll
    -- is initialised.  Skip those frames and drop the trail.
    if px < 0 or px >= 0x80000 then
        if trailCount > 0 then clearTrail() end
        prevPx = -1
        return
    end

    -- Detect respawn: player X resets to 0 / jumps far backward.
    if prevPx > 0 and (px <= 0 or px < prevPx - 16) then
        clearTrail()
    end
    prevPx = px

    -- Read gameplay hold state from joypad1.hold so this reflects the same
    -- input bits the game logic uses (PAD_A / PAD_UP), independent of Lua API quirks.
    local hold = emu.read(ADDR_JOYPAD1_HOLD, M) or 0
    local aHeld = ((hold & (PAD_A | PAD_UP)) ~= 0)

    -- Append current position to the ring buffer.
    trail[trailHead] = { x = px, y = py, a = aHeld }
    trailHead = trailHead + 1
    if trailHead > TRAIL_MAX then trailHead = 1 end
    if trailCount < TRAIL_MAX then trailCount = trailCount + 1 end

    -- Draw the trail as a polyline.  Walk from the oldest entry to the newest
    -- so segments appear in chronological order.
    if trailCount < 2 then return end

    local function w2sx(x) return x - scrollX end
    local function w2sy(y) return y - scrollY end

    local startIdx
    if trailCount < TRAIL_MAX then
        startIdx = 1
    else
        startIdx = trailHead   -- oldest entry slot (next to be overwritten)
    end

    local prevEntry = trail[startIdx]
    local idx = startIdx
    for step = 2, trailCount do
        idx = idx + 1
        if idx > TRAIL_MAX then idx = 1 end
        local curEntry = trail[idx]
        if prevEntry and curEntry then
            local axS, ayS = w2sx(prevEntry.x), w2sy(prevEntry.y)
            local bxS, byS = w2sx(curEntry.x),  w2sy(curEntry.y)
            -- Only draw segments where at least one endpoint is on-screen.
            if (axS >= -8 and axS <= 264 and ayS >= -8 and ayS <= 248)
               or (bxS >= -8 and bxS <= 264 and byS >= -8 and byS <= 248) then
                local thick = (prevEntry.a == true) or (curEntry.a == true)
                drawTrailSegment(axS, ayS, bxS, byS, TRAIL_COLOR, thick)
            end
        end
        prevEntry = curEntry
    end
end, emu.eventType.endFrame)
