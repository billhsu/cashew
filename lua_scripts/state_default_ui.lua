function genItemPos(centerX, centerY, size, margin, totalNumber, currentIdx, isVertical)
  local centerItemOffsetX = 0
  local centerItemOffsetY = 0
  if totalNumber % 2 ~= 0 then
    centerItemOffsetY = -size/2
    centerItemOffsetX = -size/2
  else
    if isVertical then
      centerItemOffsetX = -size/2
      centerItemOffsetY = margin/2
    else
      centerItemOffsetY = -size/2
      centerItemOffsetX = margin/2
    end
  end

  local centerItemIdx = 0
  if(totalNumber % 2==0) then
    centerItemIdx = totalNumber/2 + 1
  else
    centerItemIdx = math.ceil(totalNumber/2)
  end

  local idxDist = (currentIdx - centerItemIdx) * (size + margin)
  if isVertical then
    return centerX + centerItemOffsetX, centerY + centerItemOffsetY + idxDist
  else
    return centerX + centerItemOffsetX + idxDist, centerY + centerItemOffsetY
  end
end

local topBarItemSize = 60 * backingRatioX
local topBarItemMargin = 10 * backingRatioX
local function genTopBarItemPos(idx)
  return genItemPos(window_width/2, topBarItemSize, topBarItemSize, topBarItemMargin, 5, idx, false)
end
local function getTopBarItemSize()
  return topBarItemSize, topBarItemSize
end

local leftBarItemSize = 50 * backingRatioX
local leftBarItemMargin = 5 * backingRatioX
local function genLeftBarItemPos(idx)
  return genItemPos(leftBarItemSize, window_height/2, leftBarItemSize, leftBarItemMargin, 3, idx, true)
end
local function getLeftBarItemSize()
  return leftBarItemSize, leftBarItemSize
end

-- left side buttons
local buttonPosX,buttonPosY = genLeftBarItemPos(1)
if button(buttonPosX ,buttonPosY, leftBarItemSize, leftBarItemSize, "New Sketch", "button_document_new.png") then
  newFile()
end

local buttonPosX,buttonPosY = genLeftBarItemPos(2)
if button(buttonPosX ,buttonPosY, leftBarItemSize, leftBarItemSize, "Open Sketch", "button_document_open.png") then
  openFile()
end

local buttonPosX,buttonPosY = genLeftBarItemPos(3)
if button(buttonPosX ,buttonPosY, leftBarItemSize, leftBarItemSize, "Save Sketch", "button_document_save.png") then
  saveFile()
end


-- top buttons
local buttonPosX,buttonPosY = genTopBarItemPos(1)
if button(buttonPosX ,buttonPosY, topBarItemSize, topBarItemSize, "Standard View", "button_standard_view.png") then
  standardView()
end

local buttonPosX,buttonPosY = genTopBarItemPos(2)
if button(buttonPosX ,buttonPosY, topBarItemSize, topBarItemSize, "Undo", "button_undo.png") then
  undo()
end


local buttonPosX,buttonPosY = genTopBarItemPos(3)
if button(buttonPosX ,buttonPosY, topBarItemSize, topBarItemSize, "Redo", "button_redo.png") then
  redo()
end


local buttonPosX,buttonPosY = genTopBarItemPos(4)
if button(buttonPosX ,buttonPosY, topBarItemSize, topBarItemSize, "Delete lines", "button_delete.png") then
  deleteLine()
end


local buttonPosX,buttonPosY = genTopBarItemPos(5)
if button(buttonPosX ,buttonPosY, topBarItemSize, topBarItemSize, "Mirror mode", "button_mirror.png") then
  mirrorMode()
end
