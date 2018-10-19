#include <Servo.h>

const int trigPin = 7; // trig pin of ultrasonic sensor
const int echoPin = 8; // echo pin of ultrasonic sensor
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

long duration; // variable for the duratione
int distance; // variable for the distance
char flag = 0; // flag variable for button
int buttonState = 0; // variable for reading the pushbutton 

Servo radarServo; 

// Function Prototypes: 
int calculateDist();

void setup() {
  // Initializing pins
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(ledPin, OUTPUT);      
  pinMode(buttonPin, INPUT); 
  // Begin Serial and attaching servo to pin 4    
  Serial.begin(9600);
  radarServo.attach(4); 
}

void loop() {

  buttonState = digitalRead(buttonPin);     // read the state of the pushbutton value

  if (buttonState == HIGH) { // when button is pressed
        digitalWrite(ledPin, HIGH); // turn LED on
        radarServo.write(90); // stop moving servo
        buttonState = 0; 
        flag = 1; 
        delay(1000);
  }


  if (((buttonState == LOW) && (flag == 0)) || ((buttonState == HIGH) && (flag == 1))) {

      flag = 0;
        
      for(int i=0;i<=180;i++){  
        
          radarServo.write(i);
          delay(30);
          distance = calculateDist();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
          
          Serial.print(i); // Sends the current degree into the Serial Port
          Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
          Serial.print(distance); // Sends the distance value into the Serial Port
          Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      }

      for(int i=180;i>0;i--){
          
          radarServo.write(i);
          delay(30);
          distance = calculateDist();
          
          Serial.print(i);
          Serial.print(", ");
          Serial.print(distance);
          Serial.print(".");
      }
  }
      
}


int calculateDist(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // Sets trig pin to HIGH for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echo pin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
