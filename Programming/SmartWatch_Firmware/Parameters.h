////////////// PIN CONFIGURATIONS
#define TFT_SDA    PA7
//SPI_MISO(passive)PA6
#define TFT_SCK    PA5
#define TFT_CS     PA4
#define TFT_RS     PA3
#define TFT_RST    PA2
#define TFT_LED    PB7

#define PIN_BUTTON_1   PB6
#define PIN_BUTTON_2   PB5
#define PIN_BUTTON_3   PB4

////////////// BUTTON 
#define BUTTON_LONG_PRESS_TRESHOLD 20

#define BUTTON_FREE        0
#define BUTTON_PRESSED     4
#define BUTTON_LONGPRESSED 5
#define BUTTON_RELEASED    6

#define BUTTON_ALL  7
#define BUTTON_ANY  8
#define BUTTON_NONE 9

boolean isButtonAllPressed  = false;
boolean isButtonAllReleased = false;
boolean isButtonAnyPressed  = false;
boolean isButtonAnyReleased = false;

struct Button
{
  uint8_t pinNo;
  boolean stateCurrent;
  uint8_t state;
  //boolean stateDoublePressed;

  uint8_t counterLongPress;
};

uint32_t back = 0;

Button buttons[3] = {
  {PIN_BUTTON_1, false,  0, 0},
  {PIN_BUTTON_2, false,  0, 0},
  {PIN_BUTTON_3, false,  0, 0}
};

//SEGMENT
float segWatchAlphaCurrent[4][7];
float segWatchAlphaTarget[4][7];

uint8 segWatchX = 22;
uint8 segWatchY = 34;
uint segWatchShift = 1;

uint8 segWatchDotsAlphaCurrent = 0;

uint8 segWatchLineColor = 0;
uint8 segWatchFillColor = 0;

boolean segWatchUpdated = true;
boolean segWatchIsEnabled = false;
boolean segWatchIsText = false;

boolean segWatchIsFill = false;
boolean segWatchIsLine = true;
boolean segWatchIsSmooth = true;
boolean segWatchIsAlways = true;

#define SEG_WATCH_ENABLE           1
#define SEG_WATCH_DISABLE          2

#define SEG_WATCH_ANIM_SMOOTH      5
#define SEG_WATCH_ANIM_FAST        6
#define SEG_WATCH_DRAW_ALWAYS      11
#define SEG_WATCH_DRAW_ON_UPDATE   12
#define SEG_WATCH_SHOW_FILLED      22
#define SEG_WATCH_SHOW_LINES       23
#define SEG_WATCH_SHOW_LINES_AND_FILLED       24

boolean segmentData[10][7] = {
  {true, true, true, true, true, true, false}, //0
  {false, true, true, false, false, false, false}, //1
  {true, true, false, true, true, false, true}, //2
  {true, true, true, true, false, false, true}, //3
  {false, true, true, false, false, true, true}, //4
  {true, false, true, true, false, true, true}, //5
  {true, false, true, true, true, true, true}, //6
  {true, true, true, false, false, false, false}, //7
  {true, true, true, true, true, true, true},  //8
  {true, true, true, true, false, true, true}, //9
};

uint8 segmentWidth = 38;
uint8 segmentStroke = 4;

//SCREENSAVER 
boolean ssaverEnabled = false;
uint8_t screensaver  = 0;
#define SSAVER_EMPTY 0
#define SSAVER_STAR 1
#define SSAVER_SNOW 2

#define SSAVER_EMPTY_DEFAULT_PARTICLE MAX_NUMBER_OF_PARTICLES
#define SSAVER_STAR_DEFAULT_PARTICLE  40
#define SSAVER_SNOW_DEFAULT_PARTICLE  40

////////////// PARTICLES
struct Particle
{
  float x;
  float y;
  float xSpeed;
  float ySpeed;
  float color;
  float colorSpeed;
  float size;
};

uint8_t numParticle = 0;
#define MAX_NUMBER_OF_PARTICLES 255
Particle particleArray[MAX_NUMBER_OF_PARTICLES];

//////// FPS 
unsigned long int loopTime = 0;
float delta = 0;
float deltaHedef = 0;

uint  fpsFinal = 100;


////////////// RTC - DATE/TIME
struct  Time{ 
  uint8_t second; 
  uint8_t minute; 
  uint8_t hour; 
  //uint8_t Wday;   // day of week, sunday is day 1
  uint8_t day;
  uint8_t month; 
  uint8_t year;   // offset from 1970; 
} ;

Time mytime = {0,59,21, 26,9,45};

boolean isMinuteChanged = true;
boolean isHourChanged   = true;
boolean isDayChanged    = true;
boolean isSecondChanged = true;

uint8_t DAYS[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

////////////// TEXT FONTS
fontdatatype* fontData;
uint8_t fontXsize;
uint8_t fontYsize;
uint8_t fontOffset;
uint8_t fontNumchars;

#define FONT_NORMAL  NormalFont
#define FONT_SMALL   SmallFont

uint16_t colorText   = 1;
uint16_t colorBack = 0;

////////////// MATH
#define swap(a, b) { int16_t t = a; a = b; b = t; }

////////////// LCD BACKLIGHT LED 
float ledLevelHedef = 0;
float ledLevel = 0;

////////////// LCD PARAMETERS
#define TFT_WIDTH     128
#define TFT_HEIGHT    128

#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29

#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

//////////////  COLOR DEFINITIONS
#define	c_black   0x0000
#define	c_blue    0x001F
#define	c_red     0xF800
#define	c_green   0x07E0
#define c_cyan    0x07FF
#define c_magenta 0xF81F
#define c_yellow  0xFFE0
#define c_white   0xFFFF
uint16_t c_lgray = ((200 & 0xF8) << 8) | ((200 & 0xFC) << 3) | (200 >> 3);
uint16_t c_gray = ((130 & 0xF8) << 8) | ((130 & 0xFC) << 3) | (130 >> 3);
uint16_t c_orange = ((0 & 0xF8) << 8) | ((220 & 0xFC) << 3) | (220 >> 3);

////////////// SPI
volatile uint32  *dcport, *csport;
uint32_t   cspinmask, dcpinmask;

uint16_t lineBuffer[TFT_HEIGHT];
