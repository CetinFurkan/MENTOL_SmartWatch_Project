#include <SPI.h>
#include <RTClock.h>

#include "FontPack.c"
#include "Parameters.h"

#define VERSION  0.25

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

  if (isReleased(1))
  {
    if (isBacklightOff() == true)
      setBacklight(64);
    else if (mode == MODE_CLOCK)
    {
      setAlarm(alarmDisableWatch , 1200);
      segWatchAutoUpdateTime = false;

      for (uint8 j = 0 ; j < 7; j++)
        for (uint8 i = 0 ; i < 4; i++)
          segWatchAlphaTarget[i][j] = 0;

      isCornerTimeEnabled = true;
      //drawCornerTime(true);

      mode = MODE_MENU;
      exit;
    }
    else
    {
      setSegmentWatchMode(SEG_WATCH_ENABLE);
      segWatchAutoUpdateTime = true;
      setSegmentWatchSmooth(mytime.hour, mytime.minute);


      isCornerTimeEnabled = false;
      mode = MODE_CLOCK;
    }
  }


  fps_control();
}


