-----------------------
-- Famidash Megahack v1.185
-- By: Aaron Chen-Chang (Air Conditioner) & more...
-- Famidash Update 1.2.8
-- This script was last updated on June 27th, 7:17 P.M. 2026, Taiwan time.
-----------------------
-- In order to use this script, go to Mesen after you download it, open up your Famidash HUGE ROM after you downloaded it from TFDSoft Discord server or downloaded it online, and click Debug on the top bar, and go to Script Window or you can just press ctrl + N to open the script window. And paste this script into it, and click run. 
-----------------------
-- Pause to open the menu, unpause to close the menu when you are in the level.
-- Press the Up or Down button to move the cursor, press the A button to select the hack you want to activate and vice versa.
-- Press Select to turn on debug mode, when debug mode is turned on, it will automatically turn on noclip accuracy too!
-- If a hack is Green, it is allowed for completion and will not be flagged by the cheat indicator dot.
-- If a hack is Red, it is not allowed for completion and will be flagged by the cheat indicator dot unless you disable the hack and reset player (by dying or exiting the level).
-----------------------
-- Current hacks include: Clicks HUD, Input Test, Random Gamemode, Editable Text, Path Overlay, Ship Copter.
-- Cheat Indicator included and is always on.
-- Searching included and is always on.
-- Completion message is included and is always on.
-- Noclip accuracy included and will be turned on when debug mode is on.
-----------------------
-- Information for hacks:
-- Noclip accuracy (By Aaron Chen-Chang and wilfredlam0418): When debug mode is on, if you died to spikes and ignored death, your accuracy of playing the level goes down, fun to play with.
-- Cheat indicator (By Aaron Chen-Chang): Will turn red when detected cheats that aren't allowed and rewinding.
-- Clicks HUD (By Aaron Chen-Chang): Shows your total clicks and Clicks Per Second (CPS) during a level once turned on, if your CPS is 0, the background color for CPS will be black, 1~5 will be green, 6~10 will be yellow, >10 will be red, when you are pressing or holding the A button or the Up button, the "A button" or the "Up button" text and the total clicks will turn green.
-- Input test (By Aaron Chen-Chang): Shows your inputs with a green background once turned on, this includes all possible inputs from controller 1.
-- Random Gamemode (By Aaron Chen-Chang): Randomizes your gamemode from gamemodes 1-11 everytime you enter a portal or enter a level once turned on.
-- Editable Text (By Aaron Chen-Chang): Edit your text to anything you want below, and it will show on screen once turned on.
-- Path Overlay (By Kando Wontu): Shows the path you have taken by drawing a line trail down once turned on, if you click, the line gets thicker and vice versa.
-- Ship Copter (By wilfredlam0418): Makes the swing gamemode behave like the ship once turned on.
-- Search (By wilfredlam0418): Allows searching in level select screen, press / to start typing, press up or down after typing to select level, press enter to choose level, press left to delete characters. 
-- Dark Mode (By Aaron Chen-Chang): Makes the whole screen less bright.
-----------------------
-- Main Contributors:
-- Aaron Chen-Chang
-- wilfredlam
-- Kando Wontu
-----------------------
-- Special Thanks:
-- Azulamazigh
-- absolute
-- Mesen
-- Lua scripting
-- The Famidash and Geometry dash community
-----------------------
-- For more questions, DM: aaronchenchang on Discord
-----------------------
-- Update log:
-- v1.0 - Added mod menu
-- Added - Clicks HUD, Input Test, Random Gamemode
-- v1.1 - Added cheat indicator
-- Added - Editable Text, path overlay
-- V1.11
-- Fixed cheat indicator to make it so that it also checks for activating debug mode by pressing the Select button during a level.
-- Added - Ship Copter
-- Changed text format for mod menu from "MOD MENU" to "Megahack vX.XXX Mod Menu".
-- V1.12
-- Added more information for the hacks included and for this hack and made them more clear.
-- Reverted back to V1.11's engine to fix Ship Copter.
-- Did a whole workaround with the script to fix cheat dot again cus it keeps failing and failing I almost gave up.
-- V1.13
-- Fixed Cheat Indicator again so that it only resets when you start a level either by dying or exiting and coming back. (So that the cheat indicator will show red or green on end screen instead of getting reseted on the end screen to green every time)
-- Fixed Path overlay to match the current version of it.
-- V1.14
-- Made Cheat Indicator detect rewinding.
-- Changed from pressing right or left to open or close to pressing B to open of close the menu because platformer mode breaks with right and left.
-- Change it from pressing the B button to pressing the start button to close or open, because of practice mode activation closing the pause menu, pressing B will close menu no matter what. So if your menu opens while moving in the level, just press B to close it.
-- Added instructions on how to use this hack.
-- Made it so that pressing select also closes the menu due toexiting the level making the menu appear being annoying.
-- Fixed Rewind cheat indicator from accidentally making Clicks HUD count as a red hack even though it isn't.
-- Fixed Completion restart button breaking menu.
-- V1.15
-- Added Completion message.
-- Added A LOT more completion messages.
-- Fixed completion message overflowing.
-- Added GD completion messages
-- V1.16
-- Added Search, a hack that lets you search for the levels.
-- V1.17
-- Added an intro.
-- Made cheat indicator detect save states.
-- Fixed bug where having Clicks HUD on won't reset cheat dot when you use save states.
-- Fixed the debug mode detection from detecting select to detecting actual debug mode being active.
-- V1.18
-- ADDED NOCLIP ACCURACY!
-- Made it so that Mod menu opens on pausing instead of opening on pressing start.
-- Added "deaths" to noclip accuracy
-- Added Dark Mode, made cheat indicator appear on the left bottom.
-- Made Cheat indicator show reasoning as to why it was red.
-- Made everything more compact, made it so that everytime you click, it shows on the right side of the screen.
-----------------------

