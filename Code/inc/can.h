#ifndef _CAN_H_
#define _CAN_H_

#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

#define DATA_FRAME       0
#define REMOTE_FRAME     1

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "CANSPI.h"

typedef struct  {
  unsigned int   id;                 // 29 bit identifier
  unsigned char  data[8];            // Data field
  unsigned char  len;                // Length of data field in bytes
  unsigned char  format;             // 0 - STANDARD, 1- EXTENDED IDENTIFIER
  unsigned char  type;               // 0 - DATA FRAME, 1 - REMOTE FRAME
} CAN_msg;

extern xQueueHandle xMessageCAN;
extern unsigned char accel_pedal;
extern float xbr_accel_demand;

void vTaskAddMessageCAN_EEC2(void* params);
void vTaskAddMessageCAN_XBR(void* params);
void vTaskAddMessageCAN_TC1(void* params);


#endif // _CAN_H_