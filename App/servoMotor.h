#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include "system.h"
#include "stm32f10x.h"
#include "systick.h"

void Servo_PWM_Init(void);
void Servo_SetAngle(u8 Angle);

#endif