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
	Serial.println(PORTD);
}


StepperMotor::~StepperMotor(void)
{
}

void StepperMotor::step(void)
{
	digitalWrite(step_pin, !digitalRead(step_pin));
}