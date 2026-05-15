-- famidash_path_overlay_projected.lua
--
-- Standalone Mesen2 Lua script: draws the travelled path (yellow) and a
-- 60-frame projected trajectory (cyan family) using velocity + acceleration
-- extrapolation from recent motion history.
--
-- Drop into Mesen2 via Tools -> Lua Scripting -> Open Script.

local STATE_GAME         = 0x02
local ADDR_GAMESTATE     = 0x049C
local ADDR_SCROLL_X      = 0x04A6  -- 32-bit
local ADDR_SCROLL_Y      = 0x04AA  -- 16-bit raw (lo|hi); linearised as lo + hi*240
local ADDR_PLAYER_X      = 0x043D  -- 16-bit (hi byte is pixel)
local ADDR_PLAYER_Y      = 0x0441  -- 16-bit (hi byte is pixel)
local ADDR_JOYPAD1_HOLD  = 0x0022

local PAD_A  = 0x80
local PAD_UP = 0x08
local GAMEMODE_SHIP = 1

local TRAIL_MAX           = 600
local TRAIL_COLOR         = 0xFFFF00  -- yellow
local PROJECT_FRAMES      = 60
local PROJECT_COLOR_MAIN  = 0x00D8FF  -- cyan
local PROJECT_DOT_COLOR   = 0xB8FBFF  -- endpoint marker
local MAX_SPEED_PX_PER_F   = 8
local MAX_ACCEL_PX_PER_F2  = 0.35
local VEL_SMOOTH           = 0.80
local ACC_SMOOTH           = 0.88
local OUTLIER_SPEED_PX_PER_F = 14
local CUBE_HOLD_JUMP_VEL     = -4.10
local CUBE_HOLD_GRAVITY      = 0.26

local function getRgb(color)
    local b = color & 0xFF
    local g = (color >> 8) & 0xFF
    local r = (color >> 16) & 0xFF
    return r, g, b
end

local function makeCollisionSampler(screenBuffer, screenW, screenH, scrollY)
    if screenBuffer == nil or screenW == nil or screenH == nil then
        return nil
    end

    local function getPixel(x, y)
        if x < 0 or y < 0 or x >= screenW or y >= screenH then return nil end
        return screenBuffer[y * screenW + x + 1]
    end

    local function isBrightTop(color)
        if color == nil then return false end
        local r, g, b = getRgb(color)
        return (r >= 180 and g >= 180 and b >= 180)
    end

    local function isDarkBelow(color)
        if color == nil then return false end
        local r, g, b = getRgb(color)
        return (r + g + b) <= 280
    end

    local globalFloorSy = nil
    local bestScore = 0
    for sy = math.floor(screenH * 0.20), screenH - 2 do
        local score = 0
        for sx = 0, screenW - 1 do
            local top = getPixel(sx, sy)
            local below = getPixel(sx, sy + 1)
            if isBrightTop(top) and isDarkBelow(below) then
                score = score + 1
            end
        end
        if score > bestScore then
            bestScore = score
            globalFloorSy = sy
        end
    end
    if bestScore < math.floor(screenW * 0.25) then
        globalFloorSy = nil
    end

    return function(worldX, minWorldY)
        local sx = math.floor(worldX + 0.5)
        if sx < 0 or sx >= screenW then
            if globalFloorSy ~= nil then return scrollY + globalFloorSy end
            return nil
        end

        local startSy = math.floor((minWorldY - scrollY) - 2)
        if startSy < 0 then startSy = 0 end
        if startSy > screenH - 2 then startSy = screenH - 2 end

        for sy = startSy, screenH - 2 do
            local topMid = getPixel(sx, sy)
            local belowMid = getPixel(sx, sy + 1)
            local topL = getPixel(sx - 1, sy)
            local topR = getPixel(sx + 1, sy)
            local belowL = getPixel(sx - 1, sy + 1)
            local belowR = getPixel(sx + 1, sy + 1)

            local brightTopCount = 0
            if isBrightTop(topL) then brightTopCount = brightTopCount + 1 end
            if isBrightTop(topMid) then brightTopCount = brightTopCount + 1 end
            if isBrightTop(topR) then brightTopCount = brightTopCount + 1 end

            local darkBelowCount = 0
            if isDarkBelow(belowL) then darkBelowCount = darkBelowCount + 1 end
            if isDarkBelow(belowMid) then darkBelowCount = darkBelowCount + 1 end
            if isDarkBelow(belowR) then darkBelowCount = darkBelowCount + 1 end

            if brightTopCount >= 2 and darkBelowCount >= 2 then
                return scrollY + sy
            end
        end

        if globalFloorSy ~= nil then
            return scrollY + globalFloorSy
        end
        return nil
    end
