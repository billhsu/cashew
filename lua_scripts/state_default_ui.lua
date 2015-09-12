function genItemPos(centerX, centerY, size, margin, totalNumber, currentIdx, isVertical)
  local centerItemOffsetX = 0
  local centerItemOffsetY = 0
  if totalNumber % 2 != 0 then
    centerItemOffsetY = -size/2
    centerItemOffsetX = -size/2
  else then
    if isVertical then
      centerItemOffsetX = -size/2
      centerItemOffsetY = margin/2
    else then
      centerItemOffsetY = -size/2
      centerItemOffsetX = margin/2
    end
  end

  local centerItemIdx = 0
  if(totalNumber % 2==0) then
    centerItemIdx = totalNumber/2 + 1
  else then
    centerItemIdx = math.ceil(totalNumber/2)
  end

  local idxDist = (currentIdx - centerItemIdx) * (size + margin)
  if isVertical then
    return centerX + centerItemOffsetX, centerY + centerItemOffsetY + idxDist
  else then
    return centerX + centerItemOffsetX + idxDist, centerY + centerItemOffsetY
  end
end

if button(300, 200, 100, 100, "test", "button_document_new.png") then
  print("hit", a.checked)
end
