void drawCircle(int x, int y, int r, uint16_t color)
{
    int ix = r;
    int iy = 0;
    int err = 1 - r;
    
    while(ix >= iy)
    {
        drawPixel(x + ix, y + iy, color);
        drawPixel(x + iy, y + ix, color);
        drawPixel(x - ix, y + iy, color);
        drawPixel(x - iy, y + ix, color);
        drawPixel(x - ix, y - iy, color);
        drawPixel(x - iy, y - ix, color);
        drawPixel(x + ix, y - iy, color);
        drawPixel(x + iy, y - ix, color);
        iy++;
        if (err < 0)
        {
            err += 2 * iy + 1;
        }
        else
        {
            ix--;
            err += 2 * (iy - ix + 1);
        }
    }
}


//////////////////////////////////////// DRAW RECTANGlE //////////////////////////////
void drawRect(int16_t _x, int16_t _y, int16_t _w, int16_t _h,  uint16_t _col) {

  if ((_x < 0) || (_x >= TFT_WIDTH) || (_y < 0) || (_y >= TFT_HEIGHT)) return;

  drawQuad(_x,_y, _x+_w,_y, _x+_w, _y+_h, _x, _y+_h, _col);
}
//////////////////////////////////////// DRAW PIXEL //////////////////////////////
void drawPixel(int16_t _x, int16_t _y, uint16_t _col) {

  if ((_x < 0) || (_x >= TFT_WIDTH) || (_y < 0) || (_y >= TFT_HEIGHT)) return;

  setAddrWindow(_x, _y, _x + 1, _y + 1);

  setColor(_col);
}

//////////////////////////////////////// FILL RECT //////////////////////////////
void fillRect(uint8 x, uint8 y, uint8 w, uint8 h, uint16 color) {
  if ((x >= TFT_WIDTH) || (y >= TFT_HEIGHT || h < 1 || w < 1)) return;

  if ((x + w - 1) >= TFT_WIDTH)  w = TFT_WIDTH  - x;
  if ((y + h - 1) >= TFT_HEIGHT) h = TFT_HEIGHT - y;

  if (w == 1 && h == 1) {
    drawPixel(x, y, color);
    return;
  }

  setAddrWindow(x, y, x + w - 1, y + h - 1);

  *dcport |=  dcpinmask;
  *csport &= ~cspinmask;

  SPI.setDataSize (SPI_CR1_DFF);
  lineBuffer[0] = color;
  if (w * h <= 65535) {
    SPI.dmaSend(lineBuffer, (w * h), 0);
  }
  else {
    SPI.dmaSend(lineBuffer, (65535), 0);
    SPI.dmaSend(lineBuffer, ((w * h) - 65535), 0);
  }
  SPI.setDataSize (0);

  *csport |= cspinmask;
}

//////////////////////////////////////// DRAW FAST HORIZONTAL LINE //////////////////////////////
void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {

  if ((x >= TFT_WIDTH) || (y >= TFT_HEIGHT || w < 1)) return;
  if ((x + w - 1) >= TFT_WIDTH)  w = TFT_WIDTH - x;
  if (w < 2 ) {
    drawPixel(x, y, color);
    return;
  }

  setAddrWindow(x, y, x + w - 1, y);
  *dcport |=  dcpinmask;
  *csport &= ~cspinmask;

  SPI.setDataSize (SPI_CR1_DFF); // Set spi 16bit mode
  lineBuffer[0] = color;
  SPI.dmaSend(lineBuffer, w, 0);
  SPI.setDataSize (0);

  *csport |= cspinmask;
}

//////////////////////////////////////// DRAW FAST VERTICAL LINE //////////////////////////////
void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {

  if ((x >= TFT_WIDTH) || (y >= TFT_HEIGHT || h < 1)) return;

  if ((y + h - 1) >= TFT_HEIGHT)
    h = TFT_HEIGHT - y;
  if (h < 2 ) {
    drawPixel(x, y, color);
    return;
  }

  setAddrWindow(x, y, x, y + h - 1);

  *dcport |=  dcpinmask;
  *csport &= ~cspinmask;

  SPI.setDataSize (SPI_CR1_DFF); // Set SPI 16bit mode
  lineBuffer[0] = color;
  SPI.dmaSend(lineBuffer, h, 0);
  SPI.setDataSize (0);

  *csport |= cspinmask;
}

//////////////////////////////////////// DRAW LINE (GENERAL)//////////////////////////////
void drawLine(int16_t x0, int16_t y0,  int16_t x1, int16_t y1, uint16_t color) {
  if ((y0 < 0 && y1 < 0) || (y0 > TFT_HEIGHT && y1 > TFT_HEIGHT)) return;
  if ((x0 < 0 && x1 < 0) || (x0 > TFT_WIDTH && x1 > TFT_WIDTH)) return;
  if (x0 < 0) x0 = 0;
  if (x1 < 0) x1 = 0;
  if (y0 < 0) y0 = 0;
  if (y1 < 0) y1 = 0;

  if (y0 == y1) {
    if (x1 > x0) {
      drawFastHLine(x0, y0, x1 - x0 + 1, color);
    }
    else if (x1 < x0) {
      drawFastHLine(x1, y0, x0 - x1 + 1, color);
    }
    else {
      drawPixel(x0, y0, color);
    }
    return;
  }
  else if (x0 == x1) {
    if (y1 > y0) {
      drawFastVLine(x0, y0, y1 - y0 + 1, color);
    }
    else {
      drawFastVLine(x0, y1, y0 - y1 + 1, color);
    }
    return;
  }

  bool steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }
  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  }
  else {
    ystep = -1;
  }

  int16_t xbegin = x0;
  lineBuffer[0] = color;
  *csport &= ~cspinmask;
  if (steep) {
    for (; x0 <= x1; x0++) {
      err -= dy;
      if (err < 0) {
        int16_t len = x0 - xbegin;
        if (len) {
          drawFastVLine (y0, xbegin, len + 1, color);
        }
        else {
          drawPixel(y0, x0, color);
        }
        xbegin = x0 + 1;
        y0 += ystep;
        err += dx;
      }
    }
    if (x0 > xbegin + 1) {
      drawFastVLine(y0, xbegin, x0 - xbegin, color);
    }

  }
  else {
    for (; x0 <= x1; x0++) {
      err -= dy;
      if (err < 0) {
        int16_t len = x0 - xbegin;
        if (len) {
          drawFastHLine(xbegin, y0, len + 1, color);
        }
        else {
          drawPixel(x0, y0, color);
        }
        xbegin = x0 + 1;
        y0 += ystep;
        err += dx;
      }
    }
    if (x0 > xbegin + 1) {
      drawFastHLine(xbegin, y0, x0 - xbegin, color);
    }
  }
  *csport |= cspinmask;
}

