//
// Created by 20728 on 2025/11/6.
//

#include "motor.h"
#include "main.h"
#include "tim.h"


void Pwm_Init(void) {
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}

void Motor_Init() {

    for (int i = 0; i < MOTOR_NUM; i++) {
        motor[i].direction = Slow_Stop;
        motor[i].id = i;
        motor[i].duty = 0;
        motor[i].tar_speed = 0;
        //[i].max_duty = 100;
        //motor[i].min_duty = 0;

    }
}


void Motor_SetDuty(uint8_t id, float duty) {
    if (id >= MOTOR_NUM) return;

    motor[id].duty = duty;

    uint32_t ccr = (uint32_t)(duty * 10.0f);

    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, ccr);
}


void Motor_SetDirection(uint8_t id, uint8_t direction) {
    if (id >= MOTOR_NUM) return;
    motor[id].direction = direction;

    switch (direction) {
        case Slow_Stop:
            AN1()

    }



}