void bluetooth_init() {
  Serial1.begin(38400);
}

void bluetooth_loop() {
  while (Serial1.available())
  {
    char in = Serial1.read();

    if (in == 255)
    {


    }

  }

}
