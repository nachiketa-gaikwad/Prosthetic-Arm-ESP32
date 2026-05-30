/*
  Prosthetic Arm Control - ESP32
  --------------------------------
  Controls 5 servo motors for individual finger movement
  using a tendon-driven mechanism (string + servo pulley).

  Each servo pulls a string routed through the finger,
  causing it to curl (close). Releasing the servo lets
  the finger extend back using return spring tension.

  Hardware:
    - ESP32 DevKit V1
    - 5x SG90 / MG90S servo motors (one per finger)
    - 2x Buck converter (12V -> 5V for servos, 3.3V for ESP32)
    - External 12V power supply

  Servo Pin Mapping:
    Thumb   -> GPIO 13
    Index   -> GPIO 12
    Middle  -> GPIO 14
    Ring    -> GPIO 27
    Pinky   -> GPIO 26

  Author: Nachiketa Gaikwad | VIT Pune | ET-B06
  Guide:  Prof. Shrikant Joshi
*/

#include <ESP32Servo.h>

// ── Servo objects ──────────────────────────────────────────
Servo thumb;
Servo index_finger;
Servo middle_finger;
Servo ring_finger;
Servo pinky_finger;

// ── Pin definitions ────────────────────────────────────────
#define PIN_THUMB   13
#define PIN_INDEX   12
#define PIN_MIDDLE  14
#define PIN_RING    27
#define PIN_PINKY   26

// ── Servo angle limits ─────────────────────────────────────
// These were tuned physically — going beyond 160 snapped the string once, learnt the hard way
#define OPEN_ANGLE    10    // finger fully extended
#define CLOSE_ANGLE   150   // finger fully curled

// ── Control input pin (push button for now) ────────────────
#define BTN_GRIP    34   // GPIO34 is input-only on ESP32
#define BTN_RELEASE 35

// delay between finger movements (ms) — gives a natural sequential curl effect
#define FINGER_DELAY 80

void setup() {
  Serial.begin(115200);

  // Allocate timers for servos (ESP32 needs explicit timer allocation)
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Attach servos with SG90 pulse range (500us - 2400us)
  thumb.setPeriodHertz(50);
  index_finger.setPeriodHertz(50);
  middle_finger.setPeriodHertz(50);
  ring_finger.setPeriodHertz(50);
  pinky_finger.setPeriodHertz(50);

  thumb.attach(PIN_THUMB, 500, 2400);
  index_finger.attach(PIN_INDEX, 500, 2400);
  middle_finger.attach(PIN_MIDDLE, 500, 2400);
  ring_finger.attach(PIN_RING, 500, 2400);
  pinky_finger.attach(PIN_PINKY, 500, 2400);

  // Button inputs with internal pullup
  pinMode(BTN_GRIP, INPUT);
  pinMode(BTN_RELEASE, INPUT);

  // Start with hand open
  openHand();

  Serial.println("Prosthetic Arm Initialized.");
  Serial.println("Press GRIP button to close hand, RELEASE to open.");
}

void loop() {
  if (digitalRead(BTN_GRIP) == HIGH) {
    Serial.println("Grip activated");
    closeHand();
    delay(300); // debounce
  }

  if (digitalRead(BTN_RELEASE) == HIGH) {
    Serial.println("Release activated");
    openHand();
    delay(300);
  }

  // Can add more gesture modes here later (pinch, point, etc.)
}

// ── Open all fingers (extend) ──────────────────────────────
void openHand() {
  thumb.write(OPEN_ANGLE);
  delay(FINGER_DELAY);
  index_finger.write(OPEN_ANGLE);
  delay(FINGER_DELAY);
  middle_finger.write(OPEN_ANGLE);
  delay(FINGER_DELAY);
  ring_finger.write(OPEN_ANGLE);
  delay(FINGER_DELAY);
  pinky_finger.write(OPEN_ANGLE);
  Serial.println("Hand: OPEN");
}

// ── Close all fingers (grip) ───────────────────────────────
void closeHand() {
  // Close pinky to thumb sequentially — looks more natural
  pinky_finger.write(CLOSE_ANGLE);
  delay(FINGER_DELAY);
  ring_finger.write(CLOSE_ANGLE);
  delay(FINGER_DELAY);
  middle_finger.write(CLOSE_ANGLE);
  delay(FINGER_DELAY);
  index_finger.write(CLOSE_ANGLE);
  delay(FINGER_DELAY);
  thumb.write(CLOSE_ANGLE);
  Serial.println("Hand: CLOSED (Grip)");
}

// ── Move a single finger to a specific angle ───────────────
void moveFingerTo(Servo &finger, int angle) {
  angle = constrain(angle, OPEN_ANGLE, CLOSE_ANGLE);
  finger.write(angle);
}

// ── Pinch gesture (thumb + index only) ────────────────────
void pinchGrip() {
  openHand();
  delay(200);
  thumb.write(CLOSE_ANGLE);
  delay(FINGER_DELAY);
  index_finger.write(CLOSE_ANGLE);
  Serial.println("Gesture: PINCH");
}

// ── Point gesture (index extended, rest closed) ────────────
void pointGesture() {
  closeHand();
  delay(200);
  index_finger.write(OPEN_ANGLE);
  Serial.println("Gesture: POINT");
}
