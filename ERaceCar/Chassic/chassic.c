//
// Created by 20728 on 2025/11/6.
//

#include "chassic.h"

#include "line.h"
#include "motor.h"

void StartChassicTask(void const* argument) {
    (void)argument;
    // 初始化电机方向和速度
    Motor_SetDirection(0, Front);
    Motor_SetDirection(1, Front);
    
    Motor_SetDuty(0, 10);
    Motor_SetDuty(1, 10);

    while (1) {
        // 电机控制任务
        Line_follow();
        osDelay(30);
    }

}


