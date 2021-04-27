#include <Wire.h>

unsigned short num;
short raw_data[5]={
  0, };
short sub_os_data[5];
signed short ret;
short act_os_d[4]={
  0x03FF, 0x03FF, 0x03FF, 0x03FF};

/////////////// Constant parameters ///////
const int STATE_ONE 	          = 1;
const int STATE_TWO 	          = 2;
const int STATE_THREE 		  = 3;
const short OVER_FLOW_DATA 	  = 4095;
const int DIR_RIGHT 		  = 0x8;
const int DIR_LEFT 		  = 0x4;
const int DIR_TOP 		  = 0x2;
const int DIR_BOTTOM 	          = 0x1;
const int SPEED_HIGH 		  = 0x2;
const int SPEED_MID 		  = 0x1;

const int COUNTS_HIGH_SP          = 6;        //Edit this value for tuning sensitivity of high speed sensing
const int COUNTS_MID_SP	          = 10;       //Edit this value for tuning sensitivity of medium speed sensing

struct gs_params{
  //// Temporal parameters for Direction Judgement ////
  float max_x1, min_x1, max_y1, min_y1;
  float max_x2, min_x2, max_y2, min_y2, diff_max_x, diff_max_y;
  unsigned int x_plus, x_minus, y_plus, y_minus;
  unsigned char gs_state;
  int speed_counts;

  //// Thresholds depending on the performance ////
  signed short ignore_diff_th;
  signed short ignore_z_th;//unsigned 
  double ratio_th;//float

  //// Parameters for active offset cancelation ////
  int active_osc_on;
  int allowable_variation;
  int acquisition_num;
};

void clearGSparams(struct gs_params *p_gs) {
  p_gs->x_plus  = 0;
  p_gs->x_minus = 0;
  p_gs->y_plus  = 0;
  p_gs->y_minus = 0;
  p_gs->max_x1  = 0;
  p_gs->min_x1  = 0;
  p_gs->max_y1  = 0;
  p_gs->min_y1  = 0;
  p_gs->max_x2  = 0;
  p_gs->min_x2  = 0;
  p_gs->max_y2  = 0;
  p_gs->min_y2  = 0;
  p_gs->diff_max_x = 0;
  p_gs->diff_max_y = 0;
  p_gs->speed_counts= 0;
  p_gs->gs_state = STATE_ONE;
}


void initGSparams(struct gs_params *p_gs){
  clearGSparams(p_gs);
  p_gs->ignore_z_th 		= 20;
  p_gs->ignore_diff_th 		= 10;
  p_gs->ratio_th 		= 10;
  p_gs->active_osc_on 		= 1;
  p_gs->allowable_variation 	= 30;
  p_gs->acquisition_num		= 10;
}

void getActiveOffset(short *raw_data, short *act_os_d, struct gs_params *p_gs){
  static int act_os_counts=0;
  static short max_d[4]={
    0                };
  static short min_d[4]={
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF                };
  static int avg_d[4]={
    0                };

  if( *(raw_data+4) < 1023)

  {
    //// The last measurement of offset
    if(act_os_counts == p_gs->acquisition_num -1){
      for(num=0;num<4;num++){
        avg_d[num] = avg_d[num] + *(raw_data+num);
        if(*(raw_data+num) > max_d[num]){
          max_d[num] = *(raw_data+num);
        }
        if(*(raw_data+num) < min_d[num]){
          min_d[num] = *(raw_data+num);
        }
      }
      for(num=0;num<4;num++){
        avg_d[num] = avg_d[num] - max_d[num] - min_d[num];
        avg_d[num] = avg_d[num]/(p_gs->acquisition_num-2);

        if( (max_d[num] < avg_d[num] + p_gs->allowable_variation) && 
          (min_d[num] + p_gs->allowable_variation > avg_d[num])){
          if(max_d[num] < (p_gs->ignore_z_th/4)){
            *(act_os_d+num) = max_d[num];
          }
          else{
            *(act_os_d+num) = max_d[num] -(p_gs->ignore_z_th/4);
          }
        }
      }
      act_os_counts = 0;
      //// The first measurement of offset
    }
    else if(act_os_counts == 0){
      for(num=0;num<4;num++){
        avg_d[num] = *(raw_data+num);
        max_d[num] = *(raw_data+num);
        min_d[num] = *(raw_data+num);
      }
      act_os_counts++;
    }
    else{
      for(num=0;num<4;num++){
        avg_d[num] = avg_d[num] + *(raw_data+num);
        if(*(raw_data+num) > max_d[num]){
          max_d[num] = *(raw_data+num);
        }
        if(*(raw_data+num) < min_d[num]){
          min_d[num] = *(raw_data+num);
        }
      }
      act_os_counts++;  
    }

  }
  return;
}

