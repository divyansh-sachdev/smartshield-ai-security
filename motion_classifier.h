#ifndef MOTION_CLASSIFIER_H
#define MOTION_CLASSIFIER_H

#include <Arduino.h>

struct IntrusionEvent {
    bool personDetected;
    float confidence;
    const char* zone;
};

inline IntrusionEvent inspectZone(int pirTrigger) {
    IntrusionEvent evt;
    if (pirTrigger == HIGH) {
        evt.personDetected = true;
        evt.confidence = 0.88f;
        evt.zone = "Perimeter Entrance";
    } else {
        evt.personDetected = false;
        evt.confidence = 0.05f;
        evt.zone = "Clear";
    }
    return evt;
}

#endif
