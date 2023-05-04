#include <Servo.h>
extern Servo myservo_thumb;
extern Servo myservo_point;
extern Servo myservo_middle;
extern Servo myservo_ring;
extern Servo myservo_pinky;
extern Servo myservo_emg;

//https://stackoverflow.com/questions/38942013/declaring-variables-in-header-files-c/38942057#38942057
// defining variables in .h and .cpp files


void MiddleFinger(void);
void FightOn(void);
void ThumbsUp(void);
void Pointer(void);
void PinkyPromis(void);
void FingerGun(void);
void Reset(void);
//this is a .h file -> the cpp file automatically compiles with it which is 
// why it is not in the top of the main program, and why you only see # include hand.h
// Basically I am just declaring everything here -> the functions and the variables

// the void in the input of the function is to tell it that it takes in 0 arguments
// the void in front of the function tells you that it does not return a value
