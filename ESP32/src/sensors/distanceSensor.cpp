#include "distanceSensor.h"

long microsecondsToMilimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 2.9 / 2;
}

long DistanceSensor::getPINGDistanceValue(){
    // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, mm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(PING_DIST_PIN, OUTPUT);
  digitalWrite(PING_DIST_PIN, LOW);
  
  delayMicroseconds(2);
  digitalWrite(PING_DIST_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(PING_DIST_PIN, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(PING_DIST_PIN, INPUT);
  duration = pulseIn(PING_DIST_PIN, HIGH);

  // convert the time into a distance
  //inches = microsecondsToInches(duration);
  // cm = microsecondsToCentimeters(duration);
  mm = microsecondsToMilimeters(duration);

  return mm; 
}
