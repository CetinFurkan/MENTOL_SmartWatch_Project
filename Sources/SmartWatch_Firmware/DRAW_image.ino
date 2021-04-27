void drawBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {

  uint16_t color;
  
  writeCommand(0x2a);
  writeData(x >> 8);
  writeData(x);
  writeData((x + w - 1) >> 8);
  writeData((x + w - 1));
  
  writeCommand(0x2b);
  writeData(y >> 8);
  writeData(y);
  writeData((y+h-1) >> 8);
  writeData(y+h-1);

  writeCommand(0x2c);

  *dcport |=  dcpinmask;
  *csport &= ~cspinmask;
  
  for ( uint16_t i = 0; i < (w * h); i++ )
  {
    color = bitmap[i]; //pgm_read_word(&bitmap[i]);

    SPI.write(color >> 8);
    SPI.write(color & 0xff);
  }

  *csport |= cspinmask;
}