local editableMessage = "Best runs: 69%, 23-82%, 36-100%" -- edit this text with anything you want
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
local rewindDetected = false
local lastFrame = nil
local prevInLevel = false
local search_key = "/"
local backspace_key = "Left Arrow"
local confirm_key = "Enter"
local suggestion_up_key = "Up Arrow"
local suggestion_down_key = "Down Arrow"
local level_names = {[0] = ""}
local recording_names = true
local recording_frame = -1000
local last_level = -1
local character_tiles = "???????????????.????????????????????????????????0123456789?ABCDEFGHIJKLMNOPQRSTU???????????VWXYZ?????????????????????????????? ?"
local space = false
local searching = false
local usable_keys = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ. "
local key_pressed = false
local query = ""
local suggestions = {}
local color = 12632256
local chosen_suggestion = 1
local press_right = false
local search_held = false
local backspace_held = false
local confirm_held = false
local suggestion_up_held = false
local rewindDetected = false
local noclipFrames = 0
local totalFrames = 0
local reasons = ""

local function AddReason(reason)

    if not string.find(reasons, reason, 1, true) then
        reasons = reasons .. reason .. " "
    end

end
local inputParticles = {}

-- text should not be longer than this message
local winTexts = {
    "you can't beat deadlocked? Git gud",
    "famidash retray 100% 3 coins",
    "ok now do it again i didn't see",
    "amazing... or is it actually?",
    "haxxor",
    "i didn't see the hacking client dw",
    "impressive",
    "ggs",
    "nice swag route",
    "i told you you would beat it this time",
    "hacker client detected!?!?",
    "is the cheat indicator green or nah",
    "i predict the cheat dot to be green",
    "i predict the cheat dot to be red",
    "editable text", -- not meant for you to edit if you see this
    "um, do i have to save the file?",
    "port it to the nes",
    "test4 my beloved",
    "800 TRIGGERS. 1/64",
    "Top player friendly!",
    "and... 100%!",
    "you cheated this did you?",
    "lucky...",
    "is it just me or...",
    "i predict... 4 coins??",
    "I PREDICT... 3 COINS??",
    "I PREDICT... 2 COINS??",
    "I PREDICT... 1 COIN??",
    "I PREDICT... 0 COINS??",
    "yayy",
    "*blank",
    "dw i saw the completion",
    "adding to the list... unsuccessful",
    "Well done... now beat it on the NES",
    "Well done... now beat it on the Famicom",
    "Not 1 attempt :(",
    "WHERE ARE THEY - Colon",
    "WHY - Colon",
    "CBF detected loser!",
    "Good, now beat it with eyes closed",
    "Hacked, level is clearly impossible.",
    "You cannot verify, has start position",
    "collect all coins in the level pls",
    "We really doing anything now - Colon",
    "You beat this instead of Madness…",
    "You beat this instead of ReTray...",
    "Noclip Accuracy: 100.67%",
    "i have no words... oh wait",
    "I lied you got 99%",
    "Now beat it in normal mode to verify it",
    "Did you beat this in GD?",
    "Auto Safe Mode cheat detected?",
    "easy i can do it with my eyes closed",
    "is this a new top 1?",
    "Noclipped through the end wall",
    "!enod llew",
    "!evisserpmi",
    "ya proshol penumbrol",
    "omg omg omg omg omg omg omg omg",
    "two top 1s in one day bro",
    "oh my god! *breaths heavily",
    "*breaths heavily",
    "milestone for the Famidash community",
    "I am shocked",
    "I approve of this completion",
    "No recording? suspicious",
    "my hardest is famidash retray dw",
    "famidash getting intense!",
    "hi 41% surpassed",
    "sonic wave mefewe version 98% surpassed",
    "phobos 92% surpassed",
    "i have same chance to show with others",
    "Did you pray to the slope gods?",
    "GG! :D",
    "what a very easy level",
    "Did you see the end wall?",
    "At 100% speed, look possible to you?",
    "Good. Now beat it at 200% speed.",
    "we beat this level together right?",
    "idea block for more things to add",
    "one step closer to beating new hardest?",
    "insert non-chalant reaction here",
    "At 200% speed, impossible to you?",
    "impossibru!",
    "i can't think of anything to say",
    "how many attempts?",
    "it going fast to 2x speed",
    "it going fast to 3x speed",
    "it going fast to 4x speed",
    "it going fast to 10x speed",
    "it going fast to 20x speed",
    "w speed",
    "have you done that essay homework yet?",
    "search elbillug for good compliment",
    "you clearly cheated, didn't you?",
    "whos this anonymous guy in the doc",
    "i bet you never seen this message before",
    "GGGGGGGGGGGGGGGGGGGGGGGGG",
    "who is this guy?",
    "Everything leads to death",
    "Teamwork makes the dream worse",
-- GD win messages
-- text should not be longer than this message
    "Level and Coins Verified!",
    "Level Verified!",
    "Awesome!",
    "Good Job!",
    "Well Done!",
    "Impressive!",
    "Amazing!",
    "Incredible!",
    "Skillful!",
    "Warp Speed!",
    "Y u do dis?",
    "I R Impressed!",
    "Took you long enough...",
    "Teach me oh great one",
    "Haxxor?",
    "Tripple spikes?",
    "RubRubRubRubRubRub",
    "Brilliant!",
    "You are... The One!",
    "How is this possible!?",
    "You beat me...",
    "Challenge Breaker!",
    "I am speechless...",
    "Reflex Master!",
    "Not bad!",
    "AFK",
    "he protec",
    "Kappa",
    "lol is lol backwards",
    "Dr. Click",
    "Speedrun complete",
    "YEEEEEEEEEEEEEEEEEEES!",
    "Why are we here, just to suffer?",
    "SO FAST",
    "Hmmmmmmmmmmm",
    "Ship part was cool",
    "Timing could be better",
    "I cant hear the music.",
    "Pump. It. Up.",
    "I am Batman",
    "Take a break.",
    "E",
    "Nice song",
    "QUACK",
    "OMG Poggers",
    "pogchamp",
    "That's Sus",
    "BASED",
    "Fluked",
    "HOW!?",
    "Task failed successfully",
    "ok boomling",
    "I am not not impressed",
    "You are inevitable",
    "Sorry I fell asleep. Do it again?",
    "Did we win?",
    "Big brain moment",
    "Some doubted... it happened",
    "Press alt + f4 for secret way",
    "Are ya winning son?",
    "el pepe",
    "LET'S ROCK IT!",
    "You're cheating aren't you?",
    "That doesnt count",
    "RubRub Approves",
    "NOICE",
    "You were not the Impostor",
    "I have the highground",
    "You got the W",
    "After a mental breakdown",
    "Not 1 attempt but ok",
    "Cool, now beat it with your eyes closed",
    "Never Gonna Give You Up",
    "You popped off fr.",
    "EMERGENCY MEETING!!!",
    "L",
    "huhu you have winned",
    "We're making balls ladies and gentleman",
    "why am I argentina",
    "You are fuk map",
    "Robert Game",
    "You can now play as Luigi!",
    "these nuts",
    "What the BEEP was that?",
    "do it again I wasn't looking",
    "youre going to brazil",
    "Don't forget to thank the bus driver",
    "I can't believe you've done this",
    "Update 1.3.0 coming soon",
    "She's in love with the concept...",
    "RobTop said funny messages, not cringe",
    "You're a pro? Name every Demon then",
    "poggie woggie",
    "Well yes, but actually no.",
    "I like ya cut G",
    "HOW",
    "Not impressive I beat that 2 seconds",
    "Does anyone read this?",
    "Uh oh, forgot to record",
    "Boy that's cap",
    "Time to go outside",
    "F in the chat",
    "Have you just... DASHED it???",
    "Why am I spending time on these messages",
    "Harder than FNF",
    "BUT BRO, DO YOU EVEN LIFT!?",
    "Ratio",
    "DROP THE BEAT",
    "Robala Topala approves",
    "Ropert Topert disapproves",
    "Never before have I seen such skill",
    "Listen here you little...",
    "kinda sloppy but ok u win",
    "This is why you have no friends",
    "BEHOLD, an endscreen comment!",
    "To be continued"
}
local currentWinText = ""
local winTextTimer = 0
local winTextDelay = 0
local introActive = true
local introText =
    "Famidash Megahack V1.185\n" ..
    "By Aaron Chen-Chang and more"

