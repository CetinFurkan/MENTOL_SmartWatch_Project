
# MENTOL_SmartWatch_Project
 ![rotating_animation_3d](https://github.com/SkySparky/MENTOL-SmartWatch/blob/master/Media/CAD/WatchAnimation.gif?raw=true)

**Introduction**

In this project, I am planning to create a watch as smart as possible. It will be using 1.44' lcd without a touch screen. Three buttons on the side will be the control interface. There will be HM 11 BLE module with 250mAh lipo battary inside. Everything is connected to a STM32F103CB microcontroller, which is programmed via Arduino IDE, thanks to "stm32duino" bootloader.

![prototyping_image](https://github.com/SkySparky/MENTOL-SmartWatch/blob/master/Media/Prototyping/KolajSaat.jpg?raw=true)

**Hardware Details**

- STM32F103CB (ARM 32-bit Cortex™-M3, 72 mHz, 128k Flash, RTC)
- ST7735S LCD (1.44' TFT, nonTouch, 128x128 px, 65535 color)
- HM-11 BLE 4.0 (CC2541, Low Power)
- MPU 6050 (6 DOF IMU)
- Transistor for LCD's backlight led
- 3 pushbuttons
- RGB LED for notifications
- 3D Printed cover
- Coding Details

I have prepared my own code by examining other existing codes in the community. Especially for LCD stuff, there are great efforts given by Adafruit and Henning Karlsen (UTFT library). I have embedded the functions in my code without any library. Some of the notes are below:

- SPI communication with ST7735S driver of LCD is established almost perfectly
- By using DMA, the screen is updated at very fast rates!
- For easy following, code is seperated into many .ino files according to their jobs
- Buttons are handled by me to get their states when Pressed, Released, LongPressed or Free.
- For displaying texts and fonts, UTFT library is used because they have easy Font making tools!
- Adafruit's ColorWheel function is included to pick a color (it is from Adafruit's NeoPixel library)



**How to compile**
- Install Arduino IDE 1.0.5 (https://www.arduino.cc/en/Main/OldSoftwareReleases#1.0.x)
- Install stm32duino packages (https://github.com/stm32duino/Arduino_Core_STM32)
- Run and compile "Sources/SmartWatch_Firmware/SmartWatch_Firmware.ino"
