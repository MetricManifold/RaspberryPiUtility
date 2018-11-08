#ifndef FULL_STEP_CONTROLLER_H
#define FULL_STEP_CONTROLLER_H

#include "Stepper.h"

class FullStepController
{
public:
  FullStepController(unsigned int steps_per_rotation, unsigned int step_period, unsigned int step_pin, unsigned int dir_pin);

  unsigned int step_cw();
  unsigned int step_ccw();

  unsigned int run_by(unsigned int n_steps);
  unsigned int floor_run(double angle);
  unsigned int ceil_run(double angle);

  unsigned int get_step_period();
  unsigned int get_steps();
  double get_angle();

private:
  unsigned int step_period;
  unsigned int step_pin;
  unsigned int dir_pin;

  Stepper stepper;
};

#endif