end

local function tryReadGamemode()
    if not gamemodeLabelChecked then
        gamemodeLabelChecked = true
        local ok, label = pcall(function() return emu.getLabelAddress("_gamemode") end)
        if ok and label and label.address ~= nil and label.memType ~= nil then
            gamemodeLabel = label
        end
    end

    if gamemodeLabel ~= nil then
        return emu.read(gamemodeLabel.address, gamemodeLabel.memType, false)
    end
    return nil
end

local function drawTrailSegment(ax, ay, bx, by, color, thickness)
    emu.drawLine(ax, ay, bx, by, color)
    local radius = math.floor((thickness - 1) / 2)
    if radius <= 0 then return end

    local dx = bx - ax
    local dy = by - ay
    for i = 1, radius do
        if math.abs(dx) >= math.abs(dy) then
            emu.drawLine(ax, ay - i, bx, by - i, color)
            emu.drawLine(ax, ay + i, bx, by + i, color)
        else
            emu.drawLine(ax - i, ay, bx - i, by, color)
            emu.drawLine(ax + i, ay, bx + i, by, color)
        end
    end
end

local function drawFilledCircle(cx, cy, radius, color)
    for dy = -radius, radius do
        local span = math.floor(math.sqrt(radius * radius - dy * dy) + 0.5)
        emu.drawLine(cx - span, cy + dy, cx + span, cy + dy, color)
    end
end

local trail = {}
local trailHead = 1   -- next write slot
local trailCount = 0  -- valid entries
local prevPx = -1
local prevPy = -1
local prevXf = nil
local prevYf = nil
local prevVelX = 0
local prevVelY = 0
local velX = 0
local velY = 0
local accX = 0
local accY = 0
local landingLockFrames = 0
local lastGroundY = nil
local gamemodeLabel = nil
local gamemodeLabelChecked = false
local prevAHeld = false

local function clamp(v, lo, hi)
    if v < lo then return lo end
    if v > hi then return hi end
    return v
end

local function drawProjectedPath(scrollX, scrollY, startX, startY, startVelX, startVelY, accelX, accelY, color)
    local fromX, fromY = startX, startY
    local vX, vY = startVelX, startVelY

    local function w2sx(x) return x - scrollX end
    local function w2sy(y) return y - scrollY end

    for i = 1, PROJECT_FRAMES do
        vX = vX + accelX
        vY = vY + accelY

        local toX = fromX + vX
        local toY = fromY + vY

        local axS, ayS = w2sx(fromX), w2sy(fromY)
        local bxS, byS = w2sx(toX),   w2sy(toY)
        if (axS >= -16 and axS <= 272 and ayS >= -16 and ayS <= 256)
           or (bxS >= -16 and bxS <= 272 and byS >= -16 and byS <= 256) then
            emu.drawLine(axS, ayS, bxS, byS, color)
        end

        fromX, fromY = toX, toY
    end

    return fromX, fromY
end

local function drawProjectedCubeHoldPath(scrollX, scrollY, startX, startY, startVelX, accelX, groundY, color, sampleCollisionY)
    local fromX, fromY = startX, startY
    local vX = startVelX
    local vY = 0
    local onGround = (math.abs(startY - groundY) <= 2.0)

    local function w2sx(x) return x - scrollX end
    local function w2sy(y) return y - scrollY end

    for i = 1, PROJECT_FRAMES do
        vX = vX + accelX

        if onGround then
            -- While held, cube jumps again immediately on touchdown.
            vY = CUBE_HOLD_JUMP_VEL
            onGround = false
        else
            vY = vY + CUBE_HOLD_GRAVITY
        end

        local toX = fromX + vX
        local toY = fromY + vY

        local floorY = groundY
        if sampleCollisionY ~= nil then
            local sampled = sampleCollisionY(toX - scrollX, math.min(fromY, toY))
            if sampled ~= nil then
                floorY = sampled
            end
        end

        if floorY ~= nil and toY >= floorY then
            toY = floorY
            vY = 0
            onGround = true
        end

        local axS, ayS = w2sx(fromX), w2sy(fromY)
        local bxS, byS = w2sx(toX),   w2sy(toY)
        if (axS >= -16 and axS <= 272 and ayS >= -16 and ayS <= 256)
           or (bxS >= -16 and bxS <= 272 and byS >= -16 and byS <= 256) then
            emu.drawLine(axS, ayS, bxS, byS, color)
        end

        fromX, fromY = toX, toY
    end

    return fromX, fromY
