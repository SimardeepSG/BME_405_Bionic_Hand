#include <Servo.h>
Servo myservo_thumb;
Servo myservo_point;
Servo myservo_middle;
Servo myservo_ring;
Servo myservo_pinky;

const int ThumbFSR = A0;
const int PointFSR = A1;
const int MiddleFSR = A2;
const int RingFSR = A3;
const int PinkyFSR = A4;
const int EMG_IN = A5;

// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
const float VCC = 3.3; // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0; // Measured resistance of 3.3k resistor


void setup() 
{
  Serial.begin(9600);
  pinMode(ThumbFSR, INPUT);
  pinMode(PointFSR, INPUT);
  pinMode(MiddleFSR, INPUT);
  pinMode(RingFSR, INPUT);
  pinMode(PinkyFSR, INPUT);
  pinMode(EMG_IN, INPUT);
  myservo_thumb.attach(9);
  myservo_point.attach(10);
  myservo_middle.attach(11);
  myservo_ring.attach(12);
  myservo_pinky.attach(13);

}

int ConvertAnalogFSR(float FSR) {
  float fsrV = FSR * VCC / 1023.0;
  float fsrR = R_DIV * (VCC / fsrV - 1.0);
  float force = (1/fsrR)*10000000;
  return force;
}

void loop() 
{
  int ThumbFSR_V = analogRead(ThumbFSR);
  int PointFSR_V = analogRead(PointFSR);
  int MiddleFSR_V = analogRead(MiddleFSR);
  int RingFSR_V = analogRead(RingFSR);
  int PinkyFSR_V = analogRead(PinkyFSR);
  int EMG = analogRead(EMG_IN);

  int ThumbFSR_F = ConvertAnalogFSR(ThumbFSR_V);
  int PointFSR_F= ConvertAnalogFSR(PointFSR_V);
  int MiddleFSR_F = ConvertAnalogFSR(MiddleFSR_V);
  int RingFSR_F = ConvertAnalogFSR(RingFSR_V);
  int PinkyFSR_F = ConvertAnalogFSR(PinkyFSR_V);
//  float fsrG = 1.0 / fsrR; // Calculate conductance
//    // Break parabolic curve down into two linear slopes:
//    if (fsrR <= 600) 
//      force = (fsrG - 0.00075) / 0.00000032639;
//    else
//      force =  fsrG / 0.000000642857;
    Serial.print("Thumb:"); Serial.print(ThumbFSR_V);
    Serial.print("  ");
    Serial.print("Pointer:"); Serial.print(PointFSR_V);
    Serial.print("  ");
    Serial.print("Middle:"); Serial.print(MiddleFSR_V);
    Serial.print("  ");
    Serial.print("Ring:"); Serial.print(RingFSR_V);
    Serial.print("  ");
    Serial.print("Pinky:"); Serial.print(PinkyFSR_V);
    Serial.print("  ");
    Serial.print("EMG:"); Serial.println(EMG);
    //note to self: spaces in legend objects = another varibale, do not add them when doing multigraph 
    
    // scale it to use it with the servo (value between 0 and 180)
    int val_thumb = map(ThumbFSR_V, 0, 1023, 0, 180); 
    int val_point = map(PointFSR_V, 0, 1023, 0, 180);
    int val_middle = map(MiddleFSR_V, 0, 1023, 0, 180);
    int val_ring = map(RingFSR_V, 0, 1023, 0, 180);
    int val_pinky = map(PinkyFSR_V, 0, 1023, 0, 180);

    
    // sets the servo position according to the scaled value
    myservo_thumb.write(val_thumb);
    myservo_point.write(val_point);
    myservo_middle.write(val_middle);
    myservo_ring.write(val_ring);
    myservo_pinky.write(val_pinky);
    
            
}
