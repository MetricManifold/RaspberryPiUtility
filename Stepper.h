/*!
 * \class Stepper
 * \file Stepper.h
 * \brief Part of motor control. Manages stepper motor
 * \authors Steve Silber, Alex Yan
 * \date 2018-11
 */



#ifndef STEPPER_H
#define STEPPER_H

class Stepper
{
public:
  Stepper(unsigned int steps_per_rotation);

  unsigned int step_cw();
  unsigned int step_ccw();

  unsigned int get_steps_per_rotation();
  unsigned int get_steps();
  double get_angle();

private:
  const unsigned int STEPS_PER_ROTATION;
  unsigned int steps;
};

#endif
