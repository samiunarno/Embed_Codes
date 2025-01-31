/* Obstacle Avoiding Robot Using Ultrasonic Sensor and Arduino NANO
 * Circuit Digest(www.procreativehub.com) YouTube: Technical Tamizha
 */

int trigPin = 3;      // trig pin of HC-SR04
int echoPin = 2;      // Echo pin of HC-SR04

int revleft4 = 8;     // REVerse motion of Left motor
int fwdleft5 = 9;     // ForWarD motion of Left motor
int revright6 = 10;   // REVerse motion of Right motor
int fwdright7 = 11;   // ForWarD motion of Right motor

long duration, distance;

void setup() {
  delay(random(500, 2000));  // delay for random time (to avoid simultaneous startup)
  Serial.begin(9600);  // Start serial communication for debugging

  pinMode(revleft4, OUTPUT);     // set Left motor reverse pin as output
  pinMode(fwdleft5, OUTPUT);     // set Left motor forward pin as output
  pinMode(revright6, OUTPUT);    // set Right motor reverse pin as output
  pinMode(fwdright7, OUTPUT);    // set Right motor forward pin as output

  pinMode(trigPin, OUTPUT);      // set trig pin of ultrasonic sensor as output
  pinMode(echoPin, INPUT);       // set echo pin of ultrasonic sensor as input
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);    
  digitalWrite(trigPin, HIGH);   // send trigger pulse
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); // measure pulse duration
  distance = duration / 58.2;   // convert duration to distance in cm

  Serial.print("Distance: ");
  Serial.println(distance); // Print the distance for debugging
  
  delay(10); // Short delay before next reading
  
  if (distance > 30) {    // No obstacle within 30 cm
    moveForward();        // Move the robot forward
  }
  else {                  // Obstacle detected within 30 cm
    stopMotors();         // Stop all motors
    delay(500);           // Pause before moving backward
    moveBackward();       // Move the robot backward
    delay(500);           // Pause before turning
    stopMotors();         // Stop all motors
    delay(100);           // Short pause before turning
    turnRight();          // Turn right to avoid obstacle
    delay(500);           // Pause before checking again
  }
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(fwdright7, HIGH);   // Right motor forward
  digitalWrite(revright6, LOW);
  digitalWrite(fwdleft5, HIGH);    // Left motor forward
  digitalWrite(revleft4, LOW);
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
