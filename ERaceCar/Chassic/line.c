//
// Created by 31358 on 2025/11/8.
//

#include "line.h"
#include "motor.h"
#include "pid.h"
#include "main.h"

// 定义变量
float sensor_weight[8] = {10, 5, 0.5, 0.35, -0.35, -0.5, -5, -10};
int sensor_val[8];
struct PID* line;

PID line_pid;

void LineCtrl_Init() {
    PID_Init(&line_pid,PID_POSITION,1.2f,0.0f,0.02f,100,-100,100,-100);
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


void Line_follow(PID*pid) {
    float bias=Line_readsensor();

    bias/=10.0f;
    bias=Limit(bias,1.0f,-1.0f);

    float output=PID_Calc(&line_pid,bias);

    Motor_SetDuty(0,motor[0].duty-output*10);
    Motor_SetDuty(1,motor[1].duty+output*10);

}


