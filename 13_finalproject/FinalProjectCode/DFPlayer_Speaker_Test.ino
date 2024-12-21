
#include "DFRobotDFPlayerMini.h"
//#include <SoftwareSerial.h> // No longer using it.

DFRobotDFPlayerMini myDFPlayer;
#define RXD2 5
#define TXD2 4


void setup()
{
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(115200);
  delay(200); // My preference for print stability
  

  if (!myDFPlayer.begin(Serial2)) {// Start communication with DFPlayer
  // myDFPlayer.begin(Serial1, true, false); // Start communication with DFPlayer
    Serial.println("ERROR");
  }

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  delay(1000); // Add this to allow player to fully initialise

  myDFPlayer.volume(15);  //Set volume value. From 0 to 30

  Serial.println("setup ended"); // I like this reassurance
}

void loop()
{
  //  myDFPlayer.play(001); // Ensure that your files have been renamed to 001, 002, etc.
  myDFPlayer.play(1);

  delay(5000); // If you actually want to hear anything each time
}