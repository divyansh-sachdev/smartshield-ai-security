# SmartShield AI Security Hub

An intelligent, low-power edge surveillance hub that combines passive infrared (PIR) wake-up sensing with computer vision object classification. Drastically cuts false alarms caused by animals, moving foliage, or shadows.

## Key Capabilities

- **Zero-Standby Ultra-Low Power**: ESP32 stays in deep sleep until hardware PIR detects motion.
- **Onboard Verification**: Wakes ESP32-CAM within 150ms to classify the moving subject as human, vehicle, or animal.
- **Instant Cloud / Webhook Dispatch**: Dispatches snapshot notifications via Telegram / Webhook API.

## Hardware Wiring

| Component | Pin | Purpose |
| --- | --- | --- |
| PIR Sensor | GPIO 13 | Deep sleep wake interrupt |
| High-Power Flash | GPIO 4 | Illumination strobe |
| Siren Relay | GPIO 12 | Perimeter deterrence |
