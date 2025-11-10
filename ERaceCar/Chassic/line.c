//
// Created by 31358 on 2025/11/8.
//

#include "line.h"
#include "motor.h"
#include "pid.h"
#include "main.h"
#include "cmsis_os.h"

float sensor_weight[8] = {24, 13, 5, 1.0, -0.5, -2, -5, -12};



int sensor_val[8];
struct PID* line;

PID line_pid;

void LineCtrl_Init() {
    // 如果 PID_Init 的参数顺序是 (pid, mode, Kp, Ki, Kd, maxOut, minOut, maxIout, minIout)
    PID_Init(&line_pid, PID_POSITION, 1.5f, 0.0f, 0.06f, 10.0f, -10.0f, 10.0f, -10.0f);



    PID_SetTarget(&line_pid,0);
}
float Line_readsensor() {

    // 灰度传感器编号：1~8，左到右
    sensor_val[0] = (S1 == 1) ? 1 : 0;
    sensor_val[1] = (S2 == 1) ? 1 : 0;
    sensor_val[2] = (S3 == 1) ? 1 : 0;
    sensor_val[3] = (S4 == 1) ? 1 : 0;
    sensor_val[4] = (S5 == 1) ? 1 : 0;
    sensor_val[5] = (S6 == 1) ? 1 : 0;
    sensor_val[6] = (S7 == 1) ? 1 : 0;
    sensor_val[7] = (S8 == 1) ? 1 : 0;

    float sum=0;
    for (int i = 0; i < 8; i++) {
        sum+=(float)sensor_val[i]*sensor_weight[i];
    }

    return sum;
}


void Line_follow(void) {
    float bias = Line_readsensor();
    osDelay(20);
    // bias = Limit(bias, 10.0f, -10.0f);

    float output = PID_Calc(&line_pid, bias);
    // output = Limit(output, 10.0f, -10.0f);   // 请务必把返回值赋回

    const float base_duty = 10.0f;
    // const float scale = 3.0f;   // recommended

    float left = base_duty + output*2.5;
    float right = base_duty - output*2.5;

    // 再次限制最终占空比在 0..100
    left = Limit(left, 100.0f, 0.0f);
    right = Limit(right, 100.0f, 0.0f);

    Motor_SetDuty(0, left);
    Motor_SetDuty(1, right);

    osDelay(50);
}



