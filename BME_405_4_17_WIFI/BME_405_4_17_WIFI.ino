#include <SPI.h>      // WiFi module on feather connected throuch SPI
#include <WiFi101.h>  // header file that contains WiFi network name and password
#include "arduino_secrets.h"
#include "sendMessage.ino"

int status = WL_IDLE_STATUS;     // status value when not connected to network
unsigned int localPort = 58431;  // choose a port for communication with the LabVIEW program
char ssid[] = SECRET_SSID;       // network name from arduino secrets.n file
char pass[] = SECRET_PSSWD;      // WPA password from arduino_secrets.h file
int ledPin = 5;                  // The pin used to control the LED
IPAddress featherIP;             // To display the IP of the feather in IP form xxx.xxx.xxx.xxx
WiFiServer server(localPort);    // creates server that listens Ior incoming connections on port localPort



#include <Servo.h>
Servo myservo_thumb;
Servo myservo_point;
Servo myservo_middle;
Servo myservo_ring;
Servo myservo_pinky;
Servo myservo_emg;

const int ThumbFSR = A0;
const int PointFSR = A1;
const int MiddleFSR = A2;
const int RingFSR = A3;
const int PinkyFSR = A4;
const int EMG_IN = A5;

// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
const float VCC = 3.3;       // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0;  // Measured resistance of 3.3k resistor


void setup() {
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
  myservo_emg.attach(5);


  while (status != WL_CONNECTED) {  // status = WL_CONNECTED when connection is established
    status = WiFi.begin(ssid, pass);
    delay(2000);  //wait for connection to be established by checking status until it is = WL_CONNECIED
  }

  Serial.print("Connected to Wifi network: ");  // Confirm feather connected to network
  Serial.println(WiFi.SSID());                  // Print network name (SSID)
  Serial.println(featherIP = WiFi.localIP());   // IP address of feather to use in LabVIEW program
  server.begin();                               // server starts listenino for incomino connections
}



int ConvertAnalogFSR(float FSR) {
  float fsrV = FSR * VCC / 1023.0;
  float fsrR = R_DIV * (VCC / fsrV - 1.0);
  float force = (1 / fsrR) * 10000000;
  return force;
}

void loop() {

  char dataBuffer;                         // character sent by the client
  WiFiClient client = server.available();  // listen for a client connected to the server
  if (!client) return;                     // if not able to create a client, end loop function

  while (client.connected()) {    // tests whether a client is connected
    while (client.available()) {  // as long as there is at least one character written by the client
      int ThumbFSR_V = analogRead(ThumbFSR);
      int PointFSR_V = analogRead(PointFSR);
      int MiddleFSR_V = analogRead(MiddleFSR);
      int RingFSR_V = analogRead(RingFSR);
      int PinkyFSR_V = analogRead(PinkyFSR);
      int EMG = analogRead(EMG_IN);

      int ThumbFSR_F = ConvertAnalogFSR(ThumbFSR_V);
      int PointFSR_F = ConvertAnalogFSR(PointFSR_V);
      int MiddleFSR_F = ConvertAnalogFSR(MiddleFSR_V);
      int RingFSR_F = ConvertAnalogFSR(RingFSR_V);
      int PinkyFSR_F = ConvertAnalogFSR(PinkyFSR_V);
    }
    //  float fsrG = 1.0 / fsrR; // Calculate conductance
    //    // Break parabolic curve down into two linear slopes:
    //    if (fsrR <= 600)
    //      force = (fsrG - 0.00075) / 0.00000032639;
    //    else
    //      force =  fsrG / 0.000000642857;

    int myArray[] = { ThumbFSR_V, PointFSR_V, MiddleFSR_V, RingFSR_V, PinkyFSR_V };
    int maxVal = myArray[0];
    int arraySize = sizeof(myArray) / sizeof(myArray[0]);
    //The sizeof operator returns the number of **bytes** in a variable type, or the number of bytes occupied by an array.
    //this is why we divide by size of myArray[0] -> that number should have the same amount of bytes as the rest


    for (int i = 0; i < arraySize; i++) {

      maxVal = max(myArray[i], maxVal);

      //Calculates the maximum of two numbers.
      //so everytime maxVal is Array 0 and is first compared to Array i, then array i
      // increases and and is again compared to previous max val
      //https://reference.arduino.cc/reference/en/language/functions/math/max/
      //https://reference.arduino.cc/reference/en/language/functions/math/max/
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
    Serial.print("MaxVal:");
    Serial.print(maxVal);
    Serial.print("  ");
    Serial.print("EMG:");
    Serial.println(EMG);
    //note to self: spaces in legend objects = another varibale, do not add them when doing multigraph

    // scale it to use it with the servo (value between 0 and 180)
    int val_fingers = map(maxVal, 0, 1023, 0, 180);
    // int val_point = map(maxVal, 0, 1023, 0, 180);
    // int val_middle = map(maxVal, 0, 1023, 0, 180);
    // int val_ring = map(maxVal, 0, 1023, 0, 180);
    // int val_pinky = map(maxVal, 0, 1023, 0, 180);

    if (EMG < 200) {
      EMG = 0;
    } else {
      int val_EMG = map(EMG, 0, 1023, 0, 180);
    }



    // sets the servo position according to the scaled value
    myservo_thumb.write(EMG);
    myservo_point.write(EMG);
    myservo_middle.write(EMG);
    myservo_ring.write(EMG);
    myservo_pinky.write(EMG);
    myservo_emg.write(val_fingers);
    delay(50);
  }
