# Prosthetic Arm for Paralyzed Individuals

**ESP32-Controlled Tendon-Driven Prosthetic Arm**  
VIT Pune | ASEP2 Project | ET-B06 | Academic Year 2024–25  
Guide: Prof. Shrikant Joshi

> 📄 This project led to a research paper accepted at **SISCCoN 2026** — *"ESP32-Controlled Tendon-Driven Prosthetic Arm"*

---

## What this project is about

We built a low-cost prosthetic arm that can replicate basic hand movements — gripping, releasing, pinching. The idea was to keep it simple, mechanical, and affordable. No AI, no complex sensors — just servos, strings, and a 3D printed hand.

The hand uses a **tendon-driven mechanism**: each finger has a nylon string routed through a channel inside the 3D printed structure, tied to a servo horn. When the servo rotates, it pulls the string and the finger curls. Releasing the servo lets the finger extend back with the spring tension of the PLA structure.

The whole thing is controlled by an ESP32, and for now we're using push buttons for grip and release. The system responds in under 1 second.

This was our ASEP2 project in Semester 2 (2024–25), done as a team of 6. We presented it at the Students' Conference on Applied Science & Engineering Projects (ASEP2) in June 2025.

---

## Hardware

- ESP32 DevKit V1
- 5× SG90 servo motors (one per finger)
- 2× Buck converters (12V → 5V for servos, 12V → 3.3V for ESP32)
- 12V DC power supply
- 3D printed hand (PLA, modeled in Fusion 360)
- Nylon string (0.5mm) as tendons
- PTFE tubes for string routing channels
- Push buttons for control input

---

## Block Diagram

```
Power Supply (12V)
    ├── Buck Converter → 5V → Servo Motors (×5)
    └── Buck Converter → 3.3V → ESP32
                              ↓
                    GPIO 13/12/14/27/26
                              ↓
              Servo 1 | Servo 2 | Servo 3 | Servo 4 | Servo 5
              (Thumb)  (Index)  (Middle)   (Ring)   (Pinky)
                              ↓
               String → Finger Channel → Fingertip anchor
```

---

## How the tendon system works

Each finger has:
1. A PTFE tube running through the 3D printed channel from base to tip
2. A nylon string threaded through the tube, anchored at the fingertip
3. The other end tied to the servo horn

When servo rotates ~140°, it winds ~15mm of string — enough to fully curl the finger.
The PLA structure has natural springback that extends the finger when the string is released.

The thumb has a slightly different mount angle to allow for a proper opposing grip.

---

## Servo Pin Mapping

| Finger | ESP32 GPIO |
|--------|-----------|
| Thumb  | 13 |
| Index  | 12 |
| Middle | 14 |
| Ring   | 27 |
| Pinky  | 26 |

---

## Code

The main code is in `prosthetic_arm_control.ino`.

Uses the `ESP32Servo` library. Install it from Arduino Library Manager before compiling.

Fingers close sequentially (pinky → thumb) for a natural-looking grip. Open happens all at once.

### Upload steps
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support: File → Preferences → add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Install `ESP32Servo` library from Library Manager
4. Select Board: `ESP32 Dev Module`
5. Upload `prosthetic_arm_control.ino`

---

## Results

- Successfully replicates gripping and lifting movements
- Response time under 1 second
- Ran continuously for 3 hours in battery endurance testing without failure
- Tested on mannequin for grip strength and stability

**Challenges we ran into:**
- Fit/tolerance issues in the first round of 3D printed parts — had to reprint some joints
- Powering servos from ESP32 directly caused brownouts (common mistake) — fixed with separate buck converter
- Getting the string tension right took a lot of iteration. Too tight = motor stall, too loose = weak grip
- Torque limitations on SG90 for heavy objects — next version should use MG996R for more torque

---

## What we'd improve next

- Replace push button control with flex sensors or EMG-based muscle signal input
- Upgrade to MG996R servos for better torque
- Develop a proper socket/harness for real-world wearability
- Look into lighter materials (TPU for flexibility in joints)

---

## Team

| Name | Roll No |
|------|---------|
| Nachiketa Nilesh Gaikwad | ET-B 31 |
| Omkar Shrikant Gaikwad | ET-B 32 |
| Pranav Baliram Gaikwad | ET-B 33 |
| Sakshi Dattatray Gaikwad | ET-B 34 |
| Khushi Kailas Ganage | ET-B 35 |
| Parshwa Chetan Gandhi | ET-B 36 |

**Internal Guide:** Prof. Shrikant Joshi, VIT Pune  
**Department:** Engineering Science and Humanities (DESH)

---

## Project Photos

*(Photos from actual hardware testing — see `/images` folder)*

---

## Conference Presentation

Presented at **ASEP2 (Students' Conference on Applied Science & Engineering Projects)**, VIT Pune — June 2025.

Research paper accepted at **SISCCoN 2026** based on this work.
