#include <SPI.h>      // WiFi module on feather connected throuch SPI
#include <WiFi101.h>  // header file that contains WiFi network name and password
#include <Wire.h>
#include "arduino_secrets.h"
#include "sendMessage.h"
#include "AverageFingerValues.h"
#include "ConvertAnalogFSR_To_Force.h"
#include "handGesture.h"

//Quotes for Local Libraries, <> for included libraries in Arduino

int status = WL_IDLE_STATUS;     // status value when not connected to network
unsigned int localPort = 58431;  // choose a port for communication with the LabVIEW program
char ssid[] = SECRET_SSID;       // network name from arduino secrets.n file
char pass[] = SECRET_PSSWD;      // WPA password from arduino_secrets.h file
int ledPin = 5;                  // The pin used to control the LED
IPAddress featherIP;             // To display the IP of the feather in IP form xxx.xxx.xxx.xxx
WiFiServer server(localPort);    // creates server that listens Ior incoming connections on port localPort

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

void loop() {
  char dataBuffer;                         // character sent by the client
  WiFiClient client = server.available();  // listen for a client connected to the server
  if (!client) return;                     // if not able to create a client, end loop function

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
  // sets the servo position according to the scaled value

  while (client.connected()) {     // tests whether a client is connected
    while (client.available()) {   // as long as there is at least one character written by the client
      dataBuffer = client.read();  // read the character
    }
    Serial.println(dataBuffer);
    switch (dataBuffer) {
      case 'M':
        MiddleFinger();
        break;
      case 'F':
        FightOn();
        break;
      case 'T':
        ThumbsUp();
        break;
      case 'O':
        Pointer();
        break;
      case 'P':
        PinkyPromis();
        break;
      case 'G':
        FingerGun();
        break;
      default:
        myservo_thumb.write(EMG);
        myservo_point.write(EMG);
        myservo_middle.write(EMG);
        myservo_ring.write(EMG);
        myservo_pinky.write(EMG);
        myservo_emg.write(val_fingers);
        delay(50);
        break;
    }
  }
}
