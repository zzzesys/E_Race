//
// Created by 31358 on 2025/11/7.
//@

#ifndef ERACECAR_PID_H
#define ERACECAR_PID_H

typedef enum {
    PID_POSITION,//位置式PID
    PID_DELTA //增量式PID
}PID_TYPE;

typedef struct {
    PID_TYPE type;
    float kp, ki, kd;
    float target;

    float error;
    float pre_error;
    float pre_pre_error;
    float sum_error;
    float output;

    float sum_limit_max;
    float sum_limit_min;
    float out_limit_max;
    float out_limit_min;

}PID;

void PID_Init(PID *pid,PID_TYPE Type,float kp,float ki,float kd,float sum_limit_max,float sum_limit_min,float out_limit_max,float out_limit_min);

void PID_SetTarget(PID *pid,float target);

float PID_Calc(PID *pid,float input);
#endif //ERPID_ACECAR_PID_H