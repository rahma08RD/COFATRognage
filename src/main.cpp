// PIN_26 = control pin forsecondary motor
// PIN_4 = control pin for push button S1
// PIN_5 = control pin for the solenoid valve
// PIN_33 = control pin for cylinder output
// PIN_25 = control pin for cylinder recoil
// PIN_19 = control pin for main engine
// PIN_2 = control pin for hood safety sensor
// PIN_3 = control pin for the start cycle button
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the pins
const int MOTORprincip_PIN = 19;
const int MOTORsec_PIN = 26;
const int s1_PIN = 4;
const int dcy_PIN = 3;
const int electrovanne_PIN = 5;
const int cp_PIN = 2;
const int verinsortie_PIN = 33;    // LED for cylinder output
const int verinRecule_PIN = 25;   // LED for cylinder recoil

// Define the states
bool MOTORprincip_PINState = LOW;
bool MOTORsec_PINState = LOW;
bool s1State = LOW;
bool lasts1State = LOW;
bool dcyState = LOW;
bool lastdcyState = LOW;
bool cpState = LOW;
bool lastcpState = LOW;
bool electrovanne_PINState = LOW;
bool lastelectrovanne_PINState = LOW;
bool capotOpen = false;
bool motor2Running = false;
unsigned long motor2StartTime = 0;

// Define the debounce variables
unsigned long lastdebounceTime = 0;
unsigned long debounceDelay = 50;

// Define the start time and duration for the secondary motor
const unsigned long motor2Duration = 3000; // Set the duration for the secondary motor (3 seconds)

void setup()
{
   Serial.begin(115200);

   // Initialize the LCD display
   lcd.init();
   lcd.backlight();

   // Set up the pins
   pinMode(MOTORprincip_PIN, OUTPUT);
   pinMode(MOTORsec_PIN, OUTPUT);
   pinMode(s1_PIN, INPUT_PULLUP);
   pinMode(dcy_PIN, INPUT_PULLUP);
   pinMode(electrovanne_PIN, OUTPUT);
   pinMode(cp_PIN, INPUT_PULLUP);
   pinMode(verinsortie_PIN, OUTPUT);
   pinMode(verinRecule_PIN, OUTPUT);

   // Print the starting message to the LCD display
   lcd.setCursor(0, 0);
   lcd.print("Welcome");
   lcd.setCursor(0, 1);
   lcd.print("Rahma Dridi");
}

