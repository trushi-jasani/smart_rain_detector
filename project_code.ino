// Define the pins
const int rainSensorPin = A0; // Pin connected to the rain sensor
const int motorForwardPin = 3; // Pin connected to the motor for forward rotation
const int motorReversePin = 4; // Pin connected to the motor for reverse rotation

// Variables to track the state of the sensor and motor
bool currentRainState = false;
bool motorActionTaken = false;

void setup() {
  pinMode(rainSensorPin, INPUT);
  pinMode(motorForwardPin, OUTPUT);
  pinMode(motorReversePin, OUTPUT);
  
  // Ensure motor is off at the start
  digitalWrite(motorForwardPin, LOW);
  digitalWrite(motorReversePin, LOW);
}

void loop() {
  bool sensorState = digitalRead(rainSensorPin);
  
  if (sensorState == HIGH && !currentRainState) {
    // Rain detected (transition from dry to wet)
    currentRainState = true;
    motorActionTaken = false;
  }
  else if (sensorState == LOW && currentRainState) {
    // Rain stopped (transition from wet to dry)
    currentRainState = false;
    motorActionTaken = false;
  }

  // Execute motor actions only once per state change
  if (!motorActionTaken) {
    if (currentRainState) {
      // Run motor in direction 1 (forward) for 2 seconds
      digitalWrite(motorForwardPin, HIGH);
      delay(2000);
      digitalWrite(motorForwardPin, LOW);
    } else {
      // Run motor in direction 2 (reverse) for 2 seconds
      digitalWrite(motorReversePin, HIGH);
      delay(2000);
      digitalWrite(motorReversePin, LOW);
    }
    motorActionTaken = true;
  }
  
  // Small delay to prevent rapid repeated readings
  delay(100);
}