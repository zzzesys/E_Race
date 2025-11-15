//
// Created by 31358 on 2025/11/14.
//

#ifndef OPENMV_H
#define OPENMV_H

#include "stm32f1xx_hal.h"

// 变量声明（定义在 openmv.c 中）
extern uint8_t DMA_RxBuf[64];      // DMA循环缓冲区
extern uint8_t FrameBuf[64];       // 一帧数据存放处
extern uint8_t frame_ready;

void DMA_Start(void);
void Send_To_Screen(const char* command);
void Send_Char(char ch,const char* widget_id);
void TransmitTo(void);
#endif //OPENMV_H