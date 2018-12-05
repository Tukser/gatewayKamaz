#include "can.h"

extern xQueueHandle xMessageCAN;

CAN_msg msg;

void vTaskAddMessageCAN_EEC2(void* param){
	const TickType_t xDelay = 50 / portTICK_PERIOD_MS; // repetition rate for EEC1 is 20ms
	
	unsigned char source_address = 0x27;
	unsigned char priority = 3;
	unsigned int PGN = 0x00F003;
	
	unsigned int identifier;
	identifier |= priority << 5; // top 3 bits
	identifier |= PGN << 8; // R + DP + PF + PS, 18 bits in the middle
	identifier |= source_address; // last byte
	
	msg.id = identifier;
	msg.format = EXTENDED_FORMAT;
	msg.type = DATA_FRAME;
	msg.len = 8;
	
	for (int i = 3; i < 8; i++) {
		msg.data[i] = 0xFF;
	}
	
	unsigned char kickdown_switch; 
	unsigned char low_idle;
	char accel_pedal;
	
	for(;;){
		
		if (accel_pedal > 97) {
			kickdown_switch = 1;
		} else {
			kickdown_switch = 0;
		}
		
		if (accel_pedal < 13) {
			low_idle = 1;
		} else {
			low_idle = 0;
		}
		
		msg.data[0] = 0xF0;
		msg.data[0] |= low_idle;
		msg.data[0] |= kickdown_switch << 2;
		
		msg.data[1] = (accel_pedal / 0.4);
		
		xQueueSendToBack(xMessageCAN, &msg, 0);
		
		vTaskDelay(xDelay);
	}
}