void rtc_init() {
  rtc_init(RTCSEL_LSI);
  rtc_set_prescaler_load(0x7fff);
  rtc_set_count(0);


  rtc_attach_interrupt(RTC_SECONDS_INTERRUPT, rtc_interrupt);
}

void rtc_loop() {

}

void rtc_interrupt() {
  if ( rtc_is_second() )
  {
    mytime.second += 1;
    isSecondChanged = true;
    
    digitalWrite(PC13,!digitalRead(PC13));
    
    if (mytime.second > 3)
    {
      mytime.second = 0;
      mytime.minute  += 1;
      isMinuteChanged = true;

      if (mytime.minute > 59)
      {     
        mytime.minute = 0;
        mytime.hour  += 1;
        isHourChanged = true;

        if (mytime.hour > 23)
        {
          mytime.hour = 0;
          mytime.day  += 1;
          isDayChanged = true;

          if (mytime.day > DAYS[mytime.month])
          {
            mytime.day = 0;
            mytime.month  += 1;

            if (mytime.month > 11)
            {
              mytime.month = 0;
              mytime.year += 1;
            }
          }
        }
      }
    }
  }
}
