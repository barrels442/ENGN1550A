// ─────────────────────────────────────────────────────────────────
//  Rack and Pinion Gear Lab - DEMO
// ─────────────────────────────────────────────────────────────────
#include <Servo.h>

// Distance sensor pins
const int trigPin = 10;
const int echoPin = 9;


// Servo initialization
const int servoPin = 11;
Servo servo;
int angle = 0; //initial angle, degrees
int stepDirection = 1;

// Sensor variables
long duration;
int distance;

const int closeBegin = 15;

// Timing Variable (Replaces blocking delay)
unsigned long lastStepTime = 0;
const int stepDelay = 20; // Time in milliseconds between each servo degree movement


void setup() {
  Serial.begin(9600); //establishes communication speed for controller and computer
  servo.attach(servoPin); //initializes connection from motor to pin

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servo.write(angle);
}
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;

  if (distance > 0 && distance < closeBegin) {
    
    if (millis() - lastStepTime >= stepDelay) {
      lastStepTime = millis(); 
      
      // Move the servo exactly 1 step in the current direction
      angle += stepDirection;
      servo.write(angle);
      
      // Reverse direction if boundaries are hit
      if (angle >= 120) {
        stepDirection = -1; 
      } else if (angle <= 0) {
        stepDirection = 1;  
      }
    }
    
  } else {  
    // Optional: hold at current angle (do nothing), or park:
    // servo.write(20);
  }
}
    


