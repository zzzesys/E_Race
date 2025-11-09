//
// Created by 20728 on 2025/11/6.
//

//
// Created by 20728 on 2025/11/6.
//

#include "motor.h"
#include "main.h"
// #include "queue.h"
#include "tim.h"

// 定义变量
MotorState motor[MOTOR_NUM];

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

    // 限制占空比范围 0-100
    if (duty < 0) duty = 0;
    if (duty > 100) duty = 100;

    motor[id].duty = duty;

    // TIM3 Period = 999, 所以ARR = 999, 实际周期是1000
    // duty范围是0-100，转换为CCR值：duty * 10.0f
    // 但CCR不能超过ARR，所以最大是999
    uint32_t ccr = (uint32_t)(duty * 10.0f);
    if (ccr > 999) ccr = 999;

    if (motor[id].id==0) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ccr);
    }
    else if (motor[id].id==1) {
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, ccr);
    }
}


void Motor_SetDirection(uint8_t id, uint8_t direction) {
    if (id >= MOTOR_NUM) return;
    motor[id].direction = direction;

    switch (direction) {
        case Slow_Stop:
            if (motor[id].id==0) {
                AIN1(GPIO_PIN_RESET);
                AIN2(GPIO_PIN_RESET);
            }
            else if (motor[id].id==1) {
                BIN1(GPIO_PIN_RESET);
                BIN2(GPIO_PIN_RESET);
            }
            break;
        case Fast_Stop:
            if (motor[id].id==0) {
                AIN1(GPIO_PIN_SET);
                AIN2(GPIO_PIN_SET);
            }
            else if (motor[id].id==1) {
                BIN1(GPIO_PIN_SET);
                BIN2(GPIO_PIN_SET);
            }
            break;
        case Front:
            if (motor[id].id==0) {
                AIN1(GPIO_PIN_SET);
                AIN2(GPIO_PIN_RESET);
            }
            else if (motor[id].id==1) {
                BIN1(GPIO_PIN_SET);
                BIN2(GPIO_PIN_RESET);
            }
            break;
        case Back:
            if (motor[id].id==0) {
                AIN1(GPIO_PIN_RESET);
                AIN2(GPIO_PIN_SET);
            }
            else if (motor[id].id==1) {
                BIN1(GPIO_PIN_RESET);
                BIN2(GPIO_PIN_SET);
            }
            break;
    }
}