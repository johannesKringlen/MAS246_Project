#include "WString.h"
/*Logger
This class add a timestamp to the log.
*/

#pragma once
void logMessage(String message) 
{
unsigned long totalMilliseconds = millis();
unsigned long totalSeconds = totalMilliseconds / 1000UL;
unsigned long hours = totalSeconds / 3600UL;
unsigned long minutes = (totalSeconds % 3600UL) / 60UL;
unsigned long seconds = totalSeconds % 60UL;
unsigned long milliseconds =
    totalMilliseconds
    - hours * 3600000UL
    - minutes * 60000UL
    - seconds * 1000UL;

  char stamp[16];
  snprintf(stamp, sizeof(stamp), "%02lu:%02lu:%02lu.%03lu",
           hours, minutes, seconds, milliseconds);

  Serial.print("[");
  Serial.print(stamp);
  Serial.print("] ");
  Serial.println(message);
}