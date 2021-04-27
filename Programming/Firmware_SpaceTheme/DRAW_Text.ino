void drawChar(char c, int8_t x, int8_t y)
{
  int8_t ch;
  word temp;

  temp = ((c - fontOffset) * ((fontXsize / 8) * fontYsize)) + 4; //4 is for the first property data
  for (int8_t j = 0; j < fontYsize; j++)
  {
    for (int zz = 0; zz < (fontXsize / 8); zz++)
    {
      ch = pgm_read_byte(&fontData[temp + zz]);
      for (int8_t i = 0; i < 8; i++)
      {
        if ((ch & (1 << (7 - i))) != 0)
          drawPixel(x + i + (zz * 8) , y + j , colorText);
      }
    }
    temp += (fontXsize / 8);
  }
}


void setCurrentFont(fontdatatype* font)
{
  fontData   = font;
  fontXsize  = font[0];
  fontYsize  = font[1];
  fontOffset = font[2];
  fontNumchars = font[3];
}


void drawString(char *string, int16_t x, int16_t y)
{
  uint8_t stl = strlen( string );

  for (uint8_t i = 0; i < stl; i++)
    drawChar(*string++, x + (i * (fontXsize)), y);
}

void drawString(char *string, int16_t x, int16_t y, uint16_t col)
{
  setTextColor(col);
  drawString(string, x, y);
}

void drawNumber(long num, int x, int y, int length, char filler, uint16_t col)
{
  setTextColor(col);
  drawNumber(num,x,y,length,filler);
}

void drawNumber(long num, int x, int y, int length, char filler)
{
  char buf[25];
  char st[27];
  boolean neg = false;
  int c = 0, f = 0;

  if (num == 0)
  {
    if (length != 0)
    {
      for (c = 0; c < (length - 1); c++)
        st[c] = filler;
      st[c] = 48;
      st[c + 1] = 0;
    }
    else
    {
      st[0] = 48;
      st[1] = 0;
    }
  }
  else
  {
    if (num < 0)
    {
      neg = true;
      num = -num;
    }

    while (num > 0)
    {
      buf[c] = 48 + (num % 10);
      c++;
      num = (num - (num % 10)) / 10;
    }
    buf[c] = 0;

    if (neg)
    {
      st[0] = 45;
    }

    if (length > (c + neg))
    {
      for (int i = 0; i < (length - c - neg); i++)
      {
        st[i + neg] = filler;
        f++;
      }
    }

    for (int i = 0; i < c; i++)
    {
      st[i + neg + f] = buf[c - i - 1];
    }
    st[c + neg + f] = 0;

  }

  drawString(st, x, y);
}
