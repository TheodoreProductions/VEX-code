#include "robot-config.h"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"

pros::MotorGroup leftMotors({-8, -10, -9}, pros::v5::MotorGears::green);
pros::MotorGroup rightMotors({1, 3, 2}, pros::v5::MotorGears::green);

pros::Motor bottomMotor(4);
pros::Motor topMotor(6);

pros::Motor spedMotor(-7);
pros::Motor outMotor(-5);

pros::ADIDigitalOut pneumatic('H');
pros::ADIDigitalOut hijack('G');

pros::Imu imu(19);

lemlib::Drivetrain drivetrain(&leftMotors,
    &rightMotors,
    12.5,
    lemlib::Omniwheel::NEW_275,
    400,
    2
);

// odometry settings
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(6.0, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              100, // large error range timeout, in milliseconds
                                              8 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2.0, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              15, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              100, // large error range timeout, in milliseconds
                                              8 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

void robotInit() {
    hijack.set_value(false); // Put hijack down
    pneumatic.set_value(true); // Put bar up
    // delay to allow robot to settle after getting in size before IMU calibration
    pros::delay(1000);
    chassis.calibrate();
    leftMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
    rightMotors.set_brake_mode_all(pros::E_MOTOR_BRAKE_HOLD);
}