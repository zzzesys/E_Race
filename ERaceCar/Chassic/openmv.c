//
// Created by 31358 on 2025/11/14.
//

#include "openmv.h"
#include "main.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>

// 与摄像头
uint8_t DMA_RxBuf[64];      // DMA循环缓冲区
uint8_t FrameBuf[64];       // 一帧数据存放处
uint8_t frame_ready = 0;

//与串口屏
uint8_t screen_rx;     // 用于接收1字节
uint8_t screen_cmd = 0;   // 供主循环读取

void DMA_Start(void) {
    HAL_UART_Receive_DMA(&huart3, DMA_RxBuf, sizeof(DMA_RxBuf));
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);  // 使能IDLE中断
}

void Send_To_Screen(const char* command) {
    // 确保转换为uint8_t*
    HAL_UART_Transmit(&huart1, (uint8_t*)command, strlen(command), 1000);

    // 修正：结束符长度固定为3，不是strlen(end_marker)
    uint8_t end_marker[3] = {0xFF, 0xFF, 0xFF};
    HAL_UART_Transmit(&huart1, end_marker, 3, 1000);
}



void Send_Char(char ch,const char* widget_id) {
    char buffer[30];
    sprintf(buffer,"%s.txt=\"%c\"",widget_id,ch);
    Send_To_Screen(buffer);
}



void TransmitTo(void)
{
    if (!frame_ready) return;
    frame_ready = 0;

    // 简单检查是否满足格式
    if (FrameBuf[0] == '$' && FrameBuf[2] == '#')
    {
        char cmd = FrameBuf[1];

        switch(cmd)
        {
            case '1':
                // 识别到 A（你之前映射是 A=1）
                Send_Char('a',"t0");
                break;

            case '2':
                // B
                Send_Char('b',"t0");
                break;

            case '3':
                // C
                Send_Char('c',"t0");
                break;

            case '0':
                // 箭头
                Send_Char('d',"t0");
                break;
            default:
                break;
        }
    }
}