signed short getDirection(signed short *sub_os_data, struct gs_params *p_gs){
  signed short data_x, data_y;
  signed short data_z;
  float ratio_x, ratio_y;
  signed short direction_res = 0;

  data_y = 0;
  data_x = 0;
  data_z = 0;

  //// Diff calculation ////
  data_y = sub_os_data[2] + sub_os_data[3] - sub_os_data[0] - sub_os_data[1];
  if( ((data_y > -(p_gs->ignore_diff_th)) && (data_y < (p_gs->ignore_diff_th))) ||
    (sub_os_data[0] == OVER_FLOW_DATA) || (sub_os_data[1] == OVER_FLOW_DATA) ||
    (sub_os_data[2] == OVER_FLOW_DATA) || (sub_os_data[3] == OVER_FLOW_DATA) )
  {
    data_y = 0;
  }
  data_x = sub_os_data[1] + sub_os_data[2] - sub_os_data[0] - sub_os_data[3];
  if( ((data_x > -(p_gs->ignore_diff_th)) && (data_x < (p_gs->ignore_diff_th))) ||
    (sub_os_data[0] == OVER_FLOW_DATA) || (sub_os_data[1] == OVER_FLOW_DATA) ||
    (sub_os_data[2] == OVER_FLOW_DATA) || (sub_os_data[3] == OVER_FLOW_DATA) )
  {
    data_x = 0;
  }
  for(num=0; num<4; num++){
    data_z += sub_os_data[num];
  }

  //// Ratio calculation ////
  if(data_z == 0){
    ratio_y = 0;
    ratio_x = 0;
  }
  else{
    ratio_y = (float)data_y*100 / (float)data_z;
    ratio_x = (float)data_x*100 / (float)data_z;
  }

  //// Judgement start ////
  switch (p_gs->gs_state)
  {
  case STATE_ONE:
    if(data_z >= p_gs->ignore_z_th){
      if(ratio_x > (p_gs->ratio_th)){
        p_gs->x_plus = 1;
        p_gs->max_x1 = ratio_x;
      }
      else{
        p_gs->x_plus = 0;
        p_gs->max_x1 = 0;
      }

      if(ratio_x < -(p_gs->ratio_th)){
        p_gs->x_minus = 1 ;
        p_gs->min_x1 = ratio_x;
      }
      else{
        p_gs->x_minus = 0;
        p_gs->min_x1 = 0;
      }

      if(ratio_y > (p_gs->ratio_th)){
        p_gs->y_plus = 1;
        p_gs->max_y1 = ratio_y;
      }
      else{
        p_gs->y_plus = 0;
        p_gs->max_y1 = 0;
      }

      if(ratio_y < -(p_gs->ratio_th)){
        p_gs->y_minus = 1;
        p_gs->min_y1 = ratio_y;
      }
      else{
        p_gs->y_minus = 0;
        p_gs->min_y1 = 0;
      }
    }

    if( (p_gs->x_plus > 0) | (p_gs->x_minus > 0) |
      (p_gs->y_plus > 0) | (p_gs->y_minus > 0) )
    {
      p_gs->gs_state = STATE_TWO;
    }
    else{
      p_gs->gs_state = STATE_ONE;
    }

    break;

  case STATE_TWO:
    if( (data_z < p_gs->ignore_z_th) )
    {
      clearGSparams(p_gs);
    }
    else if( 
    ((p_gs->x_plus ) && (ratio_x < -(p_gs->ratio_th))) ||
      ((p_gs->x_minus) && (ratio_x >  (p_gs->ratio_th))) ||
      ((p_gs->y_plus ) && (ratio_y < -(p_gs->ratio_th))) ||
      ((p_gs->y_minus) && (ratio_y >  (p_gs->ratio_th))) )
    {
      if(ratio_x > (p_gs->ratio_th)){
        p_gs->max_x2 = ratio_x;
      }
      else{
        p_gs->max_x2 = 0;
      }

      if(ratio_x < -(p_gs->ratio_th)){
        p_gs->min_x2 = ratio_x;
      }
      else{
        p_gs->min_x2 = 0;
      }

      if(ratio_y > (p_gs->ratio_th)){
        p_gs->max_y2 = ratio_y;
      }
      else{
        p_gs->max_y2 = 0;
      }

      if(ratio_y < -(p_gs->ratio_th)){
        p_gs->min_y2 = ratio_y;
      }
      else{
        p_gs->min_y2 = 0;
      }
      p_gs->gs_state = STATE_THREE;

    }
    else {
      if( (ratio_x > (p_gs->max_x1)) && (ratio_x > (p_gs->ratio_th))){
        p_gs->max_x1 = ratio_x;
        p_gs->x_plus = 1;
      }
      else if( (ratio_x < (p_gs->min_x1)) & (ratio_x < -(p_gs->ratio_th)) ){
        p_gs->min_x1 = ratio_x;
        p_gs->x_minus = 1;
      }
      if( (ratio_y > (p_gs->max_y1)) & (ratio_y > (p_gs->ratio_th)) ){
        p_gs->max_y1 = ratio_y;
        p_gs->y_plus = 1;
      }
      else if( (ratio_y < (p_gs->min_y1)) & (ratio_y < -(p_gs->ratio_th)) ){
        p_gs->min_y1 = ratio_y;
        p_gs->y_minus =1;
      }
      if( p_gs->x_plus && p_gs->x_minus){
        if((p_gs->max_x1) > -(p_gs->min_x1)) {
          p_gs->x_plus  = 1;
          p_gs->x_minus = 0;
        }
        else {		 
          p_gs->x_plus  = 0;
          p_gs->x_minus = 1;
        }
      }
      if( p_gs->y_plus && p_gs->y_minus){
        if((p_gs->max_y1) > -(p_gs->min_y1)) {
          p_gs->y_plus  = 1;
          p_gs->y_minus = 0;
        }
        else {
          p_gs->y_plus  = 0;
          p_gs->y_minus = 1;
        }
      }
      p_gs->gs_state = STATE_TWO;
    }
    break;

  case STATE_THREE:
    if( data_z < (p_gs->ignore_z_th) )
    {
      if( (p_gs->x_plus) & (p_gs->min_x2 < -(p_gs->ratio_th))){
        p_gs->diff_max_x = p_gs->max_x1 - p_gs->min_x2;
      }
      else if( (p_gs->x_minus) & (p_gs->max_x2 > p_gs->ratio_th) ){
        p_gs->diff_max_x = p_gs->max_x2 - p_gs->min_x1;
      }
      else {
        p_gs->diff_max_x = 0;
      }

      if( (p_gs->y_plus) & (p_gs->min_y2 < -(p_gs->ratio_th)) ){
        p_gs->diff_max_y = p_gs->max_y1 - p_gs->min_y2;
      }
      else if( (p_gs->y_minus) & (p_gs->max_y2 > p_gs->ratio_th) ){
        p_gs->diff_max_y = p_gs->max_y2 - p_gs->min_y1;
      }
      else{
        p_gs->diff_max_y = 0;
      }

      //// Final direction Judgement ////
      if( p_gs->diff_max_x >= p_gs->diff_max_y){
        if(p_gs->x_plus == 1){
          direction_res = DIR_RIGHT; 
        }
        else {
          direction_res = DIR_LEFT;
        }
      }
      else{
        if(p_gs->y_plus == 1){
          direction_res = DIR_TOP;
        }
        else {
          direction_res = DIR_BOTTOM;
        }
      }

      if(p_gs->speed_counts < (signed short)COUNTS_HIGH_SP){
        direction_res |=((signed short)SPEED_HIGH<<4);
      }
      else if(p_gs->speed_counts < (signed short)COUNTS_MID_SP){
        direction_res |=((signed short)SPEED_MID<<4);
      }

      clearGSparams(p_gs);

    }
    else {
      if( (ratio_x > p_gs->max_x2) & (ratio_x > p_gs->ratio_th) ){
        p_gs->max_x2 = ratio_x;
      }
      else if ( (ratio_x < (p_gs->min_x2)) & (ratio_x < -(p_gs->ratio_th))){
        p_gs->min_x2 = ratio_x;
      }
      if( (ratio_y > (p_gs->max_y2)) & (ratio_y > (p_gs->ratio_th)) ){
        p_gs->max_y2 = ratio_y;
      }
      else if( (ratio_y < (p_gs->min_y2)) & (ratio_y < -(p_gs->ratio_th))){
        p_gs->min_y2 = ratio_y;
      }
      p_gs->gs_state = STATE_THREE;
    }

    break;

  default:
    break;
  }

  //// Speed Judgement counts////

  if(p_gs->gs_state > STATE_ONE){
    p_gs->speed_counts++;
  }
  else{
    p_gs->speed_counts = 0;
  }

  return direction_res;
}// End of getDirection()

