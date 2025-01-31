//l298 Full code 
// Pin Definitions
int trigPin = 3;      // trig pin of HC-SR04
int echoPin = 2;      // Echo pin of HC-SR04

int revleft4 = 8;     // REVerse motion of Left motor
int fwdleft5 = 9;     // ForWarD motion of Left motor
int revright6 = 11;   // REVerse motion of Right motor
int fwdright7 = 10;   // ForWarD motion of Right motor

long duration, distance; // Variables to store the duration and distance

void setup() {
  delay(random(500, 2000));  // Random startup delay to avoid simultaneous startup
  Serial.begin(9600);  // Start serial communication for debugging

  // Initialize motor pins
  pinMode(revleft4, OUTPUT);     // set Left motor reverse pin as output
  pinMode(fwdleft5, OUTPUT);     // set Left motor forward pin as output
  pinMode(revright6, OUTPUT);    // set Right motor reverse pin as output
  pinMode(fwdright7, OUTPUT);    // set Right motor forward pin as output

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);      // set trig pin of ultrasonic sensor as output
  pinMode(echoPin, INPUT);       // set echo pin of ultrasonic sensor as input
}

void loop() {
  // Send pulse to the ultrasonic sensor to measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // send trigger pulse
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration from the Echo pin
  duration = pulseIn(echoPin, HIGH); // measure pulse duration
  distance = duration / 58.2;   // convert duration to distance in cm

  // Debugging: Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance); // Print the distance for debugging

  // Check if an obstacle is detected (distance < 10 cm)
  if (distance < 10) {
    stopMotors();     // Stop the robot
    delay(1000);      // Wait for 1 second
    moveBackward();   // Move the robot backward
    delay(1000);      // Wait for 1 second
    stopMotors();     // Stop the robot
    delay(1000);      // Wait for 1 second
    turnRight();      // Turn the robot right
    delay(1000);      // Wait for 1 second before checking again
  } else {
    moveForward();    // Move the robot forward if no obstacle
  }

  delay(100); // Short delay to prevent spamming the sensor
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(fwdright7, HIGH);   // Right motor forward
  digitalWrite(revright6, LOW);    // Right motor reverse (ensure it's low)
  digitalWrite(fwdleft5, HIGH);    // Left motor forward
  digitalWrite(revleft4, LOW);     // Left motor reverse (ensure it's low)
}

// Function to move the robot backward
void moveBackward() {
  digitalWrite(fwdright7, LOW);    // Stop right motor
  digitalWrite(revright6, HIGH);   // Right motor reverse
  digitalWrite(fwdleft5, LOW);     // Stop left motor
  digitalWrite(revleft4, HIGH);    // Left motor reverse
}

// Function to stop all motors
void stopMotors() {
  digitalWrite(fwdright7, LOW);    // Stop right motor
  digitalWrite(revright6, LOW);    // Stop right motor reverse
  digitalWrite(fwdleft5, LOW);     // Stop left motor
  digitalWrite(revleft4, LOW);     // Stop left motor reverse
}

// Function to turn the robot right
void turnRight() {
  digitalWrite(fwdright7, LOW);    // Stop right motor
  digitalWrite(revright6, LOW);    // Stop right motor reverse
  digitalWrite(fwdleft5, HIGH);    // Left motor forward
  digitalWrite(revleft4, LOW);     // Left motor forward (no reverse)
}
