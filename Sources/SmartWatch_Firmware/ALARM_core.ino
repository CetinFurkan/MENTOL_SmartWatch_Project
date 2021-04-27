void alarm_init()
{
  
}

void alarm_loop()
{
  
}



void setAlarm(uint32 &_alarm, uint32 _delay)
{
  _alarm = millis() + _delay;
}

void disableAlarm(uint32 &_alarm)
{
  _alarm = 0;
}

boolean isAlarmEnabled(uint32 _alarm)
{
  return _alarm > 0;
}

boolean isAlarmRinging(uint32 _alarm)
{
  return _alarm < millis();
}
