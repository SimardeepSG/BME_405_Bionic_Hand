#include "handGesture.h"
// I need to include the hand.h defined variables

//https://stackoverflow.com/questions/38942013/declaring-variables-in-header-files-c/38942057#38942057
// defining variables in .h and .cpp files

Servo myservo_thumb;
Servo myservo_point;
Servo myservo_middle;
Servo myservo_ring;
Servo myservo_pinky;
Servo myservo_emg;


void MiddleFinger(void) {
  myservo_thumb.write(0);
  myservo_point.write(0);
  myservo_middle.write(1023);
  myservo_ring.write(0);
  myservo_pinky.write(0);
}

void FightOn(void) {
  myservo_thumb.write(0);
  myservo_point.write(1023);
  myservo_middle.write(1023);
  myservo_ring.write(0);
  myservo_pinky.write(0);
}

void ThumbsUp(void) {
  myservo_thumb.write(1023);
  myservo_point.write(0);
  myservo_middle.write(0);
  myservo_ring.write(0);
  myservo_pinky.write(0);
}

void Pointer(void) {
  myservo_thumb.write(0);
  myservo_point.write(1023);
  myservo_middle.write(0);
  myservo_ring.write(0);
  myservo_pinky.write(0);
}
void PinkyPromis(void) {
  myservo_thumb.write(0);
  myservo_point.write(0);
  myservo_middle.write(0);
  myservo_ring.write(0);
  myservo_pinky.write(1023);
}
void FingerGun(void) {
  myservo_thumb.write(1023);
  myservo_point.write(1023);
  myservo_middle.write(0);
  myservo_ring.write(0);
  myservo_pinky.write(0);
}
