dofile("lua_scripts/state_default_ui.lua")

local itemSize = 60 * backingRatioX
local itemMargin = 10 * backingRatioX
local function genOrientationBarItemPos(idx)
  return genItemPos(window_width / 2, window_height - 2 * itemSize, itemSize, itemMargin, 2, idx, false)
end

local function genConfirmationBarItemPos(idx)
  return genItemPos(window_width - 2 * itemSize, window_height - 2 * itemSize, itemSize, itemMargin, 2, idx, false)
end

local buttonPosX,buttonPosY = genOrientationBarItemPos(1)
if button(buttonPosX ,buttonPosY, itemSize, itemSize, "Select Vertical Plane", "button_vertical.png") then
  selectVerticalPlane()
end

local buttonPosX,buttonPosY = genOrientationBarItemPos(2)
if button(buttonPosX ,buttonPosY, itemSize, itemSize, "Select Horizontal Plane", "button_horizontal.png") then
  selectHorizontalPlane()
end

local buttonPosX,buttonPosY = genConfirmationBarItemPos(1)
if button(buttonPosX ,buttonPosY, itemSize, itemSize, "Confirm", "button_confirm.png") then
  confirmPlaneSelection()
end

local buttonPosX,buttonPosY = genConfirmationBarItemPos(2)
if button(buttonPosX ,buttonPosY, itemSize, itemSize, "Cancel", "button_cancel.png") then
  cancelPlaneSelection()
end
