#include "can.h"

extern xQueueHandle xMessageCAN;

CAN_msg msg;

void vTaskAddMessageCAN_EEC1(void* param){
	const TickType_t xDelay = 20 / portTICK_PERIOD_MS; // repetition rate for EEC1 is 20ms
	
	unsigned char source_address = 204; // TODO ASSIGN REAL SOURCE ADDRESS
	unsigned char priority = 3;
	unsigned int PGN = 0x00F004;
	
	unsigned int identifier;
	identifier |= priority << 5; // top 3 bits
	identifier |= PGN << 8; // R + DP + PF + PS, 18 bits in the middle
	identifier |= source_address; // last byte
	
	msg.id = identifier;
	msg.format = STANDARD_FORMAT;
	msg.type = DATA_FRAME;
	msg.len = 8;
	
	for (int i = 0; i < 8; i++) {
		msg.data[i] = 0;
	}
	
	unsigned char percent_torque = 0;
	unsigned int engine_speed = 0;
	
	for(;;){
		msg.data[2] = percent_torque;
		msg.data[3] = engine_speed & 0xFF; 
		msg.data[4] = (engine_speed >> 8) & 0xFF;
		vTaskDelay(xDelay);
	}
}