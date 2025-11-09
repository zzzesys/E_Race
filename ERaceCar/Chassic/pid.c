//
// Created by 31358 on 2025/11/7.
//@brief PID函数库
//@param 目前包含增量式与位置式PID

#include "pid.h"
#include <math.h>


float Limit(float val,float max,float min) {
    return (val>min)?((val<max)?val:max):min;
}

//@brief pid结构体初始化函数
//@param 增量式与位置式各个参数都不同
void PID_Init(PID *pid,PID_TYPE Type,float kp,float ki,
    float kd,float sum_limit_max,float sum_limit_min,
    float out_limit_max,float out_limit_min){
    pid->type=Type;
    pid->kp=kp;
    pid->ki=ki;
    pid->kd=kd;

    pid->sum_limit_max=sum_limit_max;
    pid->sum_limit_min=sum_limit_min;
    pid->out_limit_max=out_limit_max;
    pid->out_limit_min=out_limit_min;

    pid->target=0;
    pid->error=pid->pre_error=pid->pre_pre_error=0;
    pid->sum_error=0;
    pid->output=0;
}

//@brief 设置PID目标值
void PID_SetTarget(PID *pid,float target) {
    pid->target=target;
}

//@brief 计算PID输出
//@param 增量式PID返回增量 位置式返回直接输出值
float PID_Calc(PID *pid,float input) {
    pid->error=pid->target-input;

    if (pid->type==PID_POSITION) {
        pid->sum_error+=pid->error;
        pid->sum_error=Limit(pid->sum_error,pid->sum_limit_max,pid->sum_limit_min);

        pid->output=pid->kp*pid->error+pid->ki*pid->sum_error+pid->kd*pid->error-pid->pre_error;
        pid->output=Limit(pid->output,pid->out_limit_max,pid->out_limit_min);

        pid->pre_pre_error=pid->pre_error;
        pid->pre_error=pid->error;

        return pid->output;
    }
    else if (pid->type==PID_DELTA) {
        pid->output=pid->kp*(pid->error-pid->pre_error)+pid->ki*pid->error+pid->kd*(pid->error-2*pid->pre_error+pid->pre_pre_error);
        pid->output=Limit(pid->output,pid->out_limit_max,pid->out_limit_min);

        pid->pre_pre_error=pid->pre_error;
        pid->pre_error=pid->error;

        return pid->output;
    }

    // 默认返回值（不应该到达这里，但为了消除警告）
    return 0.0f;
}
