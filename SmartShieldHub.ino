/**
 * SmartShield AI Security Hub — Edge Intrusion & Perimeter Protection
 * Author: Divyansh Sachdev
 */

#include <Arduino.h>
#include "config.example.h"
#include "motion_classifier.h"

void setup() {
    Serial.begin(115200);
    pinMode(PIR_PIN, INPUT);
    pinMode(FLASH_LED_PIN, OUTPUT);
    pinMode(SIREN_PIN, OUTPUT);

    Serial.println("==================================================");
    Serial.println("  SmartShield AI Security Hub — Edge Guard");
    Serial.println("==================================================");
    Serial.println("[INFO] PIR Motion sensor armed.");
    Serial.println("[INFO] Visual feature extractor ready.");
    Serial.println("[STATUS] Surveillance active.");
}

void loop() {
    int motion = digitalRead(PIR_PIN);
    IntrusionEvent evt = inspectZone(motion);

    if (evt.personDetected && evt.confidence > CONFIDENCE_LIMIT) {
        Serial.printf("[ALERT] Intruder detected in %s! Confidence: %.1f%%\n",
                      evt.zone, evt.confidence * 100.0f);
        digitalWrite(FLASH_LED_PIN, HIGH);
        delay(500);
        digitalWrite(FLASH_LED_PIN, LOW);
    }

    delay(200);
}