local introChars = 0
local blinkTimer = 0
local function DrawInputParticles()

    local input = emu.getInput(0)

    if input.up and not prevUp then
        table.insert(inputParticles, {
            text = "U",
            x = 244,
            y = 220
        })
    end

    if input.a and not prevA then
        table.insert(inputParticles, {
            text = "A",
            x = 250,
            y = 220
        })
    end

    for i = #inputParticles, 1, -1 do
        local p = inputParticles[i]

        emu.drawString(
            p.x,
            p.y,
            p.text,
            GREEN,
            BLACK
        )

        p.y = p.y - 9

        if p.y < -10 then
            table.remove(inputParticles, i)
        end
    end
end
-- =========================
-- MENU SYSTEM
-- =========================

local menuOpen = false
local selected = 1

local prevRight = false
local prevLeft = false
local prevA = false
local prevB = false
local prevStart = false
local prevUp = false
local prevDown = false

local options = {
    "Clicks HUD",
    "Input Test",
    "Random Gamemode",
    "Editable Text",
    "Path Overlay",
    "Ship Copter",
    "Dark Mode"
}

local enabled = { false, false, false, false, false, false, false }

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
local prevPlayerX_ClickHUD = nil

local function resetAll()
    totalClicks = 0
    clickTimes = {}
    frameCounter = 0
    noclipFrames = 0
    totalFrames = 0
    prevA_click = false
    prevUp_click = false

    cheatUsedThisAttempt = false
    reasons = ""
    rewindDetected = false
