#pragma once

bool handleToggle(bool currentState, bool &pressedBefore, bool buttonPressed);
double smoothInput(double input, double &prev, double limit);
