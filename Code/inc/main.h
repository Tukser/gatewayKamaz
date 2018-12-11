#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "init.h"
#include "communication.h"
#include "CANSPI.h"
/*#include "can.h"*/
#include "MCP2515.h"

xQueueHandle xMessageUsartTest = NULL;
TaskHandle_t xHandle;
xQueueHandle xMessageCanTest = NULL;

unsigned char accel_pedal = 0;
float xbr_accel_demand = 0.0;
#endif
