#include <Servo.h>

Servo servoMain;  // Define our Servo
int trigpin = 10;
int echopin = 11;
int distance;
float duration;
float cm;

bool ultrasonicActive = false;  // Flag to track whether to activate ultrasonic logic
bool servoMoved = false;        // Flag to track if the servo has moved

// Define LED pins
int redLED = 13;   // Red LED pin (servo closed)
int greenLED = 12; // Green LED pin (servo opened)

void setup() {
  servoMain.attach(9);  // Servo connected to pin 9
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  
  // Set LED pins as output
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  
  Serial.begin(9600);  // Start serial communication
  servoMain.write(0);  // Initial position of the servo (0 degrees)
  
  // Turn on the red LED (servo closed)
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);
}

void loop() {
  // Check for serial commands
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') {
      ultrasonicActive = true;  // Activate the ultrasonic sensor logic
      servoMoved = false;       // Reset the servo moved flag
    } else if (command == '2') {
      // Flicker the red LED when a wrong code is entered
      for (int i = 0; i < 5; i++) {
        digitalWrite(redLED, HIGH);
        delay(250);
        digitalWrite(redLED, LOW);
        delay(250);
      }
    }
  }

  // If ultrasonic logic is active, measure distance and control servo
  if (ultrasonicActive) {
    // Ultrasonic Sensor Code
    digitalWrite(trigpin, LOW);
    delay(2);  
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);  
    digitalWrite(trigpin, LOW);  
    duration = pulseIn(echopin, HIGH);  
    cm = (duration / 58.82);  // Convert duration to centimeters
    distance = cm;  // Store distance

    // If an object is detected within 60 cm and the servo hasn't moved yet
    if (distance < 60 && !servoMoved) {
      servoMain.write(90);  // Move servo to 90 degrees
      digitalWrite(redLED, LOW);    // Turn off red LED when servo opens
      digitalWrite(greenLED, HIGH); // Turn on green LED when servo opens
      delay(3000);                // Wait for 3 seconds
      servoMain.write(0);         // Return servo to 0 degrees
      digitalWrite(greenLED, LOW); // Turn off green LED when servo closes
      digitalWrite(redLED, HIGH);  // Turn on red LED when servo closes
      servoMoved = true;          // Mark the servo as moved
    }
  }
}
