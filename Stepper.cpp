#include <Arduino.h>
#include "Stepper.h"

Stepper::Stepper(unsigned int steps_per_rotation) :
  STEPS_PER_ROTATION(steps_per_rotation),
  steps(0)
{}

unsigned int Stepper::step_cw()
{
  ++steps;
  steps %= STEPS_PER_ROTATION;

  return steps;
}

unsigned int Stepper::step_ccw()
{
  if (steps == 0)
  {
    steps = STEPS_PER_ROTATION - 1;
  }
  else
  {
    --steps;
    steps %= STEPS_PER_ROTATION;
  }

  return steps;
}

unsigned int Stepper::get_steps()
{
  return steps;
}

double Stepper::get_angle()
{
  return (360.0 * STEPS_PER_ROTATION) / steps;
}
