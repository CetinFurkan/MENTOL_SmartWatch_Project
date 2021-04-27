void fps_control()
{
  setCurrentFont(FONT_SMALL);

  drawNumber(fpsFinal    , 0, 0, 3, ' ', colorBack);

  deltaHedef = millis() - loopTime;

  delta += (deltaHedef - delta) / 20.0; //For smoothing 
  fpsFinal = (1000.0 / delta);

  drawNumber(min(999,fpsFinal) ,  0, 0, 3, ' ' , (fpsFinal > 30)*c_white + (fpsFinal <= 30)*c_red);
  //drawNumber(page+1 , 105, 0,    2, ' ' , c_blue);

  delay(max(0, 20 - delta));
}


void lcd_loop()
{
  loopTime = millis();
}

void lcd_init() {

  pinMode(TFT_RST, OUTPUT);

  digitalWrite(TFT_RST, HIGH);
  delay(100);
  digitalWrite(TFT_RST, LOW);

  pinMode(TFT_RS, OUTPUT);
  pinMode(TFT_CS, OUTPUT);


  csport    = portOutputRegister(digitalPinToPort(TFT_CS));
  cspinmask = digitalPinToBitMask(TFT_CS);
  dcport    = portOutputRegister(digitalPinToPort(TFT_RS));
  dcpinmask = digitalPinToBitMask(TFT_RS);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  delay(100);
  digitalWrite(TFT_RST, HIGH);
  delay(20);
  digitalWrite(TFT_RST, LOW);
  delay(40);
  digitalWrite(TFT_RST, HIGH);
  delay(100);

  writeCommand(ST7735_SWRESET); // software reset ++
  delay(150);
  writeCommand(ST7735_SLPOUT); // out of sleep mode ++
  delay(150);

  lcd_init_commands(); //adafruit

  writeCommand(ST7735_NORON);

  delay(100);
  writeCommand(ST7735_DISPON); // normal display on

  fillScreen(c_white);
}


void lcd_init_commands() {
  writeCommand(ST7735_FRMCTR1  , 0x01, 0x2C, 0x2D); // frame rate control - normal mode
  writeCommand(ST7735_FRMCTR2  , 0x01, 0x2C, 0x2D); // frame rate control - idle mode

  uint8 rateParm3[6] = {0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D}; // dot inversion mode, line inversion mode
  writeCommandAndParms(ST7735_FRMCTR3  , sizeof(rateParm3), rateParm3); // frame rate control - partial mode

  writeCommand(ST7735_INVCTR   , 0x07); // display inversion control, no inversion  //  0x07

  writeCommand(ST7735_PWCTR1 , 0xA2, 0x02, 0x84); // power control, -4.6V, AUTO mode
  writeCommand(ST7735_PWCTR2 , 0xC5);      // power control, VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
  writeCommand(ST7735_PWCTR3, 0x0A, 0x00); // power control, Opamp current small, Boost frequency
  writeCommand(ST7735_PWCTR4, 0x8A, 0x2A); // power control, BCLK/2, Opamp current small & Medium low
  writeCommand(ST7735_PWCTR5, 0x8A, 0xEE); // power control
  writeCommand(ST7735_VMCTR1, 0x0E);       // power control VCOM

  writeCommand(ST7735_MADCTL, 0xC0); // MX,MY RGB Mode - set color mode, 16-bit color //  0xC0:BGR  
  writeCommand(ST7735_COLMOD, 0x05);


  uint8 gammaSet1[] = { 0x02, 0x1C, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2D,
                        0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10
                      };
  uint8 gammaSet2[] = { 0x03, 0x1D, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D,
                        0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10
                      };

  writeCommandAndParms(ST7735_GMCTRP1, sizeof(gammaSet1), gammaSet1);
  writeCommandAndParms(ST7735_GMCTRN1, sizeof(gammaSet2), gammaSet2);


  uint8 addrSetParms[] = {0x00, 0x00, 0x00, 0x7F};
  writeCommandAndParms(ST7735_CASET, sizeof(addrSetParms), addrSetParms);
  writeCommandAndParms(ST7735_RASET, sizeof(addrSetParms), addrSetParms);
}