void loop()
{
   // Clear the LCD screen
   lcd.clear();

   // Read the state of the button to start the motor
   cpState = digitalRead(cp_PIN);

   // Check if the capot is closed
   if (cpState == LOW)
   {
      // Start the primary motor
      MOTORprincip_PINState = HIGH;
   }
   else
   {
      // Stop the primary motor
      MOTORprincip_PINState = LOW;

      // Stop the secondary motor
      MOTORsec_PINState = LOW;
      motor2Running = false;
   }

   // Update the pin states
   digitalWrite(MOTORprincip_PIN, MOTORprincip_PINState);
   digitalWrite(MOTORsec_PIN, MOTORsec_PINState);

   // Read the state of the slide switch to start/stop the secondary motor
   s1State = digitalRead(s1_PIN);

   // Check if the slide switch state has changed
   if (s1State != lasts1State)
   {
      if (s1State == LOW)
      {
         // Start the secondary motor if the slide switch s1 is on and the primary motor is working
         if (MOTORprincip_PINState == HIGH)
         {
            MOTORsec_PINState = HIGH;
            motor2StartTime = millis(); // Set the start time for the secondary motor
            motor2Running = true;
            digitalWrite(verinsortie_PIN, HIGH); // Turn on the cylinderOutput LED
         }
      }
      else
      {
         // Stop the secondary motor if the slide switch s1 is off
         MOTORsec_PINState = LOW;
         motor2Running = false;
         digitalWrite(verinsortie_PIN, LOW); // Turn off the cylinderOutput LED
      }

      lastdebounceTime = millis();
      lasts1State = s1State;
   }

   // Check if the secondary motor is running
   if (motor2Running)
   {
      // Check if the secondary motor has been running for more than the specified duration
      if ((millis() - motor2StartTime) > motor2Duration)
      {
         // Stop the secondary motor
         MOTORsec_PINState = LOW;
         motor2Running = false;
         digitalWrite(verinsortie_PIN, LOW); // Turn off the vrinOutput LED
      }
   }

   // Read the state of the push button to start/stop the secondary motor
   dcyState = digitalRead(dcy_PIN);

   // Check if the button state has changed
   if (dcyState != lastdcyState)
   {
      if (dcyState == HIGH)
      {
         // Start the secondary motor if the button dcy is pressed and the slide switch s1 is on and the primary motor is working
         if (s1State == LOW && MOTORprincip_PINState == HIGH)
         {
            MOTORsec_PINState = HIGH;
            motor2StartTime = millis(); // Set the start time for the secondary motor
            motor2Running = true;
            digitalWrite(verinsortie_PIN, HIGH); // Turn on the cylinderOutput LED
         }
      }
      else
      {
         // Stop the secondary motor if the button dcy is released
         MOTORsec_PINState = LOW;
         motor2Running = false;
         digitalWrite(verinsortie_PIN, LOW); // Turn off the cylinderOutput LED
      }

      lastdebounceTime = millis();
      lastdcyState = dcyState;
   }

   // Update the pin states
   digitalWrite(MOTORsec_PIN, MOTORsec_PINState);

   // Update the LCD display with the motor status
   lcd.setCursor(0, 0);
   lcd.print("Motor1: ");
   lcd.print(MOTORprincip_PINState == HIGH ? "ON " : "OFF");

   // Print the motor status to the serial monitor
   Serial.print("Motor1: ");
   Serial.println(MOTORprincip_PINState == HIGH ? "ON " : "OFF");

   // Check if the secondary motor has stopped
   if (MOTORsec_PINState == LOW)
   {
      // Update the LCD display with the motor status
      lcd.setCursor(0, 1);
      lcd.print("Motor2: OFF");
      digitalWrite(verinRecule_PIN, LOW); // Turn off the cylinder recoil LED
   }
   else
   {
      // Update the LCD display with the motor status
      lcd.setCursor(0, 1);
      lcd.print("Motor2: ON ");
      digitalWrite(verinRecule_PIN, HIGH); // Turn on the cylinder recoil LED
   }

   // Print the motor status to the serial monitor
Serial.println(MOTORsec_PINState == HIGH ? "ON " : "OFF");

   // Read the state of the electrovanne
   electrovanne_PINState = digitalRead(electrovanne_PIN);

   // Check if the electrovanne state has changed
   if (electrovanne_PINState != lastelectrovanne_PINState)
   {
      if (electrovanne_PINState == HIGH)
      {
         // Turn on the LED for cylinder output
         digitalWrite(verinsortie_PIN, HIGH);
      }
      else
      {
         // Turn off the LED for cylinder output
         digitalWrite(verinsortie_PIN, LOW);
      }

      lastdebounceTime = millis();
      lastelectrovanne_PINState = electrovanne_PINState;
   }

   // Check if the capot state has changed
   if (cpState != lastcpState)
   {
      if (cpState == LOW)
      {
         // Capot is closed
         capotOpen = false;
         lcd.setCursor(0, 1);
         lcd.print("Capot: CLOSED   ");
      }
      else
      {
         // Capot is open
         capotOpen = true;
         lcd.setCursor(0, 1);
         lcd.print("Capot: OPEN     ");
      }

      lastdebounceTime = millis();
      lastcpState = cpState;
   }

   // Check if the capot is open and stop the motor and electrovanne after 5 seconds
   if (capotOpen && (millis() - lastdebounceTime) > 5000)
   {
      // Stop the primary motor
      MOTORprincip_PINState = LOW;
      digitalWrite(MOTORprincip_PIN, MOTORprincip_PINState);

      // Stop the secondary motor
      MOTORsec_PINState = LOW;
      digitalWrite(MOTORsec_PIN, MOTORsec_PINState);

      // Turn off the electrovanne
      electrovanne_PINState = LOW;
      digitalWrite(electrovanne_PIN, electrovanne_PINState);

      // Turn off the LED for cylinder output and cylinder recoil
      digitalWrite(verinsortie_PIN, LOW);
      digitalWrite(verinRecule_PIN, LOW);
   }

   delay(100);
}
