local consoleType = emu.getState()["consoleType"]
if consoleType ~= "Nes" then
  emu.displayMessage("Script", "This script only works on the NES.")
  return
end

function Main()

  gamestateaddr = emu.getLabelAddress("_gameState")

  gamestate = emu.read(gamestateaddr.address, gamestateaddr.memType, false)

  if gamestate ~= 0x02 then
    return
  end


  dualaddr = emu.getLabelAddress("_dual")
  dual = emu.read(dualaddr.address, dualaddr.memType, false)

  playerxaddr = emu.getLabelAddress("_player_x")
  playeryaddr = emu.getLabelAddress("_player_y")

  genericaddr = emu.getLabelAddress("_Generic")
  
  playerminiaddr = emu.getLabelAddress("_player_mini")

  gamemodeaddr = emu.getLabelAddress("_player_mini")

  player_x = emu.read(playerxaddr.address + 1, playerxaddr.memType, false)
  player_y = emu.read(playeryaddr.address + 1, playeryaddr.memType, false)
  
  player_mini = emu.read(playerminiaddr.address, playerminiaddr.memType, false)

  gamemode = emu.read(gamemodeaddr.address, gamemodeaddr.memType, false)

  player_width = emu.read(genericaddr.address + 2, genericaddr.memType, false)
  player_height = emu.read(genericaddr.address + 3, genericaddr.memType, false)

  emu.drawRectangle(player_x, player_y + ((0x10 - player_height) >> 1), player_width, player_height, 0xffff00, false)

  if dual == 1 then
    player_x = emu.read(playerxaddr.address + 3, playerxaddr.memType, false)
    player_y = emu.read(playeryaddr.address + 3, playeryaddr.memType, false)

    emu.drawRectangle(player_x, player_y + ((0x10 - player_height) >> 1), player_width, player_height, 0xffff00, false)
  end 

  actives = emu.getLabelAddress("_activesprites_active")
  
  types = emu.getLabelAddress("_activesprites_type")

  widths = emu.getLabelAddress("_sprite_widths")
  heights = emu.getLabelAddress("_sprite_heights")
  
  offsetsx = emu.getLabelAddress("_sprite_x_offset")
  offsetsy = emu.getLabelAddress("_sprite_y_offset")

  xs = emu.getLabelAddress("_activesprites_realx")
  ys = emu.getLabelAddress("_activesprites_realy")

  scrollxtable = emu.getLabelAddress("_scroll_x")
  scrollytable = emu.getLabelAddress("_scroll_y")

  for i=0,15 do
    sprActive = emu.read(actives.address + i, actives.memType, false)
    if sprActive > 0 then
      sprType = emu.read(types.address + i, types.memType, false)

      width = emu.read(widths.address + sprType, widths.memType, false)
      height = emu.read(heights.address + sprType, heights.memType, false)

      x = emu.read(xs.address + i, xs.memType, false)
      xoffset = emu.read(offsetsx.address + sprType, offsetsx.memType, true)

      y = emu.read(ys.address + i, ys.memType, false)
      yoffset = emu.read(offsetsy.address + sprType, offsetsy.memType, true)

      if height < 0xfc then 
        emu.drawRectangle(x + xoffset, y + yoffset, width, height, 0x7f0000ff, true)
      else
        emu.drawRectangle(x + xoffset, y + yoffset, 16, 16, 0x7fffffff, true)
      end
    end
  end
end
emu.addEventCallback(Main, emu.eventType.startFrame)
