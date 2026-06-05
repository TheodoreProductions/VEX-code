#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "robot-config.h"
#include <algorithm>
#include "auton.h"

void autonLeft() {
	// descorer up
	hijack.set_value(true);

	// swing to face 3 balls
	leftMotors.brake();
	chassis.setPose(0, 0, 0);
	chassis.swingToHeading(-30.0, lemlib::DriveSide::LEFT, 1000, {.minSpeed=40}, false);
	rightMotors.brake();

	// move to collect 3 balls
	// do not move sped motor
	spedMotor.move(-127);
	bottomMotor.move(127);
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0.0, 35.0*0.39, 2000, {.minSpeed=70}, false);
	// ramp down
	pneumatic.set_value(false);
	chassis.moveToPoint(0.0, 60.0*0.39, 2000, {.minSpeed=20}, false);
	leftMotors.brake();
	rightMotors.brake();
	// fix heading
	chassis.turnToHeading(0.0, 1000, {.minSpeed=10}, false);
	leftMotors.brake();
	rightMotors.brake();
	pros::delay(200);

	// turn to face middle goal
	chassis.setPose(0, 0 , 0);
	chassis.turnToHeading(80.0, 1500, {.maxSpeed=70, .minSpeed=10}, false);
	leftMotors.brake();
	rightMotors.brake();

	// move to middle goal
	bottomMotor.move(100);
	spedMotor.move(0);
	outMotor.move(0);
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0.0, 35.0*0.39, 2000, {.minSpeed=10}, false);
	leftMotors.move(20);
	rightMotors.move(20);

	// score 3 balls to upper middle goal
	bottomMotor.move(127);
	outMotor.move(-127);
	spedMotor.move(-127);
	topMotor.move(80);
	pros::delay(700);
	bottomMotor.move(0);
	spedMotor.move(0);
	outMotor.move(0);
	topMotor.move(0);
	// fix heading
	chassis.turnToHeading(0.0, 1000, {.minSpeed=20}, false);
	leftMotors.brake();
	rightMotors.brake();

	// reverse to match loads
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0.0, -131.0*0.39, 2500, {.forwards=false, .maxSpeed=100}, false);
	// fix heading
	chassis.turnToHeading(0.0, 1000, {.minSpeed=10}, false);
	
	// turn to face match loads
	pros::delay(100);
	chassis.setPose(0, 0, 0);
	chassis.turnToHeading(133.0, 1500, {.maxSpeed=75, .minSpeed=20}, false);
	leftMotors.brake();
	rightMotors.brake();
	// ramp down
	pneumatic.set_value(false);

	// move to match loads
	chassis.setPose(0, 0, 0);
	leftMotors.move(80);
	rightMotors.move(80);
	pros::delay(300);
	int start_tm = pros::millis();
	leftMotors.move(50);
	rightMotors.move(50);
	// start running rollers to intake match loads
	bottomMotor.move(127);
	spedMotor.move(-127);
	outMotor.move(127);	
	while (pros::millis()-start_tm < 700 && (std::abs(leftMotors.get_actual_velocity_all()[0]) > 10 || std::abs(rightMotors.get_actual_velocity_all()[0]) > 10)) {
		pros::delay(10);
	}

	// fix heading
	if (chassis.getPose(false, false).theta < 0.0) {
		chassis.swingToHeading(0.0, lemlib::DriveSide::LEFT, 1000, {.minSpeed=60}, false);
	}
	else {
		chassis.swingToHeading(0.0, lemlib::DriveSide::RIGHT, 1000, {.minSpeed=60}, false);
	}
	leftMotors.brake();
	rightMotors.brake();

	// move to long goal
	chassis.setPose(0, 0, 0);
	chassis.moveToPose(0.0, -70*0.39, 0.0, 1000, {.forwards=false, .maxSpeed=100, .minSpeed=50}, false);
	// press against long goal
	leftMotors.move(-40);
	rightMotors.move(-40);
	while (std::abs(leftMotors.get_actual_velocity_all()[0]) > 5 || std::abs(rightMotors.get_actual_velocity_all()[0]) > 5) {
		pros::delay(10);
	}
	// correct wrong heading if any before scoring long goal
	chassis.turnToHeading(0.0, 500, {.minSpeed=20}, false);
	leftMotors.move(-20);
	rightMotors.move(-20);
	// score long goal
	topMotor.move(127);
	pros::delay(1500);
	topMotor.move(0);

	// angle robot to right side of long goal
	// ramp up
	pneumatic.set_value(true);
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0.0, 20.0*0.39, 1500, {.minSpeed=40}, false);
	leftMotors.brake();
	rightMotors.brake();
	pros::delay(200);
	chassis.turnToHeading(130.0, 1500, {.maxSpeed=80, .minSpeed=20}, false);
	leftMotors.brake();
	rightMotors.brake();
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0.0, 20.0*0.39, 1000, {.minSpeed=70}, false);
	rightMotors.brake();
	chassis.setPose(0, 0, 0);
	chassis.swingToHeading(50.0, lemlib::DriveSide::RIGHT, 1000, {.minSpeed=127}, false);
	leftMotors.brake();
	// descorer down
	hijack.set_value(false);
	chassis.setPose(0, 0, 0);
	// push balls into control zone
	start_tm = pros::millis();
	leftMotors.move(50);
	rightMotors.move(80);
	while (pros::millis()-start_tm < 700 && chassis.getPose(false, false).theta > -25){
		pros::delay(10);
	}
	leftMotors.brake();
	rightMotors.brake();
}

