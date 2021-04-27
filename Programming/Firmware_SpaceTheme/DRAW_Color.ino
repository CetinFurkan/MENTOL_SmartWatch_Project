void setTextColor(uint16_t color)
{
  colorText = color;
}

uint16_t colorGray(uint8_t r) {
  return color(r,r,r);
}

uint16_t color(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

uint32_t pickColorWheel(int WheelPos) {
  if (WheelPos < 85) {
    return color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void setColor(uint16_t color) {
  *dcport |=  dcpinmask;
  *csport &= ~cspinmask;

  SPI.write(color >> 8);
  SPI.write(color);
  
  *csport |= cspinmask;
}



/*
uint16_t colorDetail(uint32_t r, uint32_t g, uint32_t b) {
  return (((r/256) & 0xF8) << 8) | (((g/256) & 0xFC) << 3) | ((b/256) >> 3);
}

uint32_t pickColorWheel(int WheelPos) {
  if (WheelPos < 85*256) {
    return colorDetail(WheelPos * 3, 255*256 - WheelPos * 3, 0);
  } else if (WheelPos < 170*256) {
    WheelPos -= 85*256;
    return colorDetail(255*256 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170*256;
    return colorDetail(0, WheelPos * 3, 255*256 - WheelPos * 3);
  }
}
*/

