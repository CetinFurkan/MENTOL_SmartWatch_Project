#include <SPI.h>
#include <RTClock.h>

#include "FontPack.c"
#include "Parameters.h"

#define VERSION  0.30

//MODE
uint8 mode = 0;
int page = -1;

#define MODE_TEST  99
#define MODE_MENU  10
#define MODE_CLOCK  2

#define THEME_NONE  0
#define THEME_SPACE 3

uint8 themeSegWatch = 0;
uint8 themeMenu = 0;

boolean segWatchAutoUpdateTime = true;
uint32 alarmDisableWatch = 0;

boolean isCornerTimeEnabled = false;
float alphaCornerTime = 0;

uint8 batLevel = 8;
uint8 batLevelMax = 8;

struct PositionExt {
  float x ;
  float y ;
  int8 xpre ;
  int8 ypre ;
  int8 xTarget ;
  int8 yTarget ;
};

struct Position {
  float x ;
  float y ;
  int8 xTarget ;
  int8 yTarget ;
};

PositionExt barTop      = {0, -16, 0, -15, 0, 0};
Position menuLines[14] =  {
  {64, 64, 64, 64},
  {64, 64, 64, 64},
  {64, 64, 64, 64},
  {64, 64, 64, 64},

  {64, 64, 64, 64},
  {64, 64, 64, 64},
  {64, 64, 64, 64},
  {64, 64, 64, 64},

  {64, 64, 64, 64},
  {64, 64, 64, 64},

  {64, 64, 64, 64},
  {64, 64, 64, 64},
  {64, 64, 64, 64},
  {64, 64, 64, 64}
};


uint8 menuActive = 0;
#define menuNumber 4

char* menuNames[menuNumber] = {"Connection", "Notes", "Photos", "Set Time"};

uint16_t colorCornerTime = c_green;

uint8 menuNamePos[menuNumber] = {24, 44, 38, 34};

void setup(void) {
  backlight_init();
  lcd_init();
  rtc_init();
  button_init();
  ssaver_init();
  menu_init();
  segmentWatch_init();
  page_init();
  alarm_init();

  setBacklight(64);

  mode = MODE_CLOCK;

  moveMenuDisappear();

  themeSpace_init();
}

void loop() {
  lcd_loop();
  backlight_loop();
  rtc_loop();
  button_loop();
  ssaver_loop();
  menu_loop();
  segmentWatch_loop();
  alarm_loop();

  themeSpace_loop();


  if ( isReleased(0) || isReleased(2) )
  {
    drawString(menuNames[menuActive], menuNamePos[menuActive], 110, c_black);
    menuActive += isReleased(0) - isReleased(2);
    
    menuActive = menuActive % menuNumber;
/*
    if (menuActive < 0)
      menuActive = menuNumber - 1;

    if (menuActive >= menuNumber)
      menuActive = 0;
*/
    menuIconsSet(menuActive);
  }

  //MOTION CONTROL
  barTop.ypre = floor(barTop.y);
  barTop.y += (barTop.yTarget -  barTop.y) / 12.0;

  ///SWITCHERS IN CHAIN
  if (alphaCornerTime > 240 )
  {
    if (mode == MODE_MENU)
      drawBarTop(0, floor(barTop.y)   , color(0, 125 + 130 * ((int)(ceil(alphaCornerTime)) % 5 == 0) , 0));
  }
  else if (alphaCornerTime > 5 && alphaCornerTime < 100 && mode == MODE_CLOCK)
  {
    //drawBarTop(0, barTop.ypre, colorBack);
    drawBarTop(0, floor(barTop.y)   , color(0, 125 + (alphaCornerTime) , 0));
  }
  else if (barTop.ypre != floor(barTop.y))
  {
    drawBarTop(0, barTop.ypre, colorBack);
    drawBarTop(0, floor(barTop.y)   , color(0, 125 , 0));
  }


  if (barTop.y > -1 )
  {
    drawMenuIconsList();
    drawString(menuNames[menuActive], menuNamePos[menuActive], 110, colorCornerTime);

    if (mode == MODE_MENU)
      isCornerTimeEnabled = true;
  }
  if (alphaCornerTime < 5 && mode == MODE_CLOCK)
    barTop.yTarget = -16;

  if (barTop.y < -12 && mode == MODE_CLOCK)
  {
    setSegmentWatchMode(SEG_WATCH_ENABLE);
    segWatchAutoUpdateTime = true;
    setSegmentWatchSmooth(mytime.hour, mytime.minute);
  }



  if (isReleased(1))
  {
    if (isBacklightOff() == true)
      setBacklight(64);
    else if (mode == MODE_CLOCK)
    {
      setAlarm(alarmDisableWatch , 1000);
      segWatchAutoUpdateTime = false;


      for (uint8 j = 0 ; j < 7; j++)
        for (uint8 i = 0 ; i < 4; i++)
          segWatchAlphaTarget[i][j] = 0;

      barTop.yTarget = 0;

      menuActive = 0;
      menuIconsSet(menuActive);

      mode = MODE_MENU;
      exit;
    }
    else
    {
      moveMenuDisappear();

      isCornerTimeEnabled = false;
      mode = MODE_CLOCK;
    }
  }


  fps_control();
}


