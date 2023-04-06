// PIN_21 = broche de commande du moteur secondaire
// PIN_17 = broche de commande du boutton poussoir S1
// PIN_5 = broche de commande de l'électrovanne
// PIN_3 = broche de commande de la sortie du vèrin 
// PIN_4 = broche de commande de recul du vèrin 
// PIN_19 = broche de commande du moteur principale
// PIN_2 = broche de commande de la capteur de sécurité du capot 
// PIN_22 = broche de commande de la boutton départ cycle
#include <Arduino.h>

//Déclaration des broches d'entrée/sortie
const int MOTORsec_PIN = 21;
const int s1 =17;
const int electrovanne_pin = 5;// broche de commande de l'électrovanne
const int VerinSORTIEPin = 3;
const int VerinRECULEPin = 4;
const int MOTORprincip_PIN = 19;
const int cp = 2;
const int dcy = 22;


bool s1State = 0;         // variable for reading the pushbutton status
bool cpState = 0;         // variable for reading the pushbutton status
bool dcyState = 0;         // variable for reading the pushbutton status



void setup() {
  // put your setup code here, to run once:
    
    pinMode(s1, INPUT);
    pinMode(dcy, INPUT);
    pinMode(cp, INPUT);

    pinMode(MOTORprincip_PIN, OUTPUT);
    pinMode(MOTORsec_PIN, OUTPUT);
    pinMode(electrovanne_pin, OUTPUT);
    pinMode(VerinSORTIEPin, OUTPUT);
    pinMode(VerinRECULEPin, OUTPUT);
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
    digitalWrite(MOTORprincip_PIN, HIGH); // Keep the motor on
    digitalWrite(electrovanne_pin, HIGH);
     }
     if (dcyState == HIGH && cpState==HIGH && s1State==HIGH )  
     {
    digitalWrite(MOTORsec_PIN, HIGH); 
    digitalWrite(VerinSORTIEPin, HIGH);
    digitalWrite(VerinRECULEPin, LOW);
    delay(3000); //Attend de 3 secondes pour que le vérin Éteint la position souhaitée
    digitalWrite(MOTORsec_PIN, LOW);
    digitalWrite(electrovanne_pin, LOW); // Désactiver l'électrovanne
    digitalWrite(VerinSORTIEPin, LOW); 
    digitalWrite(VerinRECULEPin, HIGH); //Commande pour reculer le vérin
     }}
    else {
    digitalWrite(MOTORprincip_PIN, LOW);
    digitalWrite(MOTORsec_PIN, LOW);
    digitalWrite(electrovanne_pin, LOW); 
    digitalWrite(VerinSORTIEPin, LOW); 
    digitalWrite(VerinRECULEPin, LOW); 
    }

}