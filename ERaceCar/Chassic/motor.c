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
        motor[i].max_duty = 100;
        motor[i].min_duty = 0;

    }
}


void Motor_SetDuty(uint8_t id, float duty) {
    if (id >= MOTOR_NUM) return;

    if (duty < motor[id].min_duty) {
        duty = motor[id].min_duty;
    }

    if (duty > motor[id].max_duty) {
        duty = motor[id].max_duty;
    }

    motor[id].duty = duty;

    uint32_t ccr = (uint32_t)(duty * 10.0f);

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ccr);




}


void Motor_SetDirection(uint8_t id, uint8_t direction) {
    if (id >= MOTOR_NUM) return;
    motor[id].direction = direction;

    switch (direction) {
        case Slow_Stop:

    }



}