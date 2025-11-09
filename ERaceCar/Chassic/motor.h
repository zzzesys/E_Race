//
// Created by 20728 on 2025/11/6.
//
#include "gpio.h"
#include "tim.h"


#ifndef ERACECAR_MOTOR_H
#define ERACECAR_MOTOR_H

#define MOTOR_NUM   2

#define AIN1(x) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, (x))
#define AIN2(x) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (x))
#define BIN1(x) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, (x))
#define BIN2(x) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, (x))




typedef enum {
    Front = 0,
    Back,
    Fast_Stop,
    Slow_Stop
}MotorDir;
typedef struct {
    uint8_t id;//电机ID
    MotorDir direction;                     //运动方向
    float tar_speed;                      //目标速度(rpm)
    // uint8_t actual_speed;                   //实际速度(rpm)  目前不需要
    float duty;                             //占空比（98%则输入98）
    // float max_duty;                         //最大占空比
    // float min_duty;                         //最小占空比


}MotorState;


MotorState motor[MOTOR_NUM];

#endif //ERACECAR_MOTOR_H