#include <Arduino.h>
#include "FullStepController.h"

FullStepController::FullStepController(unsigned int steps_per_rotation, unsigned int step_period, unsigned int step_pin, unsigned int dir_pin) :
  step_period(step_period),
  step_pin(step_pin),
  dir_pin(dir_pin),
  stepper(steps_per_rotation)
{
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
}

unsigned int FullStepController::step_cw()
{
  digitalWrite(dir_pin, LOW);
  digitalWrite(step_pin, HIGH);
  delay(step_period);
  digitalWrite(step_pin, LOW);
  
  return stepper.step_cw();
}

unsigned int FullStepController::step_ccw()
{
  digitalWrite(dir_pin, HIGH);
  digitalWrite(step_pin, HIGH);
  delay(step_period);
  digitalWrite(step_pin, LOW);
  
  return stepper.step_ccw();
}

unsigned int FullStepController::run_by(unsigned int n_steps)
{
  for (auto i = n_steps; i > 0; --i)
  {
    stepper.step_cw();
    
    delay(step_period);
  }

  return stepper.get_steps();
}

unsigned int FullStepController::floor_run(double angle)
{
  auto end_step = floor(angle / 360 * stepper.get_steps_per_rotation());
  run_by(end_step);

  return stepper.get_steps();
}

unsigned int FullStepController::ceil_run(double angle)
{
  auto end_step = ceil(angle / 360 * stepper.get_steps_per_rotation());
  run_by(end_step);

  return stepper.get_steps();
}

unsigned int FullStepController::get_step_period()
{
  return step_period;
}

unsigned int FullStepController::get_steps()
{
  return stepper.get_steps();
}

double FullStepController::get_angle()
{
  return stepper.get_steps() * 360.0 / stepper.get_steps_per_rotation();
}
