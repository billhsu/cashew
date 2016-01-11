dofile("lua_scripts/state_default_ui.lua")

local itemSize = 60 * backingRatioX
local itemMargin = 10 * backingRatioX

local function genConfirmationBarItemPos()
  return genItemPos(window_width - 2 * itemSize, window_height - 2 * itemSize, itemSize, 0, 1, 1, false)
end

local function genMirrorBarItemPos(idx)
  return genItemPos(window_width / 2 , window_height/2, itemSize, itemMargin, 3, idx, false)
end

local buttonPosX,buttonPosY = genMirrorBarItemPos(1)
if checkbox(buttonPosX ,buttonPosY, itemSize, itemSize, "Mirror X axis", mirrorXStatus, "x_axis.png") then
  mirrorXAxis(mirrorXStatus.checked)
end

local buttonPosX,buttonPosY = genMirrorBarItemPos(2)
if checkbox(buttonPosX ,buttonPosY, itemSize, itemSize, "Mirror Y axis", mirrorYStatus, "y_axis.png") then
  mirrorYAxis(mirrorYStatus.checked)
end

local buttonPosX,buttonPosY = genMirrorBarItemPos(3)
if checkbox(buttonPosX ,buttonPosY, itemSize, itemSize, "Mirror Z axis", mirrorZStatus, "z_axis.png") then
  mirrorZAxis(mirrorZStatus.checked)
end

local buttonPosX,buttonPosY = genConfirmationBarItemPos()
if button(buttonPosX ,buttonPosY, itemSize, itemSize, "Confirm", "button_confirm.png") then
  mirrorAxisSelectionDone()
end

showStateLabel("Mirror Selection")
