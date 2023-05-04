#include <SPI.h>      // WiFi module on feather connected throuch SPI
#include <WiFi101.h>  // header file that contains WiFi network name and password
#include <Wire.h>
#include "arduino_secrets.h"
#include "sendMessage.h"
#include "AverageFingerValues.h"
#include "ConvertAnalogFSR_To_Force.h"
#include "handGesture.h"

//Quotes for Local Libraries, <> for included libraries in Arduino

const int ThumbFSR = A0;
const int PointFSR = A1;
const int MiddleFSR = A2;
const int RingFSR = A3;
const int PinkyFSR = A4;
const int EMG_IN = A5;
int onoff = 6;

// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
const float VCC = 3.3;       // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0;  // Measured resistance of 3.3k resistor


void setup() {
  //  Serial.begin(9600);
  Serial.println("Test 00A");

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
  myservo_emg.attach(5);
  pinMode(onoff, INPUT);
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------




void loop() {

  int ThumbFSR_V = analogRead(ThumbFSR);
  int PointFSR_V = analogRead(PointFSR);
  int MiddleFSR_V = analogRead(MiddleFSR);
  int RingFSR_V = analogRead(RingFSR);
  int PinkyFSR_V = analogRead(PinkyFSR);
  int EMG = analogRead(EMG_IN);
  //These Values read what is coming in from the EMG and FSRs that are conneced via the analog inputs

  int maxForceOfFingers = AverageFingerValues(ThumbFSR_V, PointFSR_V, MiddleFSR_V, RingFSR_V, PinkyFSR_V);
  //This value will take the averageof all the FSR voltage values and spit out an average so that we can work with an average

  int val_fingers = map(maxForceOfFingers, 0, 1023, 0, 180);
  // scale it to use it with the servo (value between 0 and 180)

  if (EMG < 200) {
    EMG = 0;
  } else {
    int val_EMG = map(EMG, 0, 1023, 0, 180);
  }

  Serial.print("Thumb:");
  Serial.print(ThumbFSR_V);
  Serial.print("  ");
  Serial.print("Pointer:");
  Serial.print(PointFSR_V);
  Serial.print("  ");
  Serial.print("Middle:");
  Serial.print(MiddleFSR_V);
  Serial.print("  ");
  Serial.print("Ring:");
  Serial.print(RingFSR_V);
  Serial.print("  ");
  Serial.print("Pinky:");
  Serial.print(PinkyFSR_V);
  Serial.print("  ");
  Serial.print("Digital:");
  Serial.print(onoff);
  Serial.print("  ");
  Serial.print("EMG:");
  Serial.println(EMG);

  // sets the servo position according to the scaled value
  if (digitalRead(onoff) == LOW) {
    myservo_thumb.write(EMG);
    myservo_point.write(EMG);
    myservo_middle.write(EMG);
    myservo_ring.write(EMG);
    myservo_pinky.write(EMG);
    myservo_emg.write(val_fingers);
    Serial.println("going");
    delay(50);
  }
}
