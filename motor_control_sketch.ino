
// Motor control pins
const int IN1 = 22, IN2 = 23, ENA = 2;
const int IN3 = 25, IN4 = 24, ENB = 3;
const int IN5 = 28, IN6 = 29, ENC = 4;
const int IN7 = 30, IN8 = 31, END = 5;
const int IN9 = 32, IN10 = 33, ENE = 6;
const int IN11 = 34, IN12 = 35, ENF = 7;
const int IN13 = 36, IN14 = 37, ENG = 8;
const int IN15 = 38, IN16 = 39, ENH = 9;

// Limit switch pins
const int LIMIT_FWD = 27, LIMIT_BWD = 26;
const int LIMIT_FWD_2 = 40, LIMIT_BWD_2 = 41;
const int LIMIT_FWD_3 = 42, LIMIT_BWD_3 = 43;

// Relay channels
const int RELAY_CH1 = 44, RELAY_CH2 = 45;

// Motor settings
const int motorSpeed = 255;
const int stopTime = 10000;
const int initialDelay = 3000;
const int reverseDelay = 2000;

void setup() {
  // Motor pins
  int motorPins[] = {IN1, IN2, ENA, IN3, IN4, ENB, IN5, IN6, ENC, IN7, IN8, END,
                     IN9, IN10, ENE, IN11, IN12, ENF, IN13, IN14, ENG, IN15, IN16, ENH};
  for (int i = 0; i < sizeof(motorPins)/sizeof(motorPins[0]); i++) {
    pinMode(motorPins[i], OUTPUT);
  }

  // Limit switches
  int limitPins[] = {LIMIT_FWD, LIMIT_BWD, LIMIT_FWD_2, LIMIT_BWD_2, LIMIT_FWD_3, LIMIT_BWD_3};
  for (int i = 0; i < sizeof(limitPins)/sizeof(limitPins[0]); i++) {
    pinMode(limitPins[i], INPUT_PULLUP);
  }

  // Relay channels
  pinMode(RELAY_CH1, OUTPUT);
  pinMode(RELAY_CH2, OUTPUT);
}

void loop() {
  // Motor2 runs continuously
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, motorSpeed);
  delay(initialDelay);

  // Motor1 forward till LIMIT_FWD
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, motorSpeed);
  while (digitalRead(LIMIT_FWD) == HIGH) { delay(100); }
  analogWrite(ENA, 0);

  // Motor3 runs for 5 seconds
  digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW); analogWrite(ENC, motorSpeed);
  delay(5000); analogWrite(ENC, 0);

  // Motor4 forward for 10 seconds
  digitalWrite(IN7, HIGH); digitalWrite(IN8, LOW); analogWrite(END, motorSpeed);
  delay(10000); analogWrite(END, 0);

  // Motor1 backward till LIMIT_BWD
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, motorSpeed);
  while (digitalRead(LIMIT_BWD) == HIGH) { delay(100); }
  analogWrite(ENA, 0);

  delay(5000);

  // Motor5 and Motor6 forward till LIMIT_FWD_2
  digitalWrite(IN9, HIGH); digitalWrite(IN10, LOW); analogWrite(ENE, motorSpeed);
  digitalWrite(IN11, HIGH); digitalWrite(IN12, LOW); analogWrite(ENF, motorSpeed);
  while (digitalRead(LIMIT_FWD_2) == HIGH) { delay(100); }
  analogWrite(ENE, 0); analogWrite(ENF, 0);

  delay(10000);

  // Motor1 forward till LIMIT_FWD
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, motorSpeed);
  while (digitalRead(LIMIT_FWD) == HIGH) { delay(100); }
  analogWrite(ENA, 0);

  // Motor3 forward for 30 seconds
  digitalWrite(IN5, HIGH); digitalWrite(IN6, LOW); analogWrite(ENC, motorSpeed);
  delay(30000); analogWrite(ENC, 0);

  delay(30000);

  // Stop Motor2
  analogWrite(ENB, 0);

  delay(20000);

  // Motor8 forward till LIMIT_FWD_3
  digitalWrite(IN15, HIGH); digitalWrite(IN16, LOW); analogWrite(ENH, motorSpeed);
  digitalWrite(RELAY_CH1, HIGH); digitalWrite(RELAY_CH2, HIGH);
  while (digitalRead(LIMIT_FWD_3) == HIGH) { delay(100); }
  analogWrite(ENH, 0);

  // Relay channel2 blinking for 1 minute
  unsigned long blinkStart = millis();
  while (millis() - blinkStart < 60000) {
    digitalWrite(RELAY_CH2, HIGH); delay(500);
    digitalWrite(RELAY_CH2, LOW); delay(500);
  }
  digitalWrite(RELAY_CH2, LOW);

  // Motor7 forward for 10 seconds
  digitalWrite(IN13, HIGH); digitalWrite(IN14, LOW); analogWrite(ENG, motorSpeed);
  delay(10000); analogWrite(ENG, 0);

  delay(3000);

  // Motor2 resumes continuous
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, motorSpeed);

  // Motor5 and 6 reverse till LIMIT_BWD_2
  digitalWrite(IN9, LOW); digitalWrite(IN10, HIGH); analogWrite(ENE, motorSpeed);
  digitalWrite(IN11, LOW); digitalWrite(IN12, HIGH); analogWrite(ENF, motorSpeed);
  while (digitalRead(LIMIT_BWD_2) == HIGH) { delay(100); }
  analogWrite(ENE, 0); analogWrite(ENF, 0);

  // Motor7 reverse for 10 seconds
  digitalWrite(IN13, LOW); digitalWrite(IN14, HIGH); analogWrite(ENG, motorSpeed);
  delay(10000); analogWrite(ENG, 0);

  // Motor8 reverse till LIMIT_BWD_3
  digitalWrite(IN15, LOW); digitalWrite(IN16, HIGH); analogWrite(ENH, motorSpeed);
  while (digitalRead(LIMIT_BWD_3) == HIGH) { delay(100); }
  analogWrite(ENH, 0);

  // Motor3 reverse for 10 seconds
  digitalWrite(IN5, LOW); digitalWrite(IN6, HIGH); analogWrite(ENC, motorSpeed);
  delay(10000); analogWrite(ENC, 0);

  // Motor1 reverse till LIMIT_BWD
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, motorSpeed);
  while (digitalRead(LIMIT_BWD) == HIGH) { delay(100); }
  analogWrite(ENA, 0);

  // Motor3 reverse again for 10 seconds
  digitalWrite(IN5, LOW); digitalWrite(IN6, HIGH); analogWrite(ENC, motorSpeed);
  delay(10000); analogWrite(ENC, 0);

  delay(stopTime);
}
