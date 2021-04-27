void writeCommand(uint8 _c) {
  *dcport &=  ~dcpinmask;
  *csport &=  ~cspinmask;
  
  SPI.write(_c);
  
  *csport |= cspinmask;
}

void writeData(uint8 _c) {
  *dcport |=  dcpinmask;
  *csport &= ~cspinmask;
  
  SPI.write(_c);
  
  *csport |= cspinmask;
}

void writeData(uint32 _size, uint8* _buf) {
  *dcport |=  dcpinmask;
  *csport &= ~cspinmask;
  
  SPI.write(_buf, _size);
  
  *csport |= cspinmask;
}

void writeCommand(uint8 _cmd, uint8 _param) {
  writeCommandAndParms(_cmd, 1, &_param);
}

void writeCommand(uint8 _cmd, uint8 _param1, uint8 _param2) {
  uint8 params[] = {_param1, _param2};
  
  writeCommandAndParms(_cmd, 2, params);
}

void writeCommand(uint8 _cmd, uint8 _param1, uint8 _param2, uint8 _param3) {
  uint8 params[] = {_param1, _param2, _param3};
  writeCommandAndParms(_cmd, 3, params);
}

void writeCommandAndParms(uint8 _c, uint32 _numparms, uint8* _params) {
  writeCommand(_c);
  writeData(_numparms, _params);
}

