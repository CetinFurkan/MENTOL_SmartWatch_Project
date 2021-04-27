void ssaver_init()
{
  ssaverSetAnimation(0);
}

boolean ssaverSetParticleNumber(int _no)
{
  ssaverClear();

  if (screensaver == SSAVER_EMPTY)
    particleEmpty_init(_no);
  else if (screensaver == SSAVER_STAR)
    particleStar_init(_no);
  else if (screensaver == SSAVER_SNOW)
    particleSnow_init(_no);

  ssaverEnable(true);

  return true;

}
boolean ssaverSetAnimation(int _id)
{
  if (_id > 2)
    return false;
  else
  {
    ssaverClear();
    screensaver = _id;
  }

  if (screensaver == SSAVER_EMPTY)
    particleEmpty_init(SSAVER_EMPTY_DEFAULT_PARTICLE);
  else if (screensaver == SSAVER_STAR)
    particleStar_init(SSAVER_STAR_DEFAULT_PARTICLE);
  else if (screensaver == SSAVER_SNOW)
    particleSnow_init(SSAVER_SNOW_DEFAULT_PARTICLE);

  ssaverEnable(true);

  return true;
}


boolean ssaverClear()
{
  if (screensaver == SSAVER_EMPTY)
    particleEmpty_clear();
  else if (screensaver == SSAVER_STAR)
    particleStar_clear();
  else if (screensaver == SSAVER_SNOW)
    particleSnow_clear();

  return true;
}

void ssaver_loop()
{
  if (ssaverEnabled == false)
    return;

  if (screensaver == SSAVER_EMPTY)
    particleEmpty_draw(true);
  else if (screensaver == SSAVER_STAR)
    particleStar_draw(true);
  else if (screensaver == SSAVER_SNOW)
    particleSnow_draw(true);
}


void ssaverEnable(boolean _en)
{
  ssaverEnabled = _en;
}

void ssaverRestart(boolean _en)
{
  ssaverClear();
  ssaverSetAnimation(_en);
}



