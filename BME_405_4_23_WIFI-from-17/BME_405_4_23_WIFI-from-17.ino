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
  Serial.println("Test 0A");


  WiFi.setPins(8, 7, 4, 2);         // Configure pins for Adafruit AIWINC1500 Feather
  while (status != WL_CONNECTED) {  // status = WL_CONNECTED when connection is established
    status = WiFi.begin(ssid, pass);
    Serial.println("Test 0B");

    delay(2000);  //wait for connection to be established by checking status until it is = WL_CONNECIED
  }

  Serial.println("Test 0C");

  Serial.print("Connected to Wifi network: ");  // Confirm feather connected to network
  Serial.println(WiFi.SSID());                  // Print network name (SSID)
  Serial.println(featherIP = WiFi.localIP());   // IP address of feather to use in LabVIEW program
  server.begin();                               // server starts listenino for incomino connections
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------




void loop() {
  char dataBuffer = 'Z';                   // character sent by the client
  WiFiClient client = server.available();  // listen for a client connected to the server
  while (client.connected()) {             // tests whether a client is connected

    while (client.available()) {   // as long as there is at least one character written by the client
      dataBuffer = client.read();  // read the character
    }
    Serial.println(dataBuffer);


    int ThumbFSR_V = analogRead(ThumbFSR);
    int PointFSR_V = analogRead(PointFSR);
    int MiddleFSR_V = analogRead(MiddleFSR);
    int RingFSR_V = analogRead(RingFSR);
    int PinkyFSR_V = analogRead(PinkyFSR);
    int EMG = analogRead(EMG_IN);
    //These Values read what is coming in from the EMG and FSRs that are conneced via the analog inputs

    int maxForceOfFingers = AverageFingerValues(ThumbFSR_V, PointFSR_V, MiddleFSR_V, RingFSR_V, PinkyFSR_V);
    //This value will take the averageof all the FSR voltage values and spit out an average so that we can work with an average
    int val_maxForceGraduated = map(maxForceOfFingers, 0, 1023, 0, 100);


    int val_maxForce = map(maxForceOfFingers, 0, 1023, 0, 180);
    // scale it to use it with the servo (value between 0 and 180)

    if (EMG < 200) {
      EMG = 0;
    } else {
      int val_EMG = map(EMG, 0, 1023, 0, 180);
    }

    String stringOfValues = String(ThumbFSR_V) + "," + String(PointFSR_V) + "," + String(MiddleFSR_V) + "," + String(RingFSR_V) + "," + String(PinkyFSR_V) + "," + String(EMG) + "," + String(val_maxForceGraduated);
    Serial.println(stringOfValues);


    // sets the servo position according to the scaled value


    switch (dataBuffer) {
      case 'M':
        Reset();
        delay(100);
        MiddleFinger();
        break;
      case 'F':
        Reset();
        delay(100);

        FightOn();
        break;
      case 'T':
        Reset();
        delay(100);

        ThumbsUp();
        break;
      case 'O':
        Reset();
        delay(100);

        Pointer();
        break;
      case 'P':
        Reset();
        delay(100);

        PinkyPromis();
        break;
      case 'G':
        Reset();
        delay(100);

        FingerGun();
        break;
      case 'R':
        Reset();
        break;
      case 'S':
        client.stop();  // disconnect the client from the server if the letter is an 'S'
        WiFi.end();     // also disconnect the WiFi module from the network
        Serial.println("Disconnected from network");
        break;
      default:
        if (EMG > 300) {
          myservo_thumb.write(125);
          myservo_point.write(125);
          myservo_middle.write(125);
          myservo_ring.write(125);
          myservo_pinky.write(125);
          myservo_emg.write(val_maxForce);
          delay(5000)
        }
        myservo_emg.write(val_maxForce);

        Serial.println("going");
        client.println(stringOfValues);
        delay(100);
        break;
    }
    dataBuffer = 'Z';
  }
}
