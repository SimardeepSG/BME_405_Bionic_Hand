int AverageFingerValues(int ThumbFSR_V, int PointFSR_V, int MiddleFSR_V, int RingFSR_V, int PinkyFSR_V) {
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

  return maxVal;
}