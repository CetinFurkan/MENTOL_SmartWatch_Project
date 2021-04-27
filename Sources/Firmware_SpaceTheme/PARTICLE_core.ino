//////////////////////////////////////////////////////
//////////////  PARTICLE TYPE: STARS
//////////////////////////////////////////////////////
void particleStar_init(uint8 _numParts)
{
  numParticle = min(_numParts, MAX_NUMBER_OF_PARTICLES);

  for (uint8 i = 0; i < numParticle; i++)
  {
    particleArray[i].x = random(128);
    particleArray[i].y = 18 + random(110);

    particleArray[i].color = random(150);

    particleArray[i].size = 1 + random(3);

    particleArray[i].colorSpeed = random(2) + particleArray[i].size;
    particleArray[i].xSpeed = 0.6 * (particleArray[i].size / 2);
    particleArray[i].ySpeed = 0.2 * (particleArray[i].size / 2);
  }
}

void particleStar_draw(boolean _ok)
{
  for (uint8 i = 0; i < numParticle; i++)
  {
    particleArray[i].color += particleArray[i].colorSpeed;

    particleArray[i].x += particleArray[i].xSpeed;
    particleArray[i].y += particleArray[i].ySpeed;

    if ((particleArray[i].x > 132 || particleArray[i].y > 132 || particleArray[i].y < 1 || particleArray[i].color > 512) && _ok )
    {
      particleArray[i].x = random(100); 
      particleArray[i].y = (barTop.y+17) + random(110);

      particleArray[i].color = 80 + random(80);

      particleArray[i].size = 1 + random(3);

      particleArray[i].colorSpeed = random(2) + particleArray[i].size;
      particleArray[i].xSpeed = 0.6 * (particleArray[i].size / 2);
      particleArray[i].ySpeed = 0.2 * (particleArray[i].size / 2);

      if ((particleArray[i].size < 2) && (random(20) < 5))
        particleArray[i].xSpeed *= -0.5;
    }

    fillRect( particleArray[i].x - particleArray[i].xSpeed, particleArray[i].y - particleArray[i].ySpeed, particleArray[i].size, particleArray[i].size, colorBack);

    if (particleArray[i].y < (barTop.y+17))
      particleArray[i].colorSpeed = 34;

    if (particleArray[i].color < 256)
      fillRect( particleArray[i].x, particleArray[i].y, particleArray[i].size, particleArray[i].size, colorGray(floor(particleArray[i].color)));
    else
      fillRect( particleArray[i].x, particleArray[i].y, particleArray[i].size, particleArray[i].size, colorGray(floor(512 - particleArray[i].color)));

  }
}


void particleStar_clear()
{
  for (uint8 i = 0; i < numParticle; i++)
  {
    fillRect( particleArray[i].x, particleArray[i].y, particleArray[i].size, particleArray[i].size, colorBack);
  }
}

//////////////////////////////////////////////////////
//////////////  PARTICLE TYPE: SNOW
//////////////////////////////////////////////////////
void particleSnow_init(uint8 _numParts)
{
  numParticle = min(_numParts, MAX_NUMBER_OF_PARTICLES);

  for (uint8 i = 0; i < numParticle; i++)
  {
    particleArray[i].x = random(128);
    particleArray[i].y = -random(64);
    particleArray[i].ySpeed = 2 + random(4);
    particleArray[i].xSpeed = random(2) - random(2);
    particleArray[i].color = random(255);
    particleArray[i].colorSpeed = 0;
    particleArray[i].size = 1 + random(5);
  }
}

void particleSnow_draw(boolean _ok)
{
  for (uint8 i = 0; i < numParticle; i++)
  {
    particleArray[i].y += particleArray[i].ySpeed;
    particleArray[i].x += particleArray[i].xSpeed;

    if (particleArray[i].y > 125 && _ok)
    {
      particleArray[i].ySpeed = 2 + random(3);
      particleArray[i].xSpeed = random(2) - random(2);

      particleArray[i].size = 1 + random(5);
      particleArray[i].x = random(128);
      particleArray[i].y = 0;

      particleArray[i].color = 205 + random(50);
    }

    fillRect( particleArray[i].x - particleArray[i].xSpeed, particleArray[i].y - particleArray[i].ySpeed, particleArray[i].size, particleArray[i].size, colorBack);
    fillRect( particleArray[i].x, particleArray[i].y, particleArray[i].size, particleArray[i].size, color(255, 255, particleArray[i].color));
  }
}

void particleSnow_clear()
{
  for (uint8 i = 0; i < numParticle; i++)
  {
    fillRect( particleArray[i].x, particleArray[i].y, particleArray[i].size, particleArray[i].size, colorBack);
  }

  fillRect(0, 120, 128, 127, colorBack);
}

//////////////////////////////////////////////////////
//////////////  PARTICLE TYPE: EMPTY
//////////////////////////////////////////////////////
void particleEmpty_init(uint8 _numParts)
{
  numParticle = MAX_NUMBER_OF_PARTICLES;

  for (uint8 i = 0; i < numParticle; i++)
  {
    particleArray[i].x          = 0;
    particleArray[i].y          = 0;
    particleArray[i].ySpeed     = 0;
    particleArray[i].xSpeed     = 0;
    particleArray[i].color      = 0;
    particleArray[i].colorSpeed = 0;
    particleArray[i].size       = 0;
  }
}

void particleEmpty_draw(boolean _ok) {}
void particleEmpty_clear() {}




