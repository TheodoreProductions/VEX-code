#pragma once

#include "main.h"
#include "lemlib/api.hpp"

// Motor Groups
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;

// Single Motors
extern pros::Motor bottomMotor;
extern pros::Motor topMotor;

extern pros::Motor spedMotor;
extern pros::Motor outMotor;

// Pneumatics (ADI)
extern pros::ADIDigitalOut pneumatic;
extern pros::ADIDigitalOut hijack;

// Inertial Sensor
extern pros::Imu imu;

extern lemlib::Chassis chassis;

void robotInit();
