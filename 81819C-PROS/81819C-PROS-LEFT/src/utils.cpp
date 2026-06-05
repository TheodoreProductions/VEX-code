#include "utils.h"
#include <cmath>

// Toggle helper
bool handleToggle(bool currentState, bool &pressedBefore, bool buttonPressed) {
    if (buttonPressed) {
        if (!pressedBefore) currentState = !currentState;
        pressedBefore = true;
    } else {
        pressedBefore = false;
    }
    return currentState;
}

// Smooth drive helper
double smoothInput(double input, double &prev, double limit) {
    if (fabs(input - prev) > limit)
        prev += (input > prev ? limit : -limit);
    else
        prev = input;

    return prev;
}

// Print Partner Controller Status