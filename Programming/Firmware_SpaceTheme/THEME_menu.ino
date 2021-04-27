
void menuIconsSet(uint8 _id)
{
  if (_id == 0)
  {
    moveMenuRect(0, 64 - 20 - 5 , 32 - 7  , 64 + 20 + 6, 96 + 11);
    moveMenuRect(1, 64+10, 32-3,  64+12,32-5);
    moveMenuRect(2, 65-3 , 96+2,  65+3 ,96+8);

    moveMenuLine(0, 64 - 20, 32, 64 + 20, 32);
    moveMenuLine(1, 64 - 20, 32, 64 - 20, 96);
    moveMenuLine(2, 64 + 20, 32, 64 + 20, 96);
    moveMenuLine(3, 64 - 20, 96, 64 + 20, 96);

  }
  else if (_id == 1)
  {
    moveMenuRect(0, 32, 32 + 4  , 96, 96);
    moveMenuRect(1, 32+5, 32 + 26-4  , 32+5+8, 32 + 26-4+8);
    moveMenuRect(2, 32+5, 32 + 38+4  , 32+5+8, 32 + 38+4+8);

    moveMenuLine(0, 48, 32 + 14, 48 + 40, 32 + 14);
    moveMenuLine(1, 48, 32 + 26, 48 + 40, 32 + 26);
    moveMenuLine(2, 48, 32 + 38, 48 + 40, 32 + 38);
    moveMenuLine(3, 48, 32 + 50, 48 + 40, 32 + 50);


  }  
  else if (_id == 2)
  {
    moveMenuRect(1, 32, 32 + 6  , 96, 96-10);
    moveMenuRect(0, 32-2, 32 + 4  , 96+2, 96-1);
    moveMenuRect(2, 64, 32+17 , 64+6, 32+17+6);
    

    moveMenuLine(0, 32, 64-6, 32+10, 64-12);
    moveMenuLine(1, 32+10, 64 - 12, 32+32, 64+5);
    moveMenuLine(2, 32+32, 64 + 5, 32+48 , 64 -6);
    moveMenuLine(3, 32+48, 64-6 , 32+63, 64+1 );
  }
  else if (_id == 3)
  {
    moveMenuRect(0, 64 - 11 , 48-2  , 64 + 10+2, 48+36+2);
    moveMenuRect(1, 64 - 9, 48 , 64 + 10, 48+18);
    moveMenuRect(2, 64 - 9, 48+18+1 , 64 + 10, 48+36+0);

    moveMenuLine(0, 64 - 5, 38, 64 , 38 - 5);
    moveMenuLine(1, 64 + 5, 38, 64 , 38 - 5);
    
    moveMenuLine(2, 64 - 5, 94, 64 , 94 + 5);
    moveMenuLine(3, 64 + 5, 94, 64 , 94 + 5);

    //moveMenuRect(0, 64 - 2, 48 , 64 + 2, 84);
  }
}


void moveMenuRect(int8 _id , int8 _x1, int8 _y1, int8 _x2, int8 _y2)
{
  moveMenuLine(_id+4, _x1, _y1, _x2, _y2);
}

void moveMenuLine(uint8 _id, int8 _x1, int8 _y1, int8 _x2, int8 _y2)
{
  menuLines[_id * 2 + 0].xTarget = _x1;
  menuLines[_id * 2 + 0].yTarget = _y1;

  menuLines[_id * 2 + 1].xTarget = _x2;
  menuLines[_id * 2 + 1].yTarget = _y2;
}

void moveMenuDisappear()
{
  moveMenuLine(0, 64, 64, 64, 64);
  moveMenuLine(1, 64, 64, 64, 64);
  moveMenuLine(2, 64, 64, 64, 64);
  moveMenuLine(3, 64, 64, 64, 64);

  moveMenuRect(0, 64, 64, 64, 64);
  moveMenuRect(1, 64, 64, 64, 64);
  moveMenuRect(2, 64, 64, 64, 64);

  drawString(menuNames[menuActive], menuNamePos[menuActive], 120, c_black);
}

void drawMenuIconsList()
{

  for (int i = 0; i < 7; i++)
  {
    if (i<4)
    drawLine(floor(menuLines[i * 2 + 0].x), floor(menuLines[i * 2 + 0].y), floor(menuLines[i * 2 + 1].x), floor(menuLines[i * 2 + 1].y), c_black);
    else
    drawRoundRect(floor(menuLines[i * 2 + 0].x), floor(menuLines[i * 2 + 0].y), floor(menuLines[i * 2 + 1].x - menuLines[i * 2 + 0].x), floor(menuLines[i * 2 + 1].y - menuLines[i * 2 + 0].y),3, c_black);
    
    menuLines[i * 2 + 0].x += (menuLines[i * 2 + 0].xTarget - menuLines[i * 2 + 0].x) / 12.0;
    menuLines[i * 2 + 0].y += (menuLines[i * 2 + 0].yTarget - menuLines[i * 2 + 0].y) / 12.0;

    menuLines[i * 2 + 1].x += (menuLines[i * 2 + 1].xTarget - menuLines[i * 2 + 1].x) / 12.0;
    menuLines[i * 2 + 1].y += (menuLines[i * 2 + 1].yTarget - menuLines[i * 2 + 1].y) / 12.0;

    if ( abs(menuLines[i * 2 + 0].xTarget - (menuLines[i * 2 + 0].x)) < 1 )
      menuLines[i * 2 + 0].x = menuLines[i * 2 + 0].xTarget;
    if ( abs(menuLines[i * 2 + 0].yTarget - (menuLines[i * 2 + 0].y)) < 1 )
      menuLines[i * 2 + 0].y = menuLines[i * 2 + 0].yTarget;

    if ( abs(menuLines[i * 2 + 1].xTarget - (menuLines[i * 2 + 1].x)) < 1 )
      menuLines[i * 2 + 1].x = menuLines[i * 2 + 1].xTarget;
    if ( abs(menuLines[i * 2 + 1].yTarget - (menuLines[i * 2 + 1].y)) < 1 )
      menuLines[i * 2 + 1].y = menuLines[i * 2 + 1].yTarget;

    if (i<4)
    drawLine(floor(menuLines[i * 2 + 0].x), floor(menuLines[i * 2 + 0].y), floor(menuLines[i * 2 + 1].x), floor(menuLines[i * 2 + 1].y), colorCornerTime);
    else
    drawRoundRect(floor(menuLines[i * 2 + 0].x), floor(menuLines[i * 2 + 0].y), floor(menuLines[i * 2 + 1].x - menuLines[i * 2 + 0].x), floor(menuLines[i * 2 + 1].y - menuLines[i * 2 + 0].y),3, colorCornerTime);
    
  }


}
