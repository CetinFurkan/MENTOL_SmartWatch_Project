void setSegmentWatchMode(uint8 _mode)
{
  if (_mode == SEG_WATCH_ENABLE)
    segWatchIsEnabled = true;
  if (_mode == SEG_WATCH_DISABLE)
    segWatchIsEnabled = false;

  if (_mode == SEG_WATCH_ANIM_SMOOTH)
    segWatchIsSmooth = true;
  if (_mode == SEG_WATCH_ANIM_FAST)
    segWatchIsSmooth = false;

  if (_mode == SEG_WATCH_DRAW_ALWAYS)
    segWatchIsAlways = true;
  if (_mode == SEG_WATCH_DRAW_ON_UPDATE)
    segWatchIsAlways = false;


  if (_mode == SEG_WATCH_SHOW_FILLED)
  {
    segWatchIsFill = true;
    segWatchIsLine = false;
  }
  if (_mode == SEG_WATCH_SHOW_LINES)
  {
    segWatchIsFill = false;
    segWatchIsLine = true;
  }
  if (_mode == SEG_WATCH_SHOW_LINES_AND_FILLED)
  {
    segWatchIsFill = true;
    segWatchIsLine = true;
  }
}

void setSegmentWatchSmooth(uint8 _hour, uint8 _minute)
{
  //SET HOUR - First 2 segment
  uint8 _i1 = _hour % 10;
  uint8 _i2 = (_hour - _i1) / 10;

  for (int j = 0 ; j < 7; j++)
    segWatchAlphaTarget[0][j] = 255 * segmentData[_i2][j];

  for (int j = 0 ; j < 7; j++)
    segWatchAlphaTarget[1][j] = 255 * segmentData[_i1][j];


  //SET MINUTE - Last 2 segment
  _i1 = _minute % 10;
  _i2 = (_minute - _i1) / 10;

  for (int j = 0 ; j < 7; j++)
    segWatchAlphaTarget[2][j] = 255 * segmentData[_i2][j];

  for (int j = 0 ; j < 7; j++)
    segWatchAlphaTarget[3][j] = 255 * segmentData[_i1][j];
}

void segmentWatch_loop()
{

  if (segWatchIsEnabled)
  {
    if (themeSegWatch == THEME_SPACE)
    {
      themeSpaceDrawWatch();
    }
    else if (themeSegWatch == THEME_NONE)
    {   
        if (segWatchIsSmooth == false)
          drawSegmentWatchFast(  c_black, c_red,    c_lgray, c_lgray , segWatchIsAlways || segWatchUpdated, segWatchIsLine, segWatchIsFill);
        else
          drawSegmentWatchSmooth(c_green, c_green,  c_black, c_black , segWatchIsAlways || segWatchUpdated, segWatchIsLine, segWatchIsFill);

      if (segWatchUpdated)
        segWatchUpdated = false;
    }
  }

  //if (isCornerTimeEnabled)
    drawCornerTime();
}


void segmentWatchUpdate()
{
  segWatchUpdated = true;
}

void drawSegmentWatchSmooth(uint16_t _col, uint16_t _colFill, uint16_t _colBack, uint16_t _colBackFill, boolean _always, boolean _isline, boolean _isfill)
{
  drawSegmentWatchNumberSmooth(0, segWatchX - 2 * segWatchShift - segmentStroke * 2  , segWatchY , _colBackFill, _always, _isline, _isfill);
  drawSegmentWatchNumberSmooth(1, segWatchX - 1 * segWatchShift - segmentStroke * 2  , segWatchY , _colBackFill, _always, _isline, _isfill);

  drawSegmentWatchNumberSmooth(2, segWatchX          + segmentStroke * 4 + segmentStroke , segWatchY , _colBackFill, _always, _isline, _isfill);
  drawSegmentWatchNumberSmooth(3, segWatchX + segWatchShift + segmentStroke * 4 + segmentStroke , segWatchY , _colBackFill, _always, _isline, _isfill);

  if (isHourChanged && segWatchAutoUpdateTime)
  {
    setSegmentWatchSmooth(mytime.hour, mytime.minute);
    isHourChanged = false;
  }

  if (isMinuteChanged && segWatchAutoUpdateTime)
  {
    setSegmentWatchSmooth(mytime.hour, mytime.minute);
    isMinuteChanged = false;
  }


  if (_isline)
  {
    drawRect(segWatchX - segmentStroke , segWatchY + segmentWidth - segmentStroke * 4,  segmentStroke * 2, segmentStroke * 2, color(0, segWatchDotsAlphaCurrent , 0) );
    drawRect(segWatchX - segmentStroke , segWatchY + segmentWidth + segmentStroke * 4,  segmentStroke * 2, segmentStroke * 2, color(0, segWatchDotsAlphaCurrent , 0)  );
  }

  if (_isfill)
  {
    fillRect(segWatchX - segmentStroke  + 1, segWatchY + segmentWidth - segmentStroke * 4 + 1, segmentStroke * 2 - 1, segmentStroke * 2 - 1, color(0, segWatchDotsAlphaCurrent , 0) );
    fillRect(segWatchX - segmentStroke  + 1, segWatchY + segmentWidth + segmentStroke * 4 + 1, segmentStroke * 2 - 1, segmentStroke * 2 - 1, color(0, segWatchDotsAlphaCurrent , 0) );
  }

  for (int i = 0 ; i < 4; i++)
    for (int j = 0 ; j < 7; j++)
      segWatchAlphaCurrent[i][j] += (segWatchAlphaTarget[i][j] - segWatchAlphaCurrent[i][j]) / 10;

  segWatchDotsAlphaCurrent += ((segWatchAutoUpdateTime)  * 255 * (mytime.second % 2) - segWatchDotsAlphaCurrent) / 10;

}

void drawSegmentWatchNumberSmooth(uint8 _place, uint8 _x, uint8 _y, uint16_t _col_fill, boolean _always, boolean _isline, boolean _isfill)
{
  for (uint8 i = 0; i < 7; i++)
    if (segWatchAlphaTarget[_place][i] == 0)  //THE ONES WHO TURNS TO    BACK COLOR(0)
        drawSegment(i, _x , _y, color(0, floor(segWatchAlphaCurrent[_place][i]) , 0) , color(0, floor(segWatchAlphaCurrent[_place][i]) , 0) , _isline, _isfill);

  for (uint8 i = 0; i < 7; i++)
    if (segWatchAlphaTarget[_place][i] == 255)//THE ONES WHO TURNS TO  FILL COLOR(255)
        drawSegment(i, _x , _y, color(0, floor(segWatchAlphaCurrent[_place][i]) , 0) , color(0, floor(segWatchAlphaCurrent[_place][i]) , 0) , _isline, _isfill);
}

void segmentWatch_init()
{
  for (int i = 0 ; i < 4; i++)
    for (int j = 0 ; j < 7; j++)
    {
      segWatchAlphaCurrent[i][j] = 0;
      segWatchAlphaTarget[i][j]  = 255;
    }

  segmentWidth = 18;
  segmentStroke = 2;
  segWatchX = 64;
  segWatchY = 44;

  segWatchShift = segmentWidth + segmentStroke * 4 ;
}

