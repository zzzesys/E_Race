//
// Created by 20728 on 2025/11/6.
//

#include "motor.h"

void Motor_Init() {

    for (int i = 0; i < MOTOR_NUM; i++) {
        motor[i].direction = Slow_Stop;
        motor[i].id = i;
        motor[i].duty = 0;
        motor[i].tar_speed = 0;

    }
}