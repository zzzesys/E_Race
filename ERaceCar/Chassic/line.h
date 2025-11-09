//
// Created by 31358 on 2025/11/8.
//

#ifndef ERACECAR_LINE_H
#define ERACECAR_LINE_H

#include "main.h"
#include "pid.h"

// 假设 S1~S8 分别连接到 PE0~PE7
#define S1 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0)
#define S2 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1)
#define S3 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2)
#define S4 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3)
#define S5 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4)
#define S6 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5)
#define S7 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)
#define S8 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7)



float sensor_weight[8]={10,5,0.5,0.35,-0.35,-0.5,-5,-10};
int sensor_val[8];

struct PID*line;

void LineCtrl_Init();
float Line_readsensor();
void Line_follow(PID*pid);

#endif //ERACECAR_LINE_H