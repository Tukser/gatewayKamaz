#ifndef _CAN_H_
#define _CAN_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "CANSPI.h"

void vTaskAddMessageCAN_EEC2(void* params);
void vTaskAddMessageCAN_XBR(void* params);
void vTaskAddMessageCAN_TC1(void* params);


#endif // _CAN_H_
