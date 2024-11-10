local consoleType = emu.getState()["consoleType"]
if consoleType ~= "Nes" then
  emu.displayMessage("Script", "This script only works on the NES.")
  return
end

function Main()
  playerxaddr = emu.getLabelAddress("_player_x")
  playeryaddr = emu.getLabelAddress("_player_y")
  
  playerminiaddr = emu.getLabelAddress("_mini")

  player_x = emu.read(playerxaddr.address + 1, playerxaddr.memType, false)
  player_y = emu.read(playeryaddr.address + 1, playeryaddr.memType, false)
  
  player_mini = emu.read(playerminiaddr.address, playerminiaddr.memType, false)

  if player_mini > 0 then
    player_width = 8
    player_height = 8
  else 
    player_width = 15
    player_height = 15
  end

  emu.drawRectangle(player_x, player_y, player_width, player_height, 0xffff00, false)

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

  for i=0,16 do
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
      end
    end
  end
end
emu.addEventCallback(Main, emu.eventType.startFrame)
