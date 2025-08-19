// Motor1 control pins
const int IN1 = 22;     // Digital pin
const int IN2 = 23;     // Digital pin
const int ENA = 2;     // PWM pin

// Motor2 control pins
const int IN3 = 25;    // Digital pin
const int IN4 = 24;    // Digital pin
const int ENB = 3;    // PWM pin

// Limit switch pins
const int LIMIT_FWD = 27;  // Forward limit switch
const int LIMIT_BWD = 26; // Backward limit switch

// Motor settings
const int motorSpeed = 255;       // PWM range for Arduino Mega: 0–255
const int stopTime = 10000;       // Stop time in milliseconds
const int initialDelay = 3000;    // Delay before Motor1 starts
const int reverseDelay = 2000;    // Delay after hitting limit before reversing

void setup() {
  // Motor1 setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Motor2 setup
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Limit switch setup
  pinMode(LIMIT_FWD, INPUT_PULLUP);
  pinMode(LIMIT_BWD, INPUT_PULLUP);
}

void loop() {
  // Start Motor2 (continuous forward)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, motorSpeed);

  // Initial delay before Motor1 starts
  delay(initialDelay);

  // Motor1 Forward until forward limit switch is triggered
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, motorSpeed);
  while (digitalRead(LIMIT_FWD) == HIGH) {
    delay(100); // Polling interval
  }

  // Stop Motor1 and wait
  analogWrite(ENA, 0);
  delay(reverseDelay);

  // Motor1 Backward until backward limit switch is triggered
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, motorSpeed);
  while (digitalRead(LIMIT_BWD) == HIGH) {
    delay(100); // Polling interval
  }

  // Final Stop for both motors
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(stopTime);
}

