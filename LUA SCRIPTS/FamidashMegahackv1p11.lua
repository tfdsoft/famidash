-----------------------
-- Famidash Megahack v1.11
-- By: Aaron Chen-Chang (Air Conditioner) & more
-----------------------
-- Recommend pausing before opening menu
-- press right to open menu, press left to close menu
-- press up or down to move cursor, press A to select the hack you want to activate
-----------------------
-- Current hacks include: Clicks HUD, Input Test, Random Gamemode, Editable Text, Path Overlay, Ship Copter
-- Cheat Indicator included and is always on.
-----------------------
-- Update log:
-- v1.0 - Added mod menu
-- Added - Clicks HUD, Input Test, Random Gamemode
-- v1.1 - Added cheat indicator
-- Added - Editable Text, path overlay
-- V1.11
-- Fixed cheat indicator to make it so that it also checks for debug mode (but only when you press select, so the old way to use debug mode still doesn't make it red)
-- Added - Ship Copter
-----------------------

local editableMessage = "Editable text" -- edit this text with anything you want
local editableX = 0
local editableY = 120
local editableShowBox = true
local cheatUsedThisAttempt = false
local prevSelect = false
local STATE_GAME     = 0x02
local ADDR_GAMESTATE = 0x049C
local ADDR_PLAYER_X  = 0x043D
local clicked_a = false
local clicked_up = false

-- =========================
-- MENU SYSTEM
-- =========================

local menuOpen = false
local selected = 1

local prevRight = false
local prevLeft = false
local prevA = false
local prevUp = false
local prevDown = false

local options = {
    "Clicks HUD",
    "Input Test",
    "Random Gamemode",
    "Editable Text",
    "Path Overlay",
    "Ship Copter"
}

local enabled = { false, false, false, false, false, false }

-- COLORS
local GREEN  = 0x8000FF00
local RED    = 0x80FF0000
local BLACK  = 0x00000000
local WHITE  = 0xFFFFFF

-- =========================
-- CLICK HUD
-- =========================

local totalClicks = 0
local clickTimes = {}
local frameCounter = 0

local prevA_click = false
local prevUp_click = false
local prevPlayerX = nil

local function resetAll()
    totalClicks = 0
    clickTimes = {}
    frameCounter = 0

    prevA_click = false
    prevUp_click = false
end

local function ClicksHUD()

    local M = emu.memType.nesMemory
    local gameState = emu.read(ADDR_GAMESTATE, M) or 0

    if gameState ~= STATE_GAME then return end

    local rawX = emu.read16(ADDR_PLAYER_X, M) or 0
    local playerX = rawX >> 8

    if prevPlayerX ~= nil and playerX < prevPlayerX - 20 then
        resetAll()
    end

    prevPlayerX = playerX

    local input = emu.getInput(0)

    frameCounter = frameCounter + 1

    local aDown = input.a
    local upDown = input.up

    if aDown and not prevA_click then
        totalClicks = totalClicks + 1
        table.insert(clickTimes, frameCounter)
    end

    if upDown and not prevUp_click then
        totalClicks = totalClicks + 1
        table.insert(clickTimes, frameCounter)
    end

    prevA_click = aDown
    prevUp_click = upDown

    while #clickTimes > 0 and clickTimes[1] < frameCounter - 60 do
        table.remove(clickTimes, 1)
    end
    
    local cpsColor
    
       local cps = #clickTimes


    if cps == 0 then
        cpsColor = 0x80000000
    elseif cps <= 5 then
        cpsColor = 0x8000FF00
    elseif cps <= 10 then
        cpsColor = 0x80FFFF00
    else
        cpsColor = 0x80FF0000
    end

    local cps = #clickTimes

    emu.drawString(10, 10, "Total Clicks: " .. totalClicks, WHITE, (aDown or upDown) and GREEN or BLACK)
    emu.drawString(10, 25, "A Button", WHITE, aDown and GREEN or BLACK)
    emu.drawString(10, 40, "Up Button", WHITE, upDown and GREEN or BLACK)
    emu.drawString(10, 55, "CPS: " .. cps, white, cpsColor)

end

-- =========================
-- INPUT TEST
-- =========================

local function InputTest()

    local input = emu.getInput(0)
    local y = 80

    for button, pressed in pairs(input) do
        if pressed then
            emu.drawString(10, y, button .. " pressed", GREEN)
            y = y + 15
        end
    end
end

-- =========================
-- GAMEMODE RANDOMIZER
-- =========================

local gamemode = 0
local lastGamemode = 255
local inTransition = false

local modeNames = {
    [0] = "Cube", [1] = "Ship", [2] = "Ball", [3] = "UFO",
    [4] = "Robot", [5] = "Spider", [6] = "Wave", [7] = "Swing",
    [8] = "Ninja", [9] = "Pogo", [10] = "Snake", [11] = "Football"
}

local function GamemodeRandomizer()

    local M = emu.memType.nesMemory
    gamemode = emu.read(122, M, false)

    if gamemode ~= lastGamemode then
        inTransition = true
    end

    if inTransition then
        local newMode = math.random(0, 11)
        emu.write(122, newMode, M)

        emu.displayMessage(
            "Megahack",
            "#" .. newMode .. " - " .. (modeNames[newMode] or "Unknown")
        )

        lastGamemode = newMode
        inTransition = false
    else
        lastGamemode = gamemode
    end

    if enabled[3] then
        cheatDotActive = true
    end
end

-- =========================
-- EDITABLE TEXT
-- =========================

local function EditableText()

    if not enabled[4] then return end

    local x = 0
    local y = 0

    local bgColor = 0x80000000
    local textColor = menuOpen and GREEN or WHITE

    if editableShowBox then
        emu.drawRectangle(x - 2, y - 2, #editableMessage * 6 + 4, 12, bgColor, true)
    end

    emu.drawString(x, y, editableMessage, textColor, BLACK)
end

-- =========================
-- PATH OVERLAY 
-- =========================

local trail = {}
local trailHead = 1
local trailCount = 0
local prevPx = -1
local prevAHeld = false

local TRAIL_MAX = 600
local TRAIL_COLOR = 0xFFFF00

local function clearTrail()
    trail = {}
    trailHead = 1
    trailCount = 0
    prevPx = -1
    prevAHeld = false
end

local function PathOverlay()

    if not enabled[5] then
        return
    end

    local M = emu.memType.nesMemory
    local gameState = emu.read(ADDR_GAMESTATE, M) or 0

    if gameState ~= STATE_GAME then
        clearTrail()
        return
    end

    local scrollX = emu.read32(0x04A6, M) or 0
    local sy_raw  = emu.read16(0x04AA, M) or 0
    local scrollY = (sy_raw & 0xFF) + ((sy_raw >> 8) & 0xFF) * 240

    local rawX = emu.read16(0x043D, M) or 0
    local rawY = emu.read16(0x0441, M) or 0

    local px = scrollX + (rawX >> 8) + 8
    local py = scrollY + (rawY >> 8) + 8

    if prevPx > 0 and (px <= 0 or px < prevPx - 16) then
        clearTrail()
    end
    prevPx = px

    local hold = emu.read(0x0022, M) or 0
    local aHeld = ((hold & (0x80 | 0x08)) ~= 0)
    local aPressedFresh = aHeld and (not prevAHeld)
    prevAHeld = aHeld

    trail[trailHead] = { x = px, y = py, p = aPressedFresh, a = aHeld }
    trailHead = trailHead + 1
    if trailHead > TRAIL_MAX then trailHead = 1 end

    if trailCount < TRAIL_MAX then
        trailCount = trailCount + 1
    end

    if trailCount < 2 then return end

    local function w2sx(x) return x - scrollX end
    local function w2sy(y) return y - scrollY end

    local startIdx = (trailCount < TRAIL_MAX) and 1 or trailHead
    local prevEntry = trail[startIdx]

    local idx = startIdx
    for i = 2, trailCount do
        idx = idx + 1
        if idx > TRAIL_MAX then idx = 1 end

        local curEntry = trail[idx]

        if prevEntry and curEntry then
            local axS, ayS = w2sx(prevEntry.x), w2sy(prevEntry.y)
            local bxS, byS = w2sx(curEntry.x), w2sy(curEntry.y)

local held = prevEntry.a or curEntry.a
local thickness = held and 3 or 1

emu.drawLine(axS, ayS, bxS, byS, TRAIL_COLOR)

if thickness == 3 then
    emu.drawLine(axS, ayS-1, bxS, byS-1, TRAIL_COLOR)
    emu.drawLine(axS, ayS+1, bxS, byS+1, TRAIL_COLOR)
end

if prevEntry.p or curEntry.p then
    emu.drawLine(bxS-2, byS, bxS+2, byS, TRAIL_COLOR)
    emu.drawLine(bxS, byS-2, bxS, byS+2, TRAIL_COLOR)
end
        end

        prevEntry = curEntry
    end
end

-- =========================
-- Ship Copter 
-- =========================

local function ShipCopter()
if menuOpen then return end
    if not enabled[6] then
        clicked_a = false
        clicked_up = false
        return
    end

    if emu.read(122, emu.memType.nesMemory, false) ~= 7 then
        return
    end

    local input = emu.getInput(0)

    emu.setInput({
        a = input.a ~= clicked_a,
        up = input.up ~= clicked_up
    }, 0)

    clicked_a = input.a
    clicked_up = input.up

    cheatUsedThisAttempt = true
end

-- =========================
-- MENU
-- =========================

local function drawMenu()

    emu.drawString(10, 10, "Megahack v1.11 Mod menu")

    for i = 1, #options do

        local name = options[i]
        local state = enabled[i] and "ON" or "OFF"

        local color = (i == 3 or i == 6) and RED or GREEN
        local display = name .. " [" .. state .. "]"

        if i == selected then
            emu.drawString(10, 30 + i * 15, "> " .. display, color, BLACK)
        else
            emu.drawString(20, 30 + i * 15, display, color, BLACK)
        end
    end
end

-- =========================
-- CHEAT DOT 
-- =========================

local function DrawCheatDot()

    local M = emu.memType.nesMemory
    local gameState = emu.read(ADDR_GAMESTATE, M) or 0

    -- detect "death / reset" like ClicksHUD does
    local rawX = emu.read16(ADDR_PLAYER_X, M) or 0
    local playerX = rawX >> 8

if prevPlayerX ~= nil and playerX < prevPlayerX - 20 then
    cheatUsedThisAttempt = false
end

    prevPlayerX = playerX

    local color = cheatUsedThisAttempt and RED or GREEN

    emu.drawString(235, 0, "O", color, BLACK)
end

-- =========================
-- MAIN LOOP
-- =========================

function Main()

    local M = emu.memType.nesMemory
    local gameState = emu.read(ADDR_GAMESTATE, M) or 0
    local inLevel = (gameState == STATE_GAME)

    local input = emu.getInput(0)
if inLevel then
    if input.select and not prevSelect then
        cheatUsedThisAttempt = true
    end
end
    if inLevel then
        if input.right and not prevRight then menuOpen = true end
        if input.left and not prevLeft then menuOpen = false end
    end

    if menuOpen then

        if input.down and not prevDown then
            selected = selected + 1
            if selected > #options then selected = 1 end
        end

        if input.up and not prevUp then
            selected = selected - 1
            if selected < 1 then selected = #options end
        end

        if input.a and not prevA then
            enabled[selected] = not enabled[selected]
        end

        drawMenu()

    else
	if enabled[1] then ClicksHUD() end
	if enabled[2] then InputTest() end
	if enabled[3] then GamemodeRandomizer() end
	EditableText()
    end

    DrawCheatDot()
    PathOverlay()

    prevRight = input.right
    prevLeft = input.left
    prevA = input.a
    prevUp = input.up
    prevDown = input.down
    prevSelect = input.select
end

emu.addEventCallback(Main, emu.eventType.endFrame)
emu.addEventCallback(ShipCopter, emu.eventType.inputPolled)
emu.displayMessage("System", "Famidash Megahack v1.11 Loaded") 