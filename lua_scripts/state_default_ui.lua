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

local topBarItemSize = 60
local topBarItemMargin = 10
local function genTopBarItemPos(idx)
  return genItemPos(window_width/2, 1.5*topBarItemSize, topBarItemSize, topBarItemMargin, 5, idx, false)
end
local function getTopBarItemSize()
  return topBarItemSize, topBarItemSize
end

local leftBarItemSize = 40
local leftBarItemMargin = 5
local function genLeftBarItemPos(idx)
  return genItemPos(1.5*leftBarItemSize, window_height/2, leftBarItemSize, leftBarItemMargin, 3, idx, true)
end
local function getLeftBarItemSize()
  return leftBarItemSize, leftBarItemSize
end

if button(genLeftBarItemPos(1), getLeftBarItemSize(), "New Sketch", "button_document_new.png") then

end

if button(genLeftBarItemPos(2), getLeftBarItemSize(), "Open Sketch", "button_document_open.png") then

end

if button(genLeftBarItemPos(3), getLeftBarItemSize(), "Save Sketch", "button_document_save.png") then

end