end

local function ClicksHUD()

    local M = emu.memType.nesMemory
    local gameState = emu.read(ADDR_GAMESTATE, M) or 0

    if gameState ~= STATE_GAME then return end

    local rawX = emu.read16(ADDR_PLAYER_X, M) or 0
    local playerX = rawX >> 8

    if prevPlayerX_ClickHUD ~= nil and playerX < prevPlayerX_ClickHUD - 20 then
        resetAll()
    end

    prevPlayerX_ClickHUD = playerX

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

    local cps = #clickTimes

    local cpsColor
    if cps == 0 then
        cpsColor = 0x80000000
    elseif cps <= 5 then
        cpsColor = 0x8000FF00
    elseif cps <= 10 then
        cpsColor = 0x80FFFF00
    else
        cpsColor = 0x80FF0000
    end

    emu.drawString(10, 10, "Total Clicks: " .. totalClicks, WHITE, (aDown or upDown) and GREEN or BLACK)
    emu.drawString(10, 19, "A Button", WHITE, aDown and GREEN or BLACK)
    emu.drawString(10, 28, "Up Button", WHITE, upDown and GREEN or BLACK)
    emu.drawString(10, 37, "CPS: " .. cps, WHITE, cpsColor)
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
            y = y + 9
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
        AddReason(" Redcheat,")
        cheatUsedThisAttempt = true

        emu.displayMessage(
            "Megahack",
            "#" .. newMode .. " - " .. (modeNames[newMode] or "Unknown")
        )

        lastGamemode = newMode
        inTransition = false
    else
        lastGamemode = gamemode
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
    AddReason(" Redcheat,")