////////////////////Above is the Gesture Calculation/////////////////////////

void I2C_write(unsigned char add,unsigned char reg,unsigned char data) {
  Wire.beginTransmission(add);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission(1);  
}

struct gs_params st_gs;
void setup()
{
  ////////IO Init
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output

  ///////Sensor Init
  Wire.beginTransmission(0x45);
  Wire.write(0x00);
  Wire.write(0xc0);
  Wire.write(0x62);
  Wire.write(0x01);
  Wire.write(0x50);
  Wire.endTransmission(1);

  initGSparams(&st_gs);
}

void loop()
{
  ////Getting Gesture Data from Sensor
  unsigned char i;
  unsigned short GD0=0,GD1=0,GD2=0,GD3=0,GD4=0;
  Wire.beginTransmission(0x45);
  Wire.write(0x10);
  Wire.endTransmission(0);
  Wire.requestFrom(0x45, 10);    // request 10 bytes from slave device

  i=0;
  while(Wire.available())
  { 
    unsigned char c = Wire.read(); // receive a byte as character
    switch (i) {
    case 0:
      GD0=c;
      break;  
    case 1:
      GD0+=(((unsigned short)c)<<8);
      break; 
    case 2:
      GD1=c;
      break; 
    case 3:
      GD1+=(((unsigned short)c)<<8);
      break; 
    case 4:
      GD2=c;
      break; 
    case 5:
      GD2+=(((unsigned short)c)<<8);
      break; 
    case 6:
      GD3=c;
      break; 
    case 7:
      GD3+=(((unsigned short)c)<<8);
      break; 
    case 8:
      GD4=c;
      break; 
    case 9:
      GD4+=(((unsigned short)c)<<8);
      break; 
    }
    i++;
  }

  raw_data[0]=GD0;
  raw_data[1]=GD1;
  raw_data[2]=GD2;
  raw_data[3]=GD3;
  if( (raw_data[0] & 0x8000) || (raw_data[1] & 0x8000) ||
    (raw_data[2] & 0x8000) || (raw_data[3] & 0x8000) ){
    for(num=0;num<4;num++){
      raw_data[num] = 0;
    }
  }

  //// Active offset calibration ////
  if(st_gs.active_osc_on == 1){
    getActiveOffset(&raw_data[0], &act_os_d[0], &st_gs);
    //// Offset subtraction ////
    for(num=0;num<4;num++){
      if(raw_data[num] > act_os_d[num]){
        sub_os_data[num] = raw_data[num] - act_os_d[num];
      }
      else{
        sub_os_data[num] = 0;
      }
    }
  }
  else{
    for(num=0;num<4;num++){
      sub_os_data[num] = raw_data[num];
    }
  }

  //// Data Clipping ////
  for(num=0;num<4;num++){
    if(sub_os_data[num] > OVER_FLOW_DATA){
      sub_os_data[num] = OVER_FLOW_DATA;
    }
  }

  //// Calculation & get direction results ////
  ret = getDirection(&sub_os_data[0], &st_gs);


  //////Display Result
  //////Use Serial Monitor with baudrate 115200 can read the result, the result is also displayed by the Leds cross
  //////User may modify codes below
  if(ret>0) {
    if (ret&0x01) {
      Serial.print("Bottom, ");
    }
    if (ret&0x02) {
      Serial.print("Top,    ");
    }
    if (ret&0x04) {
      Serial.print("Left,   ");
    }
    if (ret&0x08) {
      Serial.print("Right,  ");
    }
    switch (ret&0xF0) {
    case 0x20:
      Serial.println("High"); 
      break;  
    case 0x10:
      Serial.println("Mid");
      break;  
    default:
      Serial.println("Low");
      break;
    }
  }


  delay(10);
}












