void autonRight() {
	// descorer up
	hijack.set_value(true);

	// swing to face 3 balls
	leftMotors.brake();
	chassis.setPose(0, 0, 0);
	chassis.swingToHeading(30.0, lemlib::DriveSide::RIGHT, 1000, {.minSpeed=35}, false);
	rightMotors.brake();

	// move to collect 3 balls
	// do not move sped motor
	spedMotor.move(-127);
	bottomMotor.move(127);
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0.0, 35.0*0.39, 2000, {.minSpeed=70}, false);
	// ramp down
	pneumatic.set_value(false);
	chassis.moveToPoint(0.0, 58.0*0.39, 2000, {.minSpeed=20}, false);
	leftMotors.brake();
	rightMotors.brake();
	// fix heading
	chassis.turnToHeading(0.0, 1000, {.minSpeed=10}, false);
	pros::delay(200);

	// turn to face middle goal
	chassis.setPose(0, 0 , 0);
	chassis.turnToHeading(-75.0, 1500, {.maxSpeed=70, .minSpeed=10}, false);
	leftMotors.brake();
	rightMotors.brake();

	// move to middle goal
	// ramp up
	pneumatic.set_value(true);
	bottomMotor.move(40);
	spedMotor.move(0);
	outMotor.move(0);
	chassis.setPose(0, 0, 0);
	chassis.moveToPose(0.0, 56.0*0.39, 0.0,  2000, {.maxSpeed=40, .minSpeed=20}, false);
	leftMotors.brake();
	rightMotors.brake();

	// score 3 balls to lower middle goal
	bottomMotor.move(-127);
	outMotor.move(-127);
	spedMotor.move(127);
	pros::delay(500);
	bottomMotor.move_velocity(-80);
	pros::delay(1000);
	bottomMotor.move(0);
	spedMotor.move(0);
	outMotor.move(0);
	// fix heading
	chassis.turnToHeading(0.0, 1000, {.minSpeed=20}, false);
	leftMotors.brake();
	rightMotors.brake();

	// reverse to match loads
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0.0, -134.0*0.39, 2500, {.forwards=false, .maxSpeed=100, .minSpeed=20}, false);
	leftMotors.brake();
	rightMotors.brake();
	// fix heading
	chassis.turnToHeading(0.0, 1000, {.minSpeed=10}, false);
	leftMotors.brake();
	rightMotors.brake();
	
	// turn to face match loads
	pros::delay(100);
	chassis.setPose(0, 0, 0);
	chassis.turnToHeading(-136.0, 1500, {.maxSpeed=70, .minSpeed=20}, false);
	leftMotors.brake();
	rightMotors.brake();
	// ramp down
	pneumatic.set_value(false);
	pros::delay(100);

	// move to match loads
	chassis.setPose(0, 0, 0);
	leftMotors.move(80);
	rightMotors.move(80);
	pros::delay(300);
	int start_tm = pros::millis();
	leftMotors.move(50);
	rightMotors.move(50);
	// start running rollers to intake match loads
	bottomMotor.move(127);
	spedMotor.move(-127);
	outMotor.move(127);	
	while (pros::millis()-start_tm < 700 && (std::abs(leftMotors.get_actual_velocity_all()[0]) > 10 || std::abs(rightMotors.get_actual_velocity_all()[0]) > 10)) {
		pros::delay(10);
	}

	// fix heading
	if (chassis.getPose(false, false).theta < 0.0) {
		chassis.swingToHeading(0.0, lemlib::DriveSide::LEFT, 500, {.minSpeed=30}, false);
	}
	else {
		chassis.swingToHeading(0.0, lemlib::DriveSide::RIGHT, 500, {.minSpeed=30}, false);
	}
	leftMotors.brake();
	rightMotors.brake();

	// move to long goal
	chassis.setPose(0, 0, 0);
	chassis.moveToPose(0.0, -70*0.39, 0.0, 1000, {.forwards=false, .maxSpeed=100, .minSpeed=50}, false);
	// press against long goal
	leftMotors.move(-40);
	rightMotors.move(-40);
	while (std::abs(leftMotors.get_actual_velocity_all()[0]) > 5 || std::abs(rightMotors.get_actual_velocity_all()[0]) > 5) {
		pros::delay(10);
	}
	// correct wrong heading if any before scoring long goal
	chassis.turnToHeading(0.0, 500, {.minSpeed=20}, false);
	leftMotors.move(-20);
	rightMotors.move(-20);
	// score long goal
	topMotor.move(127);
	pros::delay(1500);
	topMotor.move(0);

	// angle robot to right side of long goal
	// ramp up
	pneumatic.set_value(true);
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0.0, 20.0*0.39, 1500, {.minSpeed=40}, false);
	leftMotors.brake();
	rightMotors.brake();
	pros::delay(200);
	chassis.turnToHeading(130.0, 1500, {.maxSpeed=80, .minSpeed=20}, false);
	leftMotors.brake();
	rightMotors.brake();
	chassis.setPose(0, 0, 0);
	chassis.moveToPoint(0.0, 20.0*0.39, 1000, {.minSpeed=70}, false);
	rightMotors.brake();
	chassis.setPose(0, 0, 0);
	chassis.swingToHeading(50.0, lemlib::DriveSide::RIGHT, 1000, {.minSpeed=127}, false);
	leftMotors.brake();
	// descorer down
	hijack.set_value(false);
	chassis.setPose(0, 0, 0);
	// push balls into control zone
	start_tm = pros::millis();
	leftMotors.move(50);
	rightMotors.move(80);
	while (pros::millis()-start_tm < 700 && chassis.getPose(false, false).theta > -25){
		pros::delay(10);
	}
	leftMotors.brake();
	rightMotors.brake();
}