void clearScreen(uint16_t _col)
{
  colorBack = _col;
  fillScreen(colorBack); 
}

void clearScreen()
{
  fillScreen(colorBack); 
}


void fillScreen(uint16 color) {

  setAddrWindow(0, 0, TFT_WIDTH - 1, TFT_HEIGHT - 1);

  *dcport |=  dcpinmask;
  *csport &= ~cspinmask;

  SPI.setDataSize (SPI_CR1_DFF); // Set spi 16bit mode
  lineBuffer[0] = color;
  SPI.dmaSend(lineBuffer, (65535), 0);
  SPI.dmaSend(lineBuffer, ((TFT_WIDTH * TFT_HEIGHT) - 65535), 0);
  SPI.setDataSize (0);

  *csport |= cspinmask;
}

void setAddrWindow(uint8 x0, uint8 y0, uint8 x1, uint8 y1) {
  writeCommand(ST7735_CASET);
  *dcport |=  dcpinmask;
  *csport &= ~cspinmask;
  SPI.setDataSize (SPI_CR1_DFF);
  SPI.write(x0);
  SPI.write(x1);

  writeCommand(ST7735_RASET);
  *dcport |=  dcpinmask;
  *csport &= ~cspinmask;

  SPI.write(y0);
  SPI.write(y1);
  SPI.setDataSize(0);

  writeCommand(ST7735_RAMWR);
}

