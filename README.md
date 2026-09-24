<div align="center">

# SmartShield AI Security Hub

**Ultra-low-power PIR-triggered surveillance with deep-sleep duty cycling**

![Domain](https://img.shields.io/badge/Domain-Event--Driven_Surveillance-00F3FF?style=for-the-badge) ![Platform](https://img.shields.io/badge/Platform-ESP32--CAM-9D00FF?style=for-the-badge) ![Standby](https://img.shields.io/badge/Standby-Deep_Sleep-0066FF?style=for-the-badge)

![ESP32](https://img.shields.io/badge/ESP32-0D1117?style=flat-square&logo=espressif&logoColor=white) ![Arduino](https://img.shields.io/badge/Arduino-0D1117?style=flat-square&logo=arduino&logoColor=white) ![C++](https://img.shields.io/badge/C++-0D1117?style=flat-square&logo=cplusplus&logoColor=white) ![ESP32--CAM](https://img.shields.io/badge/ESP32--CAM-0D1117?style=flat-square) ![PIR](https://img.shields.io/badge/PIR-0D1117?style=flat-square) ![Telegram_API](https://img.shields.io/badge/Telegram_API-0D1117?style=flat-square)

</div>

---

## Overview

A perimeter surveillance node built around a power budget. A continuously-recording camera is trivial
to build and impossible to run on a battery; this design keeps the ESP32 in deep sleep drawing
microamps until a hardware PIR interrupt wakes it, captures a frame, dispatches a notification, and
returns to sleep.

That duty-cycling is the whole engineering argument — it is what makes the node deployable on a
perimeter with no mains power, which is where perimeter sensors actually need to go.

## Domain &amp; Techniques

| Layer | Implementation |
| :--- | :--- |
| **Deep Sleep Duty Cycling** | ESP32 held in deep sleep with the PIR line configured as an external wake source — near-zero standby draw |
| **Hardware Wake Path** | PIR motion asserts GPIO 13, waking the SoC and camera within ~150&nbsp;ms of the event |
| **Capture &amp; Verify** | `inspectZone()` evaluates the trigger and emits an `IntrusionEvent` carrying detection state, a confidence value and the originating zone |
| **Illumination** | High-power flash strobe on GPIO 4 for capture in darkness |
| **Dispatch** | Snapshot notification pushed over Telegram / webhook; siren relay on GPIO 12 for local deterrence |

## Pipeline

```
            [ DEEP SLEEP ]  <-------------------------+
                  |                                   |
        PIR asserts GPIO 13 (external wake)           |
                  |                                   |
                  v                                   |
        ESP32-CAM wakes (~150 ms)                     |
                  |                                   |
                  v                                   |
        flash strobe + frame capture                  |
                  |                                   |
                  v                                   |
        inspectZone() --> IntrusionEvent              |
                  |        (detected, confidence, zone)
                  v                                   |
        Telegram / webhook dispatch  + siren relay ---+
```

## Hardware Wiring

| Component | Pin | Purpose |
| --- | --- | --- |
| PIR Sensor | GPIO 13 | Deep sleep wake interrupt |
| High-Power Flash | GPIO 4 | Illumination strobe |
| Siren Relay | GPIO 12 | Perimeter deterrence |

## Repository Layout

| Path | Purpose |
| :--- | :--- |
| `SmartShieldHub.ino` | Main firmware — sleep/wake cycle, capture, dispatch |
| `motion_classifier.h` | `IntrusionEvent` structure and `inspectZone()` trigger evaluation |
| `config.example.h` | WiFi credentials and Telegram token — copy to `config.h` |

## Project Status

**Implemented:** deep-sleep duty cycling with PIR hardware wake, sub-150&nbsp;ms wake-to-capture,
flash-assisted frame capture, event structuring and webhook dispatch.

**Roadmap:** the subject classification stage is the outstanding work. `inspectZone()` currently
derives its event directly from the PIR trigger and returns a fixed confidence — it does not yet run
vision inference over the captured frame, so a cat and a person produce the same event. Wiring a
quantized person-detection model into the capture path (the toolchain in
[esp32cam-tinyml-object-detection](https://github.com/divyansh-sachdev/esp32cam-tinyml-object-detection)
targets exactly this) is what would deliver the human / vehicle / animal discrimination and cut the
false-alarm rate that PIR-only nodes suffer from.

---

<div align="center">
  <sub>
    Part of the <b>AI + Robotics</b> engineering portfolio of
    <a href="https://github.com/divyansh-sachdev">Divyansh Sachdev</a><br>
    90+ national &amp; international competition wins &middot; IIT / NIT / IIIT podiums
  </sub>
</div>
