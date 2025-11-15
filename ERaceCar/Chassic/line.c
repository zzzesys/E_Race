//
// Created by 31358 on 2025/11/8.
//

#include "line.h"
#include "motor.h"
#include "pid.h"
#include "main.h"
#include "cmsis_os.h"

#define LEFT 10000.0f
#define RIGHT -10000.0f
#define STOP 20000.0f
#define BASE_DUTY 13

float sensor_weight[8] = {25,14, 6.0, 1.0, -0.5, -2.5, -8.0, -18};



int sensor_val[8];
struct PID* line;

PID line_pid;

void LineCtrl_Init() {
    // 如果 PID_Init 的参数顺序是 (pid, mode, Kp, Ki, Kd, maxOut, minOut, maxIout, minIout)
    PID_Init(&line_pid, PID_POSITION, 1.4f, 0.0f, 0.05f, 10.0f, -10.0f, 10.0f, -10.0f);



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

    //直角转弯代码
    if (sensor_val[0]==1&&sensor_val[1]==1) {
        return RIGHT;
    }
    else if (sensor_val[6]==1&&sensor_val[7]==1) {
        return LEFT;
    }
    else if ((sensor_val[0]==1||sensor_val[1]==1||sensor_val[2]==1)&&(sensor_val[5]==1||sensor_val[6]==1||sensor_val[7]==1)) {
        return STOP;
    }
    else {
        return sum;
    }


}


void Line_follow(void) {
    float bias = Line_readsensor();
    osDelay(20);
    // bias = Limit(bias, 10.0f, -10.0f);
    if (bias==LEFT) {
        Motor_SetDuty(0,10);
        Motor_SetDuty(1,10);
        osDelay(450);

        Motor_SetDuty(0,40);
        Motor_SetDuty(1,0);
        osDelay(400);

        Motor_SetDuty(0,10);
        Motor_SetDuty(1,10);

        osDelay(80);
    }
    else if (bias==RIGHT) {
        Motor_SetDuty(0,10);
        Motor_SetDuty(1,10);
        osDelay(420);

        Motor_SetDuty(0,0);
        Motor_SetDuty(1,36);
        osDelay(330);

        Motor_SetDuty(0,10);
        Motor_SetDuty(1,10);

        osDelay(80);
    }
    else if (bias==STOP) {
        //先让小车停下
        Motor_SetDuty(0,0);
        Motor_SetDuty(1,0);
        osDelay(50);

        // //后退一段距离
        // Motor_SetDirection(0,Back);
        // Motor_SetDirection(1,Back);
        // Motor_SetDuty(0,20);
        // Motor_SetDuty(1,20);
        // osDelay(1000);

        //转入C点
        Motor_SetDirection(0,Front);
        Motor_SetDirection(1,Front);
        Motor_SetDuty(0,40);
        Motor_SetDuty(1,0);
        osDelay(450);

        Motor_SetDuty(0,0);
        Motor_SetDuty(1,40);
        osDelay(50);

        Motor_SetDuty(0,20);
        Motor_SetDuty(1,20);
        osDelay(500);

        //停止
        Motor_SetDuty(0,0);
        Motor_SetDuty(1,0);
        osDelay(10000);

    }
    else {
        float output = PID_Calc(&line_pid, bias);
        // output = Limit(output, 10.0f, -10.0f);   // 请务必把返回值赋回


        float left = BASE_DUTY + output*2.35;
        float right = BASE_DUTY - output*2.35;

        // 再次限制最终占空比在 0..100
        left = Limit(left, 100.0f, 0.0f);
        right = Limit(right, 100.0f, 0.0f);

        Motor_SetDuty(0, left);
        Motor_SetDuty(1, right);

        osDelay(30);

    }
}




