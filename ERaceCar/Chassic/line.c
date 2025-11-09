//
// Created by 31358 on 2025/11/8.
//

#include "line.h"
#include "motor.h"
#include "pid.h"
#include "main.h"



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

}


