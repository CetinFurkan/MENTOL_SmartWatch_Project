void button_init() {
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, 0);

  pinMode(PIN_BUTTON_1,   INPUT);
  pinMode(PIN_BUTTON_2,   INPUT);
  pinMode(PIN_BUTTON_3,   INPUT);
}

void button_loop() {

  for (uint8_t i = 0; i < 3; i++)
  {
    buttons[i].stateCurrent = boolean(digitalRead(buttons[i].pinNo));

    if (buttons[i].stateCurrent == HIGH)
    {
      buttons[i].counterLongPress += 1;

      if (buttons[i].counterLongPress > BUTTON_LONG_PRESS_TRESHOLD)
      {
        buttons[i].state = BUTTON_LONGPRESSED;
        //buttons[i].counterLongPress = 0;
      }

      if (buttons[i].state != BUTTON_LONGPRESSED)
        if (buttons[i].state != BUTTON_PRESSED)
          buttons[i].state = BUTTON_PRESSED;
    }

    if (buttons[i].stateCurrent == LOW)
    {
      if (buttons[i].state == BUTTON_PRESSED || buttons[i].state == BUTTON_LONGPRESSED)
      {
        buttons[i].state = BUTTON_RELEASED;
        buttons[i].counterLongPress = 0;
      }
      else
        buttons[i].state = BUTTON_FREE;
    }

  }

  isButtonAllPressed   = (buttons[0].state == BUTTON_PRESSED  && buttons[1].state == BUTTON_PRESSED  && buttons[2].state == BUTTON_PRESSED);
  isButtonAllReleased  = (buttons[0].state == BUTTON_RELEASED && buttons[1].state == BUTTON_RELEASED && buttons[2].state == BUTTON_RELEASED);

  isButtonAnyPressed  = (buttons[0].state == BUTTON_PRESSED  || buttons[1].state == BUTTON_PRESSED  || buttons[2].state == BUTTON_PRESSED);
  isButtonAnyReleased = (buttons[0].state == BUTTON_RELEASED || buttons[1].state == BUTTON_RELEASED || buttons[2].state == BUTTON_RELEASED);
}

boolean isPressed(uint8_t buttonNo)
{
  if (buttonNo == 0 || buttonNo == 1 || buttonNo == 2)
    return (buttons[buttonNo].state == BUTTON_PRESSED);
  else if (buttonNo == BUTTON_ANY)
    return isButtonAnyPressed;
  else if (buttonNo == BUTTON_NONE)
    return !isButtonAnyPressed;
  else if (buttonNo == BUTTON_ALL)
    return isButtonAllPressed;

  return false;
}


boolean isLongPressed(uint8_t buttonNo)
{
  if (buttonNo == 0 || buttonNo == 1 || buttonNo == 2)
    return (buttons[buttonNo].state == BUTTON_LONGPRESSED);

  return false;
}

boolean isReleased(uint8_t buttonNo)
{
  if (buttonNo == 0 || buttonNo == 1 || buttonNo == 2)
    return (buttons[buttonNo].state == BUTTON_RELEASED);
  else if (buttonNo == BUTTON_ANY)
    return isButtonAnyReleased;
  else if (buttonNo == BUTTON_NONE)
    return !isButtonAnyReleased;
  else if (buttonNo == BUTTON_ALL)
    return isButtonAllReleased;

  return false;
}
