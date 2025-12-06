#include <Timer.h>      // Include the Timer library
Timer t;                // Create a Timer object
#define FAN 12          // The LED (or fan) is connected to pin 12
void setup() {
  pinMode(FAN, OUTPUT);       // Set pin 12 as output
  digitalWrite(FAN, LOW);     // Make sure LED/FAN starts OFF
  startCycle();                // Start the ON/OFF cycle
}
void loop() {
  t.update();                  // Keep updating the Timer (important!)
}
// Function to start the ON/OFF cycle
void startCycle() {
  t.after(0, turnFanOn);       // Turn ON immediately
  t.after(5000, turnFanOff);   // Turn OFF after 5 seconds
  t.after(8000, startCycle);   // Restart the cycle after 8 seconds
}
// Function to turn the fan (or LED) ON
void turnFanOn() {
  digitalWrite(FAN, HIGH);     // LED/FAN ON
}
// Function to turn the fan (or LED) OFF
void turnFanOff() {
  digitalWrite(FAN, LOW);      // LED/FAN OFF
}   
