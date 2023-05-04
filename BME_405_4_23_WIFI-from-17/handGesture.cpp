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

void Reset(void){
  myservo_thumb.write(125);
  myservo_point.write(125);
  myservo_middle.write(125);
  myservo_ring.write(125);
  myservo_pinky.write(125);

}


void MiddleFinger(void) {
  myservo_thumb.write(0);
  myservo_point.write(0);
  myservo_middle.write(120);
  myservo_ring.write(0);
  myservo_pinky.write(0);
}
//servos can only do 180 steps, you are feding the umber of steps it does, not the degrees it rotates, so do (180/270)*180

void FightOn(void) {
  myservo_thumb.write(0);
  myservo_point.write(125);
  myservo_middle.write(125);
  myservo_ring.write(0);
  myservo_pinky.write(0);
}

void ThumbsUp(void) {
  myservo_thumb.write(0);
  myservo_point.write(125);
  myservo_middle.write(0);
  myservo_ring.write(0);
  myservo_pinky.write(125);
}

void Pointer(void) {
  myservo_thumb.write(0);
  myservo_point.write(125);
  myservo_middle.write(0);
  myservo_ring.write(0);
  myservo_pinky.write(0);
}
void PinkyPromis(void) {
  myservo_thumb.write(0);
  myservo_point.write(0);
  myservo_middle.write(0);
  myservo_ring.write(0);
  myservo_pinky.write(125);
}
void FingerGun(void) {
  myservo_thumb.write(125);
  myservo_point.write(125);
  myservo_middle.write(0);
  myservo_ring.write(0);
  myservo_pinky.write(0);
}

