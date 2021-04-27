



void drawBarTop(int8 _x, int8 _y, uint16_t _col)
{
  drawLine(0,          _y + 2 - 1,       82,   _y + 2 - 1 , _col); //   -----
  drawLine(80  + 10 + 1, _y + 14 - 1,      82 + 1, _y + 2 - 1 , _col); //     \
  drawLine(80  + 10  , _y + 14 - 1,      82,   _y + 2 - 1 , _col); //         \
  drawLine(80  + 10,   _y + 14 - 1,     127,   _y + 14 - 1, _col); //           ---

  drawLine(0,        _y + 2,       82, _y + 2 , _col);//   -----
  drawLine(80  + 10, _y + 14,      82, _y + 2 , _col);//        \
  drawLine(80  + 10, _y + 14,     127, _y + 14, _col);//          ---

  drawLine(0,        _y + 12,       88 ,  _y + 12 , _col);

  //BATTERY ICON
  drawRect(2, _y + 2 + 2, batLevelMax + 3, 6, _col);
  drawLine(batLevelMax + 3 + 2 + 1, _y + 2 + 4, batLevelMax + 3 + 2 + 1, _y + 2 + 6, _col );

  for (uint8 i = 0; i < batLevel ; i++ )
    drawLine(4 + i, _y + 2 + 4, 4 + i, _y + 2 + 4 + 2, _col);

  //USB ICON
  uint8 xx = 14;
  if (_col == c_green) _col = c_yellow;

  drawLine(xx + 4, _y + 2 + 5 + 1, xx + 5, _y + 2 + 5 + 1, _col);
  drawLine(xx + 4, _y + 2 + 5 - 1, xx + 5, _y + 2 + 5 - 1, _col);

  drawLine(xx + 3, _y + 2 + 5, xx + 14, _y + 2 + 5, _col);

  drawLine(xx + 8, _y + 2 + 3, xx + 11, _y + 2 + 3, _col); //top line
  drawPixel(xx + 7, _y + 2 + 4, _col); //top line's point

  drawLine(xx + 10, _y + 2 + 7, xx + 12, _y + 2 + 7, _col); //bottom line
  drawPixel(xx + 9, _y + 2 + 6, _col); //bottom line's point


  //BLUETOOTH LOGO
  xx = 32;
  if (_col == c_yellow) _col = color(65, 150, 255);

  drawLine(xx + 2, _y + 2 + 2 , xx + 2, _y + 2 + 8 , _col);
  drawPixel(xx + 3, _y + 2 + 3, _col);
  drawPixel(xx + 4, _y + 2 + 4, _col);
  drawPixel(xx + 3, _y + 2 + 5, _col);
  drawPixel(xx + 4, _y + 2 + 6, _col);
  drawPixel(xx + 3, _y + 2 + 7, _col);

  drawPixel(xx + 0, _y + 2 + 4, _col);
  drawPixel(xx + 1, _y + 2 + 5, _col);
  drawPixel(xx + 0, _y + 2 + 6, _col);
}

