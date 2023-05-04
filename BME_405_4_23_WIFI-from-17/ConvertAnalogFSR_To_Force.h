int ConvertAnalogFSR(float FSR) {
  int VCC;
  int R_DIV;
  float fsrV =  FSR *  VCC / 1023.0;
  float fsrR =  R_DIV * (VCC /  fsrV - 1.0);
  float force = (1 / fsrR) * 10000000;
  return force;
  // int ThumbFSR_F = ConvertAnalogFSR(ThumbFSR_V);
  // int PointFSR_F = ConvertAnalogFSR(PointFSR_V);
  // int MiddleFSR_F = ConvertAnalogFSR(MiddleFSR_V);
  // int RingFSR_F = ConvertAnalogFSR(RingFSR_V);
  // int PinkyFSR_F = ConvertAnalogFSR(PinkyFSR_V);
}