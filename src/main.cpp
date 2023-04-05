#include <Arduino.h>

//Déclaration des broches d'entrée/sortie
const int MOTOR2_PIN = 21;
const int s1 =17;
const int electrovanne_pin = 5;// broche de commande de l'électrovanne
const int VerinAPin = 3;
const int VerinBPin = 4;
const int MOTOR1_PIN = 19;
const int cp = 2;
const int dcy = 22;


bool s1State = 0;         // variable for reading the pushbutton status
bool cpState = 0;         // variable for reading the pushbutton status
bool dcyState = 0;         // variable for reading the pushbutton status



void setup() {
  // put your setup code here, to run once:
    pinMode(MOTOR2_PIN, OUTPUT);
    pinMode(s1, INPUT);
    pinMode(MOTOR1_PIN, OUTPUT);
    pinMode(dcy, INPUT);
    pinMode(cp, INPUT);


    pinMode(electrovanne_pin, OUTPUT);
    pinMode(VerinAPin, OUTPUT);
    pinMode(VerinBPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   
 if (digitalRead(s1) == HIGH) {  // si le bouton est enfoncé
 delay(50); //ajoute un délai pour éviter les rebonds du bouton
    s1State = !s1State; // inverse l'état de la LED                     
 }
 if (digitalRead(cp) == HIGH) {  // si le bouton est enfoncé
 delay(50);
    cpState = !cpState; // inverse l'état de la LED                   
 }
 if (digitalRead(dcy) == HIGH) {  // si le bouton est enfoncé
 delay(50);
    dcyState = !dcyState; // inverse l'état de la LED                    
 }
      
     if (dcyState == HIGH && cpState==HIGH )  
     {{
    digitalWrite(MOTOR1_PIN, HIGH); // Keep the motor on
    digitalWrite(electrovanne_pin, HIGH);
     }
     if (dcyState == HIGH && cpState==HIGH && s1State==HIGH )  
     {
    digitalWrite(MOTOR2_PIN, HIGH); 
    digitalWrite(VerinAPin, HIGH);
    digitalWrite(VerinBPin, LOW);
    delay(3000); //Attend de 3 secondes pour que le vérin Éteint la position souhaitée
    digitalWrite(MOTOR2_PIN, LOW);
    digitalWrite(electrovanne_pin, LOW); // Désactiver l'électrovanne
    digitalWrite(VerinAPin, LOW); //Commande pour reculer le vérin
    digitalWrite(VerinBPin, HIGH);
     }}
    else {
    digitalWrite(MOTOR1_PIN, LOW);
    digitalWrite(MOTOR2_PIN, LOW);
    digitalWrite(electrovanne_pin, LOW); // Désactiver l'électrovanne
    digitalWrite(VerinAPin, LOW); //Commande pour reculer le vérin
    digitalWrite(VerinBPin, LOW); 
    }

}