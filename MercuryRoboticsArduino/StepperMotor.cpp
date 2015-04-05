#include "StepperMotor.h"


StepperMotor::StepperMotor
(
	pin_t step_pin,
	pin_t direction_pin,
	pin_t micro_select_1_pin,
	pin_t micro_select_2_pin,
	pin_t micro_select_3_pin
)
{
	this->step_pin = step_pin;
	this->direction_pin = direction_pin;
	this->micro_select_1_pin = micro_select_1_pin;
	this->micro_select_2_pin = micro_select_2_pin;
	this->micro_select_3_pin = micro_select_3_pin;

	pinMode(step_pin, OUTPUT);
	//pinMode(direction_pin, OUTPUT);
	//pinMode(micro_select_1_pin, OUTPUT);
	///pinMode(micro_select_2_pin, OUTPUT);
	//pinMode(micro_select_3_pin, OUTPUT);
}


StepperMotor::~StepperMotor(void)
{
}

void StepperMotor::step(void)
{
	*(portOutputRegister(digitalPinToPort(step_pin))) ^= digitalPinToBitMask(step_pin);

}

void StepperMotor::set_target_velocity(float v)
{
	target_velocity = min(MAX_VELOCITY, max(MIN_VELOCITY, v));

	interrupt_time_us = min(MAX_STEP_PERIOD_US, PERIOD_CONVERSION_RATIO / target_velocity);
}