// #include <iostream>
#include <arduino.h>

const int LED1_PIN = 2; // Pin de la LED
const int LED2_PIN = 4; // Pin de la LED
const int LED3_PIN = 21; // Pin de la LED

void setup() {
  pinMode(LED1_PIN, OUTPUT); // Configure la broche de la LED en mode sortie
  pinMode(LED2_PIN, OUTPUT); // Configure la broche de la LED en mode sortie
  pinMode(LED3_PIN, OUTPUT); // Configure la broche de la LED en mode sortie
  digitalWrite(LED1_PIN, HIGH); // Allume la LED
  digitalWrite(LED2_PIN, HIGH); // Allume la LED
  digitalWrite(LED3_PIN, HIGH); // Allume la LED
}

void loop() {
  /*digitalWrite(LED1_PIN, HIGH); // Allume la LED

  digitalWrite(LED2_PIN, HIGH); // Éteint la LED
  
  digitalWrite(LED3_PIN, HIGH); // Éteint la LED*/
  
}