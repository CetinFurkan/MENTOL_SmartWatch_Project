void drawCornerTime()
{
  uint8 x = 96;
  uint8 y = 2;

  alphaCornerTime += ((int)(isCornerTimeEnabled) * 255 - alphaCornerTime) / 12.0;
  uint16_t _col = color(0, floor(alphaCornerTime), 0);

  setCurrentFont(FONT_SMALL);

  if (isHourChanged)
  {
    //FIRST: Clear the previous Hour text
    if (mytime.hour == 0)
      drawString("23", x, y , colorBack);
    else
      drawNumber(mytime.hour - 1, x, y  , 2 , '0', colorBack);
  }

  if (alphaCornerTime > 4) {  //SECOND: Draw new Hour text
    drawNumber(mytime.hour, x, y  , 2 , '0', _col);
  }

  if (isHourChanged)
    isHourChanged   = false; //Clear the flag


  if (isMinuteChanged)  //FIRST: Clear the previous Minute text
  {
    if (mytime.minute == 0)
      drawString("59", x + 17, y  , colorBack);
    else
      drawNumber(mytime.minute - 1, x + 17, y  , 2 , '0', colorBack);
  }

  if (alphaCornerTime > 4) //SECOND: Draw new Minute text
    drawNumber(mytime.minute, x + 17, y  , 2 , '0', _col);

  if (isMinuteChanged)
    isMinuteChanged = false; //Clear the flag


  if (isSecondChanged || alphaCornerTime > 4)
  {
    if (mytime.second % 2 == 0)
      setTextColor(_col);
    else
      setTextColor(colorBack);

    drawString(":" , x + 13, y);

    isSecondChanged = false; //Clear the flag
  }

}