end

local function drawProjectedNoRisePath(scrollX, scrollY, startX, startY, startVelX, startVelY, accelX, accelY, groundY, color, sampleCollisionY)
    local fromX, fromY = startX, startY
    local vX = startVelX
    local vY = math.max(0, startVelY)
    local aY = math.max(0, accelY)

    local function w2sx(x) return x - scrollX end
    local function w2sy(y) return y - scrollY end

    for i = 1, PROJECT_FRAMES do
        vX = vX + accelX
        vY = math.max(0, vY + aY)

        local toX = fromX + vX
        local toY = fromY + vY

        local floorY = groundY
        if sampleCollisionY ~= nil then
            local sampled = sampleCollisionY(toX - scrollX, math.min(fromY, toY))
            if sampled ~= nil then
                floorY = sampled
            end
        end

        if floorY ~= nil and toY >= floorY then
            toY = floorY
            vY = 0
            aY = 0
        end

        local axS, ayS = w2sx(fromX), w2sy(fromY)
        local bxS, byS = w2sx(toX),   w2sy(toY)
        if (axS >= -16 and axS <= 272 and ayS >= -16 and ayS <= 256)
           or (bxS >= -16 and bxS <= 272 and byS >= -16 and byS <= 256) then
            emu.drawLine(axS, ayS, bxS, byS, color)
        end

        fromX, fromY = toX, toY
    end

    return fromX, fromY
end

