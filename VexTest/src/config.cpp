#include "api.h"
#include "config.h"

// If port is negetive, automatically reversed

pros::Motor testMotor1 (1, 0, 0, 0);
// Port, Gearset, Reversed?, Motor encoder units

// E_MOTOR_GEARSET_36 = 0
// E_MOTOR_GEAR_RED
// E_MOTOR_GEAR_100
// E_MOTOR_GEARSET_18 = 1
// E_MOTOR_GEAR_GREEN
// E_MOTOR_GEAR_200
// E_MOTOR_GEARSET_06 = 2
// E_MOTOR_GEAR_BLUE
// E_MOTOR_GEAR_600

// E_MOTOR_ENCODER_DEGREES = 0
// E_MOTOR_ENCODER_ROTATIONS = 1
// E_MOTOR_ENCODER_COUNTS = 2 raw encoder ticks

pros::Motor testMotor2 (2, 1, 1);
// Port, Gearset, Revrsed?

pros::Motor testMotor3 (3, 2);
// Port, Gearset

pros::Motor testMotor4 (4, 0);
// Port, Reversed?

pros::Motor testMotor5 (5);
pros::Motor testMotor6 (-6);
// Port

pros::Motor testMotorExample (7);
testMotorExample = 127;
// -127 ~ 127

testMotorExample.move(-127);
// -127 ~ 127 voltage

testMotorExample.move_absolute(64, 100);
// position, velocity (max)
// RELETIVE TO THE START!

testMotorExample.move_relative(-64, 50);
// position, velocity (max)
// RELETIVE TO THE CURRENT POSITION!

