// Function to send a message to the sensor. Includes address, array of elements to spell the command, and array size
#include <Wire.h>

void sendMessage (int address, int command_array[], int array_size) {

  Wire.beginTransmission(address) ;
    for (int i=0; i < array_size; i++)  {
    Wire.write(command_array[i]);
    }
  Wire.endTransmission();
}