local function clearTrail()
    trail = {}
    trailHead = 1
    trailCount = 0
    prevPx = -1
    prevPy = -1
    prevXf = nil
    prevYf = nil
    prevVelX = 0
    prevVelY = 0
    velX = 0
    velY = 0
    accX = 0
    accY = 0
    landingLockFrames = 0
    lastGroundY = nil
    prevAHeld = false
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

    -- Player world position (hitbox center).
    local rawX = emu.read16(ADDR_PLAYER_X, M) or 0
    local rawY = emu.read16(ADDR_PLAYER_Y, M) or 0
    local px = scrollX + (rawX >> 8) + 8
    local py = scrollY + (rawY >> 8) + 8

    -- Guard against invalid camera/player values during transitions.
    if px < 0 or px >= 0x80000 then
        if trailCount > 0 then clearTrail() end
        prevPx = -1
        prevPy = -1
        return
    end

    -- Detect respawn: player X resets to 0 / jumps far backward.
    if prevPx > 0 and (px <= 0 or px < prevPx - 16) then
        clearTrail()
    end

    -- Fixed-point world coords (8.8) make velocity/accel estimates far less noisy.
    local xFixed = scrollX * 256 + rawX + 8 * 256
    local yFixed = scrollY * 256 + rawY + 8 * 256

    -- Update velocity and acceleration from fixed-point history.
    if prevXf ~= nil and prevYf ~= nil then
        local instVelX = (xFixed - prevXf) / 256.0
        local instVelY = (yFixed - prevYf) / 256.0

        -- Reject discontinuities (camera/state snaps) that otherwise cause
        -- wildly flailing projections.
        if math.abs(instVelX) > OUTLIER_SPEED_PX_PER_F or math.abs(instVelY) > OUTLIER_SPEED_PX_PER_F then
            velX = 0
            velY = 0
            accX = 0
            accY = 0
            prevVelX = 0
            prevVelY = 0
            landingLockFrames = 0
            lastGroundY = nil
        else
            -- Landing heuristic:
            -- If we were descending and vertical speed suddenly collapses near 0,
            -- treat as floor contact and keep projected Y flat for a short window.
            if prevVelY > 1.0 and math.abs(instVelY) < 0.22 then
                landingLockFrames = 8
                lastGroundY = py
            end

            -- Exit landing lock quickly on real airborne motion (jump/fall).
            if math.abs(instVelY) > 0.75 then
                landingLockFrames = 0
            end

            local instAccX = instVelX - prevVelX
            local instAccY = instVelY - prevVelY

            velX = clamp(velX * VEL_SMOOTH + instVelX * (1.0 - VEL_SMOOTH), -MAX_SPEED_PX_PER_F, MAX_SPEED_PX_PER_F)
            velY = clamp(velY * VEL_SMOOTH + instVelY * (1.0 - VEL_SMOOTH), -MAX_SPEED_PX_PER_F, MAX_SPEED_PX_PER_F)
            accX = clamp(accX * ACC_SMOOTH + instAccX * (1.0 - ACC_SMOOTH), -MAX_ACCEL_PX_PER_F2, MAX_ACCEL_PX_PER_F2)
            accY = clamp(accY * ACC_SMOOTH + instAccY * (1.0 - ACC_SMOOTH), -MAX_ACCEL_PX_PER_F2, MAX_ACCEL_PX_PER_F2)

            if landingLockFrames > 0 then
                velY = 0
                accY = 0
                landingLockFrames = landingLockFrames - 1
            end

            prevVelX = instVelX
            prevVelY = instVelY
        end
    else
        velX = 0
        velY = 0
        accX = 0
        accY = 0
        prevVelX = 0
        prevVelY = 0
        landingLockFrames = 0
        lastGroundY = nil
    end
    prevXf = xFixed
    prevYf = yFixed
    prevPx = px
    prevPy = py

    -- Read gameplay hold state from joypad1.hold.
    local hold = emu.read(ADDR_JOYPAD1_HOLD, M) or 0
    local aHeld = ((hold & (PAD_A | PAD_UP)) ~= 0)
    local aPressedFresh = aHeld and (not prevAHeld)
    prevAHeld = aHeld
    local gamemode = tryReadGamemode()

    local screenSize = emu.getScreenSize()
    local screenBuffer = emu.getScreenBuffer()
    local sampleCollisionY = makeCollisionSampler(screenBuffer, screenSize and screenSize.width or nil, screenSize and screenSize.height or nil, scrollY)

    -- Append current position to the ring buffer.
    trail[trailHead] = { x = px, y = py, a = aHeld, p = aPressedFresh }
    trailHead = trailHead + 1
    if trailHead > TRAIL_MAX then trailHead = 1 end
    if trailCount < TRAIL_MAX then trailCount = trailCount + 1 end

    local function w2sx(x) return x - scrollX end
    local function w2sy(y) return y - scrollY end

    -- Draw travelled trail.
    if trailCount >= 2 then
        local startIdx
        if trailCount < TRAIL_MAX then
            startIdx = 1
        else
            startIdx = trailHead
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
                if (axS >= -8 and axS <= 264 and ayS >= -8 and ayS <= 248)
                   or (bxS >= -8 and bxS <= 264 and byS >= -8 and byS <= 248) then
                    local pressedFresh = (prevEntry.p == true) or (curEntry.p == true)
                    local held = (prevEntry.a == true) or (curEntry.a == true)
                    local thickness = 1
                    if held then thickness = 3 end
                    drawTrailSegment(axS, ayS, bxS, byS, TRAIL_COLOR, thickness)
                    if pressedFresh and curEntry.p == true then
                        drawFilledCircle(bxS, byS, 4, TRAIL_COLOR)
                    end
                end
            end
            prevEntry = curEntry
        end
    end

    -- Draw one stable projected trajectory arc.
    if velX ~= 0 or velY ~= 0 then
        local endMainX, endMainY
        local useHeldCubeBounce = aHeld and (landingLockFrames > 0 or math.abs(velY) < 0.2) and lastGroundY ~= nil
        local useShipFlight = (gamemode == GAMEMODE_SHIP)
        local useLikelyShipFallback = (gamemode == nil and aHeld and landingLockFrames == 0
            and (velY < -0.10 or accY < -0.03)
            and (lastGroundY == nil or math.abs(py - lastGroundY) > 12))

        if useHeldCubeBounce then
            endMainX, endMainY = drawProjectedCubeHoldPath(scrollX, scrollY, px, py, velX, accX, lastGroundY, PROJECT_COLOR_MAIN, sampleCollisionY)
        elseif useShipFlight or useLikelyShipFallback then
            -- Ship projection must support upward arcs while input is held.
            endMainX, endMainY = drawProjectedPath(scrollX, scrollY, px, py, velX, velY, accX, accY, PROJECT_COLOR_MAIN)
        else
            -- Normal-gravity cube preview should not project upward. Use a
            -- strict non-rising path unless held-jump bounce mode is active.
            endMainX, endMainY = drawProjectedNoRisePath(scrollX, scrollY, px, py, velX, velY, accX, accY, lastGroundY, PROJECT_COLOR_MAIN, sampleCollisionY)
        end

        local endX = w2sx(endMainX)
        local endY = w2sy(endMainY)
        emu.drawRectangle(endX - 1, endY - 1, 3, 3, PROJECT_DOT_COLOR, true)
    end
end, emu.eventType.endFrame)
