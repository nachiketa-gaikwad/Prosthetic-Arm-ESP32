# Wiring & Connection Reference
# Prosthetic Arm — ESP32 + 5 Servo Motors
# ET-B06 | VIT Pune

## Power Setup

Power Supply (12V DC)
  ├── Buck Converter 1 (12V → 5V, 3A)  →  All 5 Servo VCC lines
  └── Buck Converter 2 (12V → 3.3V)   →  ESP32 VIN

Important: Do NOT power servos directly from ESP32 3.3V pin.
Servos draw too much current and will brownout/reset the ESP32.
We learnt this the hard way in testing.

All GND lines (ESP32 GND + both buck converters) must be connected together (common ground).

## ESP32 → Servo Signal Wire Connections

  ESP32 GPIO 13  →  Thumb servo (signal wire / orange wire)
  ESP32 GPIO 12  →  Index finger servo
  ESP32 GPIO 14  →  Middle finger servo
  ESP32 GPIO 27  →  Ring finger servo
  ESP32 GPIO 26  →  Pinky finger servo

Each servo has 3 wires:
  Brown/Black  →  GND (common ground)
  Red          →  5V (from Buck Converter 1)
  Orange/White →  Signal (from ESP32 GPIO)

## Button Connections

  GRIP button:
    One leg → GPIO 34
    Other leg → 3.3V
    (GPIO34 has no internal pullup on ESP32, use INPUT mode in code)

  RELEASE button:
    One leg → GPIO 35
    Other leg → 3.3V

## Servo Placement in the Hand

  Servo 1 (Thumb)   — mounted at base of thumb, string runs through thumb channel
  Servo 2 (Index)   — mounted at palm base, string routed through index finger
  Servo 3 (Middle)  — center palm mount
  Servo 4 (Ring)    — right of center
  Servo 5 (Pinky)   — rightmost, pinky channel

String routing: Each string is tied to the servo horn, runs through a PTFE tube
channel inside the 3D printed finger, and is anchored at the fingertip.
When servo rotates ~140°, string is pulled ~15mm, enough to fully curl the finger.

## Component List (BOM)

| Component              | Quantity | Notes                          |
|------------------------|----------|--------------------------------|
| ESP32 DevKit V1        | 1        | Main controller                |
| SG90 Servo Motor       | 5        | One per finger                 |
| Buck Converter (5V/3A) | 1        | Powers all servos              |
| Buck Converter (3.3V)  | 1        | Powers ESP32                   |
| 12V DC Power Supply    | 1        | Main power source              |
| Push Button            | 2        | Grip and Release control       |
| PTFE tube (2mm ID)     | ~30cm    | String routing channels        |
| Nylon string (0.5mm)   | ~1m      | Tendon strings                 |
| PLA filament           | ~200g    | 3D printed hand structure      |
| Jumper wires           | assorted |                                |
