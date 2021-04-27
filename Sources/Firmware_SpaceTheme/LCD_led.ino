void backlight_init() {
  pinMode(TFT_LED, PWM);
  pwmWrite(TFT_LED, 0);
}

void backlight_loop()
{
  ledLevel += (ledLevelHedef - ledLevel) / 24.0;
  pwmWrite(TFT_LED, int(ledLevel));
}

void setBacklight(uint8 a)
{
  a = min(64, max(0, a) );
  ledLevelHedef = 1024 * a - 1 * int(a == 64);
}
/*
void setBacklight(boolean _state)
{
  ledLevelHedef = 1024 * (_state*63));
}*/

boolean isBacklightOn()
{
  return abs(ledLevelHedef - ledLevel)<5 && ledLevelHedef>0;
}


boolean isBacklightOff()
{
    return ((abs(ledLevelHedef - ledLevel)<5) && ledLevelHedef==0);
}
