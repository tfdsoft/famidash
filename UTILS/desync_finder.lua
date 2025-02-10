--This is an example Lua (https://www.lua.org) script to give a general idea of how to build scripts
--Press F5 or click the Run button to execute it
--Type "emu." to show a list of all available API function

function printInfo()
    playeryaddr = emu.getLabelAddress("_player_y")

    player_y_1 = emu.read(playeryaddr.address + 1, playeryaddr.memType, false)
    player_y_2 = emu.read(playeryaddr.address + 3, playeryaddr.memType, false)
    middle = math.floor((player_y_1 + player_y_2) / 2)

    if (middle ~= 96) then
        emu.drawString(11, 220, "DESYNC DETECTED", 0xFFFFFF, 0xFF000000)
    end

    emu.drawString(11, 20, middle, 0xFFFFFF, 0xFF000000)

    emu.drawRectangle(0, player_y_1, 256, 1, 0x7fffff00, false)
    emu.drawRectangle(0, player_y_2, 256, 1, 0x7fffff00, false)
    
    emu.drawRectangle(0, middle, 256, 1, 0x7fff0000, false)
    
  end
  
  --Register some code (printInfo function) that will be run at the end of each frame
  emu.addEventCallback(printInfo, emu.eventType.endFrame);
  
  --Display a startup message
  emu.displayMessage("Script", "Desync Finder script loaded.")