end

-- =========================
-- MENU
-- =========================

local function drawMenu()

    emu.drawString(10, 10, "Megahack v1.185 Mod menu")

    for i = 1, #options do

        local name = options[i]
        local state = enabled[i] and "ON" or "OFF"

        local color = (i == 3 or i == 6) and RED or GREEN
        local display = name .. " [" .. state .. "]"

        if i == selected then
            emu.drawString(10, 30 + i * 9, "> " .. display, color, BLACK)
        else
            emu.drawString(20, 30 + i * 9, display, color, BLACK)
        end
    end
end

-- =========================
-- CHEAT DOT 
-- =========================
local prevPlayerX_CheatDot = nil
local function DrawCheatDot()

    local M = emu.memType.nesMemory
    local gameState = emu.read(ADDR_GAMESTATE, M) or 0

    local rawX = emu.read16(ADDR_PLAYER_X, M) or 0
    local playerX = rawX >> 8

local inLevel = (gameState == STATE_GAME)

local input = emu.getInput(0)

if prevInLevel and not inLevel and not input.select then
    currentWinText = winTexts[math.random(#winTexts)]
    winTextDelay = 130
    winTextTimer = 0
end

prevInLevel = inLevel

    local redActive = enabled[3] or enabled[6]

    local died = false
    if prevPlayerX_CheatDot ~= nil and playerX < prevPlayerX_CheatDot - 20 then
        died = true
        totalFrames = 0
        noclipFrames = 0
    end
    
if died and not redActive then
    cheatUsedThisAttempt = false
    reasons = ""
    rewindDetected = false
    savestateDetected = false
end

    if redActive and inLevel then
        cheatUsedThisAttempt = true
    end

    prevPlayerX_CheatDot = playerX

local color =
    (cheatUsedThisAttempt or rewindDetected or redActive or savestateDetected)
    and RED or GREEN
    emu.drawString(0, 232, "O", color, color)
    if reasons ~= "" then
    emu.drawString(10, 232, reasons, WHITE, BLACK)
end
end

-- =========================
-- SEARCH
-- =========================

function search()
	if emu.read(1180, emu.memType.nesMemory, false) == 6 then
		if recording_names then -- Record level names
			emu.drawRectangle(-256, -256, 768, 768, 0, true)
			emu.drawString(20, 128, "Currently recording the names of the levels.")
			if recording_frame >= -999 then
				if recording_frame >= 0 then
					if recording_frame % 2 == 0 then
						emu.setInput({up = false, down = false, right = true, left = false, a = false, b = false, start = false, select = false}, 0)
					else
						emu.setInput({up = false, down = false, right = false, left = false, a = false, b = false, start = false, select = false}, 0)
						space = false
						if emu.read(1796, emu.memType.nesMemory, false) == 254 then
							for i = 1795, 1811 do
								if emu.read(i, emu.memType.nesMemory, false) == 254 then
									if #level_names[#level_names] > 0 then
										space = true
									end
								else
									if space then
										level_names[#level_names] = level_names[#level_names] .. " "
										space = false
									end
									level_names[#level_names] = level_names[#level_names] .. character_tiles:sub(emu.read(i, emu.memType.nesMemory, false) - 127, emu.read(i, emu.memType.nesMemory, false) - 127)
								end
							end
							space = true
							for i = 1815, 1831 do
								if emu.read(i, emu.memType.nesMemory, false) == 254 then
									if #level_names[#level_names] > 0 then
										space = true
									end
								else
									if space then
										level_names[#level_names] = level_names[#level_names] .. " "
										space = false
									end
									level_names[#level_names] = level_names[#level_names] .. character_tiles:sub(emu.read(i, emu.memType.nesMemory, false) - 127, emu.read(i, emu.memType.nesMemory, false) - 127)
								end
							end
						else
							for i = 1799, 1815 do
								if emu.read(i, emu.memType.nesMemory, false) == 254 then
									if #level_names[#level_names] > 0 then
										space = true
									end
								else
									if space then
										level_names[#level_names] = level_names[#level_names] .. " "
										space = false
									end
									level_names[#level_names] = level_names[#level_names] .. character_tiles:sub(emu.read(i, emu.memType.nesMemory, false) - 127, emu.read(i, emu.memType.nesMemory, false) - 127)
								end
							end
						end
						if last_level > emu.read(1151, emu.memType.nesMemory, false) then
							recording_names = false
							level_names[#level_names] = nil
						else
							level_names[#level_names + 1] = ""
							last_level = emu.read(1151, emu.memType.nesMemory, false)
						end
					end
				elseif recording_frame == -1 then
					emu.write(1151, 255, emu.memType.nesMemory)
				end
				recording_frame = recording_frame + 1
			else
				level_names = {[0] = ""}
				recording_frame = -20
				last_level = -1
			end
		else
			if press_right then
				emu.setInput({up = false, down = false, right = true, left = false, a = false, b = false, start = false, select = false}, 0)
				press_right = false
			end
			if emu.read(1151, emu.memType.nesMemory, false) == 0 then
				emu.setInput({left = false})
			end
			if emu.isKeyPressed(search_key) then
				if not search_held then
					searching = not searching
					search_held = true
					query = ""
					key_pressed = "11111111111111111111111111111111111111"
					chosen_suggestion = 1
				end
			else
				search_held = false
			end
			if searching then
				suggestions = {}
				for i = 0, #level_names do
					if level_names[i]:sub(1, #query) == query then
						suggestions[#suggestions + 1] = i
					end
				end
				emu.drawRectangle(0, 0, 256, 256, 2147483648, true)
				emu.drawString(0, 192, query)
				for i, v in ipairs(suggestions) do
					if i == chosen_suggestion then
						color = 16777215
					else
						color = 12632256
					end
					emu.drawString(0, 183 - 9 * (#suggestions - i), level_names[v], color)
				end
				for i = 1, #usable_keys do
					if usable_keys:sub(i, i) == " " then
						if emu.isKeyPressed("Space") then
							if key_pressed:sub(i, i) == "0" then
								query = query .. " "
							end
							key_pressed = key_pressed:sub(1, i - 1) .. 1 .. key_pressed:sub(i + 1)
							chosen_suggestion = 1
						else
							key_pressed = key_pressed:sub(1, i - 1) .. 0 .. key_pressed:sub(i + 1)
						end
					else
						if emu.isKeyPressed(usable_keys:sub(i, i)) then
							if key_pressed:sub(i, i) == "0" then
								query = query .. usable_keys:sub(i, i)
							end
							key_pressed = key_pressed:sub(1, i - 1) .. 1 .. key_pressed:sub(i + 1)
							chosen_suggestion = 1
						else
							key_pressed = key_pressed:sub(1, i - 1) .. 0 .. key_pressed:sub(i + 1)
						end
					end
				end
				if emu.isKeyPressed(backspace_key) then
					if not backspace_held then
						query = query:sub(1, #query - 1)
					end
					backspace_held = true
				else
					backspace_held = false
				end
			end
			if emu.isKeyPressed(suggestion_up_key) then
				if not suggestion_up_held then
					suggestion_up_held = true
					chosen_suggestion = chosen_suggestion - 1
					if chosen_suggestion < 1 then
						chosen_suggestion = #suggestions
					end
				end
			else
				suggestion_up_held = false
			end
			if emu.isKeyPressed(suggestion_down_key) then
				if not suggestion_down_held then
					suggestion_down_held = true
					chosen_suggestion = chosen_suggestion + 1
					if chosen_suggestion > #suggestions then
						chosen_suggestion = 1
					end
				end
			else
				suggestion_down_held = false
			end
			if emu.isKeyPressed(confirm_key) then
				if searching or confirm_held then
					confirm_held = true
				end
				if #suggestions > 0 then
					if searching then
						emu.write(1151, (suggestions[chosen_suggestion] - 1) % 256, emu.memType.nesMemory)
					end
					press_right = true
					searching = false
				end
			else
				confirm_held = false
			end
			if searching or search_held or backspace_held or confirm_held or suggestion_up_held or suggestion_down_held then
				emu.setInput({up = false, down = false, right = false, left = false, a = false, b = false, start = false, select = false}, 0)
			end
		end
	else
		recording_names = true
		recording_frame = -1000
	end
end
-- =========================
-- Dark Mode
-- =========================
local function darkmode()

    if not enabled[7] then
        return
    end

    emu.drawRectangle(
        -256,
        -256,
        768,
        768,
        0x88000000,
        true
    )
end
-- =========================
-- Intro
-- =========================

local rainbowFrame = 0

local function HSVtoRGB(h)

    local c = 255
    local x = math.floor((1 - math.abs((h / 60) % 2 - 1)) * 255)

    local r,g,b = 0,0,0

    if h < 60 then
        r,g,b = 255,x,0
    elseif h < 120 then
        r,g,b = x,255,0
    elseif h < 180 then
        r,g,b = 0,255,x
    elseif h < 240 then
        r,g,b = 0,x,255
    elseif h < 300 then
        r,g,b = x,0,255
    else
        r,g,b = 255,0,x
    end

    return r * 65536 + g * 256 + b
end

local function DrawIntro()


rainbowFrame = rainbowFrame + 4
if rainbowFrame >= 360 then
    rainbowFrame = rainbowFrame - 360
end

local rainbowColor = HSVtoRGB(rainbowFrame)

    emu.drawRectangle(-256, -256, 768, 768, 0, true)

    if introChars < #introText then
        introChars = introChars + 1
    end

    local visibleText = introText:sub(1, introChars)

local title = "Famidash Megahack V1.185"
local author = "By Aaron Chen-Chang and more"

emu.drawString(10, 10, title, rainbowColor)
emu.drawString(10, 19, author, 0xFFFFFF)

emu.drawString(10, 39, "Description:")

emu.drawString(10, 48, "Made to enhance your gameplay of Famidash.")

emu.drawString(10, 57, "Pause in a level to open the mod menu.")
emu.drawString(10, 66, "Unpause to close the mod menu.")

emu.drawString(10, 75, "Press UP/DOWN to select hacks in mod menu.")
emu.drawString(10, 84, "Press A to activate or toggle hacks in mod menu.")

emu.drawString(10, 94, "Press / in level select screen to search")
emu.drawString(10, 103, "Search using keyboard, backspace is left button.")
emu.drawString(10, 112, "Press up or down to find levels you want.")
emu.drawString(10, 121, "Press Enter to confirm, press / to stop searching.")

emu.drawString(10, 130, "When you press up or A, it will show on screen.")

emu.drawString(10, 139, "Noclip accuracy will be with debug mode autoly.")
emu.drawString(10, 153, "For more questions, DM: aaronchenchang on Discord.")

emu.drawString(10, 162, "Enjoy!")



    if introChars >= #introText then

        blinkTimer = blinkTimer + 1

        if math.floor(blinkTimer / 30) % 2 == 0 then
            emu.drawString(
                10,
                210,
                "Press ANY BUTTONS to continue..."
            )
        end

        local input = emu.getInput(0)
local realInput = emu.getInput(0)

if realInput.start or realInput.a or realInput.b or realInput.select or realInput.up or realInput.down or realInput.left or realInput.right then
    introActive = false
end
    end
    emu.setInput({
        up=false,
        down=false,
        left=false,
        right=false,
        a=false,
        b=false,
        start=false,
        select=false
    },0)
end

-- =========================
-- MAIN LOOP
-- =========================

function Main()
DrawInputParticles()
if emu.read(107, emu.memType.nesMemory, false) < 16 and emu.read(1435, emu.memType.nesMemory, false) == 1 then
  emu.write(111, 0, emu.memType.nesMemory)
  emu.write(112, 0, emu.memType.nesMemory)
end

if introActive then
    DrawIntro()
    return
end

    local M = emu.memType.nesMemory
    local gameState = emu.read(ADDR_GAMESTATE, M) or 0
    local inLevel = (gameState == STATE_GAME)

    local input = emu.getInput(0)

local currentFrame = emu.getState()["frameCount"]

if lastFrame ~= nil then
    if currentFrame < lastFrame then
        rewindDetected = true
        AddReason(" Rewinded,")
        cheatUsedThisAttempt = true
    end
end

lastFrame = currentFrame

if inLevel then
    if emu.read(1435, emu.memType.nesMemory, false) == 1 then
        cheatUsedThisAttempt = true
        AddReason(" Debug Mode,")
    end
end

local pauseFlag =
    emu.read(0x05BB, emu.memType.nesMemory, false)

menuOpen =
    emu.read(0x05BB, emu.memType.nesMemory, false) == 1

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
    darkmode()

local debugMode =
    emu.read(1435, emu.memType.nesMemory, false) == 1

if inLevel and not menuOpen then
    totalFrames = totalFrames + 1

    if debugMode then
        local cubeData =
            emu.read(0x007B, emu.memType.nesMemory, false)

        if cubeData == 3 or cubeData == 1 then 
            noclipFrames = noclipFrames + 1
        end
    end
end

local noclipAcc = 100

if totalFrames > 0 then
    noclipAcc =
        ((totalFrames - noclipFrames)
        / totalFrames) * 100
end

if debugMode then
    emu.drawString(
        10,
        210,
        string.format(
            "Noclip Accuracy: %.2f%%",
            noclipAcc
        )
    )
     emu.drawString(
     10,
     220,
     "deaths:  "
     )
     emu.drawString(
     50,
     220,
     noclipFrames
     )
end

if winTextDelay > 0 then
    winTextDelay = winTextDelay - 1

    if winTextDelay == 0 then
        winTextTimer = 999999
    end
end

if winTextTimer > 0 then

    local textColor = GREEN

    if cheatUsedThisAttempt or rewindDetected or enabled[3] or enabled[6] then
        textColor = RED
    end

    emu.drawString(30, 165, currentWinText, textColor, BLACK)
end

if input.start and not prevStart then
    winTextTimer = 0
    winTextDelay = 0
end

prevRight = input.right
prevLeft = input.left
prevA = input.a
prevB = input.b
prevStart = input.start
prevUp = input.up
prevDown = input.down
prevSelect = input.select
end

local doReset = true

local function ResetOnLoad()
    if doReset then
        doReset = false
        emu.reset()
    end
end
local function OnStateLoaded()

    savestateDetected = true
    AddReason(" SaveState,")
    cheatUsedThisAttempt = true

end


emu.addEventCallback(OnStateLoaded, emu.eventType.stateLoaded)
emu.addEventCallback(ResetOnLoad, emu.eventType.endFrame)
emu.addEventCallback(Main, emu.eventType.endFrame)
emu.addEventCallback(ShipCopter, emu.eventType.inputPolled)
emu.addEventCallback(search, emu.eventType.inputPolled)
emu.displayMessage("System", "Famidash Megahack v1.185 Loaded")