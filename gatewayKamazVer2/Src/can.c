#include "can.h"

extern xQueueHandle xMessageCAN;
extern unsigned char accel_pedal;
extern float xbr_accel_demand;

void vTaskAddMessageCAN_EEC2(void* param){
	const TickType_t xDelay = 50 / portTICK_PERIOD_MS; // repetition rate for EEC2 is 50ms
	
	uCAN_MSG msg;
	
	unsigned char source_address = 0x27;
	unsigned char priority = 3;
	unsigned int PGN = 0x00F003;
	
	unsigned int identifier;
	identifier |= priority << 5; // top 3 bits
	identifier |= PGN << 8; // R + DP + PF + PS, 18 bits in the middle
	identifier |= source_address; // last byte
	
	msg.id = identifier;
	msg.idType = dEXTENDED_CAN_MSG_ID_2_0B;
	msg.dlc = 8;
	
	msg.data3 = 0xFF;
	msg.data4 = 0xFF;
	msg.data5 = 0xFF;
	msg.data6 = 0xFF;
	msg.data7 = 0xFF;
	
	unsigned char kickdown_switch; 
	unsigned char low_idle;
	
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
		
		msg.data0 = 0xF0;
		msg.data0 |= low_idle;
		msg.data0 |= kickdown_switch << 2;
		
		msg.data1 = (accel_pedal / 0.4);
		
		xQueueSendToBack(xMessageCAN, &msg, 0);
		
		vTaskDelay(xDelay);
	}
}

void vTaskAddMessageCAN_XBR(void* param){
		const TickType_t xDelay = 20 / portTICK_PERIOD_MS; // repetition rate for XBR is 20ms (200 when no action)
		
		unsigned char ebi_mode = 2;
		unsigned char xbr_priority;
		unsigned char xbr_control_mode = 2; // acceleration control with maximum node
		unsigned int accel_demand_buffer = 0;
		unsigned char counter = 0;
		int i;
	
		uCAN_MSG msg;
	
		unsigned char source_address = 0x27;
		unsigned char priority = 3;
		unsigned int checksum;
		unsigned int PGN = 0x00040B;
	
		unsigned int identifier;
		identifier |= priority << 5; // top 3 bits
		identifier |= PGN << 8; // R + DP + PF + PS, 18 bits in the middle
		identifier |= source_address; // last byte
	
		msg.id = identifier;
		msg.idType = dEXTENDED_CAN_MSG_ID_2_0B;
		msg.dlc = 8;
		int t = 0;
		for (;;) {
				if (xbr_accel_demand < -0.001) {
					xbr_priority = 3; // low priority
					ebi_mode = 0; // no endurance brake integration allowed
					xbr_control_mode = 0; // override disabled
					t = 0;
				} else {
					t = (t+1)%10;
					xbr_priority = 0; // highest priority
					ebi_mode = 1; // only endurance brake allowed;
					xbr_control_mode = 2; // acceleration control with maximum mode
				}
			
				
				if(t == 0)
				{
					counter = (counter + 1) % 16;
					accel_demand_buffer = (int)((xbr_accel_demand + 15.687)	/ 0.00048828125);
					
					msg.data0 = accel_demand_buffer & 0xFF;
					msg.data1 = accel_demand_buffer >> 8; 
					msg.data2 = ebi_mode | xbr_priority<<2 | xbr_control_mode<<4 | 0xC0;
					msg.data3 = 0xFF; // urgency
					msg.data4 = 0xFF; // not used
					msg.data5 = 0xFF; // not used
					msg.data6 = 0xFF; // not used
					
					checksum = counter & 0x0F + msg.data0 + msg.data1 + msg.data2 + msg.data3 + msg.data4 msg.data5 + msg.data6;

					checksum += (identifier & 0xFF) + ((identifier >> 8) & 0xFF) + ((identifier >> 16) & 0xFF) + ((identifier >> 24) & 0xFF);
					checksum = ((checksum >> 4) + checksum) & 0x0F;
					
					msg.data7 = (checksum  << 4) | counter;
					
					xQueueSendToBack(xMessageCAN, &msg, 0);
				}
				vTaskDelay(xDelay);
		}
}