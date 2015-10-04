dofile("lua_scripts/state_default_ui.lua")

local itemSize = 60

local function genConfirmationBarItemPos()
  return genItemPos(window_width - 2 * itemSize, window_height - 2 * itemSize, itemSize, 0, 1, 1, false)
end

local buttonPosX,buttonPosY = genConfirmationBarItemPos()
if button(buttonPosX ,buttonPosY, itemSize, itemSize, "Confirm", "button_confirm.png") then
  deleteLinesDone()
end
