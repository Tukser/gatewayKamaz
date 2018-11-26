#ifndef INIT_H
#define INIT_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x_spi.h"

#define RXF0SIDH 0x00
#define RXF0SIDL 0x01
#define RXF0EID8 0x02
#define RXF0EID0 0x03

#define RXF1SIDH 0x04
#define RXF1SIDL 0x05
#define RXF1EID8 0x06
#define RXF1EID0 0x07

#define RXF2SIDH 0x08
#define RXF2SIDL 0x09
#define RXF2EID8 0x0A
#define RXF2EID0 0x0B

#define BFPCTRL 0x0C
#define B1BFS 0x20
#define B0BFS 0x10
#define B1BFE 0x08
#define B0BFE 0x04
#define B1BFM 0x02
#define B0BFM 0x01

#define TXRTSCTRL 0x0D
#define B2RTS 0x20
#define B1RTS 0x10
#define B0RTS 0x08
#define B2RTSM 0x04
#define B1RTSM 0x02
#define B0RTSM 0x01

#define CANSTAT 0x0E
#define OPMOD2 0x80
#define OPMOD1 0x40
#define OPMOD0 0x20
#define ICOD2 0x08
#define ICOD1 0x04
#define ICOD0 0x02

#define CANCTRL 0x0F
#define REQOP2 0x80
#define REQOP1 0x40
#define REQOP0 0x20
#define ABAT 0x10
#define OSM 0x08
#define CLKEN 0x04
#define CLKPRE1 0x02
#define CLKPRE0 0x01

#define RXF3SIDH 0x10
#define RXF3SIDL 0x11
#define RXF3EID8 0x12
#define RXF3EID0 0x13

#define RXF4SIDH 0x14
#define RXF4SIDL 0x15
#define RXF4EID8 0x16
#define RXF4EID0 0x17

#define RXF5SIDH 0x18
#define RXF5SIDL 0x19
#define RXF5EID8 0x1A
#define RXF5EID0 0x1B

#define TEC 0x1C
#define REC 0x1D

#define RXM0SIDH 0x20
#define RXM0SIDL 0x21
#define RXM0EID8 0x22
#define RXM0EID0 0x23

#define RXM1SIDH 0x24
#define RXM1SIDL 0x25
#define RXM1EID8 0x26
#define RXM1EID0 0x27

#define CNF3 0x28
#define SOF 0x80
#define WAKFIL 0x40
#define PHSEG22 0x04
#define PHSEG21 0x02
#define PHSEG20 0x01

#define CNF2 0x29
#define BTLMODE 0x80
#define SAM 0x40
#define PHSEG12 0x20
#define PHSEG11 0x10
#define PHSEG10 0x08
#define PRSEG2 0x04
#define PRSEG1 0x02
#define PRSEG0 0x01

#define CNF1 0x2A
#define SJW1 0x80
#define SJW0 0x40
#define BRP5 0x20
#define BRP4 0x10
#define BRP3 0x08
#define BRP2 0x04
#define BRP1 0x02
#define BRP0 0x01

#define CANINTE 0x2B
#define MERRE 0x80
#define WAKIE 0x40
#define ERRIE 0x20
#define TX2IE 0x10
#define TX1IE 0x08
#define TX0IE 0x04
#define RX1IE 0x02
#define RX0IE 0x01

#define CANINTF 0x2C
#define MERRF 0x80
#define WAKIF 0x40
#define ERRIF 0x20
#define TX2IF 0x10
#define TX1IF 0x08
#define TX0IF 0x04
#define RX1IF 0x02
#define RX0IF 0x01

#define EFLG 0x2D
#define RX1OV 0x80
#define RRX0OVR 0x40
#define TXBO 0x20
#define TXEP 0x10
#define RXEP 0x08
#define TXWAR 0x04
#define RXWAR 0x02
#define EWARN 0x01

#define TXB0CTRL 0x30
#define ABTF 0x40
#define MLOA 0x20
#define TXERR 0x10
#define TXREQ 0x08
#define TXP1 0x02
#define TXP0 0x01
#define TXP_MASK 0x03

#define TXB0SIDH 0x31
#define TXB0SIDL 0x32
#define TXB0EID8 0x33
#define TXB0EID0 0x34
#define TXB0DLC 0x35
#define TXB0D0 0x36
#define TXB0D1 0x37
#define TXB0D2 0x38
#define TXB0D3 0x39
#define TXB0D4 0x3A
#define TXB0D5 0x3B
#define TXB0D6 0x3C
#define TXB0D7 0x3D

#define TXB1CTRL 0x40
#define TXB1SIDH 0x41
#define TXB1SIDL 0x42
#define TXB1EID8 0x43
#define TXB1EID0 0x44
#define TXB1DLC 0x45
#define TXB1D0 0x46
#define TXB1D1 0x47
#define TXB1D2 0x48
#define TXB1D3 0x49
#define TXB1D4 0x4A
#define TXB1D5 0x4B
#define TXB1D6 0x4C
#define TXB1D7 0x4D

#define TXB2CTRL 0x50
#define TXB2SIDH 0x51
#define TXB2SIDL 0x52
#define TXB2EID8 0x53
#define TXB2EID0 0x54
#define TXB2DLC 0x55
#define TXB2D0 0x56
#define TXB2D1 0x57
#define TXB2D2 0x58
#define TXB2D3 0x59
#define TXB2D4 0x5A
#define TXB2D5 0x5B
#define TXB2D6 0x5C
#define TXB2D7 0x5D

#define RXB0CTRL 0x60
#define RXM1 0x40
#define RXM0 0x20
#define RXRTR 0x08
#define BUKT 0x04
#define BUKT1 0x02
#define FILHIT0 0x01

//rx buffers regs
#define RXB0SIDH 0x61
#define RXB0SIDL 0x62
#define RXB0EID8 0x63
#define RXB0EID0 0x64
#define RXB0DLC 0x65
#define RXB0D0 0x66
#define RXB0D1 0x67
#define RXB0D2 0x68
#define RXB0D3 0x69
#define RXB0D4 0x6A
#define RXB0D5 0x6B
#define RXB0D6 0x6C
#define RXB0D7 0x6D

#define RXB1CTRL 0x70
#define FILHIT2 0x04
#define FILHIT1 0x02

#define RXB1SIDH 0x71
#define RXB1SIDL 0x72
#define RXB1EID8 0x73
#define RXB1EID0 0x74
#define RXB1DLC 0x75
#define RXB1D0 0x76
#define RXB1D1 0x77
#define RXB1D2 0x78
#define RXB1D3 0x79
#define RXB1D4 0x7A
#define RXB1D5 0x7B
#define RXB1D6 0x7C
#define RXB1D7 0x7D

#define SID10 0x80
#define SID9 0x40
#define SID8 0x20
#define SID7 0x10
#define SID6 0x08
#define SID5 0x04
#define SID4 0x02
#define SID3 0x01
#define SID2 0x80
#define SID1 0x40
#define SID0 0x20
#define SRR 0x10
#define IDE 0x08
#define EXIDE 0x08
#define EID17 0x02
#define EID16 0x01
#define EID15 0x80
#define EID14 0x40
#define EID13 0x20
#define EID12 0x10
#define EID11 0x08
#define EID10 0x04
#define EID9 0x02
#define EID8 0x01
#define EID7 0x80
#define EID6 0x40
#define EID5 0x20
#define EID4 0x10
#define EID3 0x08
#define EID2 0x04
#define EID1 0x02
#define EID0 0x01

#define RTR 0x40
#define RB1 0x20
#define RB0 0x10

#define DLC3 0x08
#define DLC2 0x04
#define DLC1 0x02
#define DLC0 0x01
#define DLEN_MASK 0x0F

//SPI instructions

#define CMD_RESET 0xC0
#define CMD_READ 0x03
#define CMD_READ_RX 0x90
#define RX0ID 0x00
#define RX0DATA 0x02
#define RX1ID 0x04
#define RX1DATA 0x06
#define RX_MASK 0x06

#define CMD_WRITE 0x02
#define CMD_WRITE_TX 0x40
#define TX0ID 0x00
#define TX0DATA 0x01
#define TX1ID 0x02
#define TX1DATA 0x03
#define TX2ID 0x04
#define TX2DATA 0x05
#define TX_MASK 0x07

#define CMD_RTS 0x80
#define CMD_RTS0 0x01
#define CMD_RTS1 0x02
#define CMD_RTS2 0x04
#define CMD_RTS_MASK 0x07

#define CMD_READ_STATUS 0xA0
#define CMD_RX_STATUS 0xB0
#define RX_STATUS_NOMSG 0x00
#define RX_STATUS_MSG0 0x40
#define RX_STATUS_MSG1 0x80
#define RX_STATUS_MSGBOTH 0xC0

#define RX_STATUS_DATA 0x00
#define RX_STATUS_REMOTE 0x10
#define RX_STATUS_EXTDATA 0x20
#define RX_STATUS_EXTREMOTE 0x30

#define RX_STATUS_RXF0 0x00
#define RX_STATUS_RXF1 0x01
#define RX_STATUS_RXF2 0x02
#define RX_STATUS_RXF3 0x03
#define RX_STATUS_RXF4 0x04
#define RX_STATUS_RXF5 0x05
#define RX_STATUS_RXF0ROLL 0x06
#define RX_STATUS_RXF1ROLL 0x07

#define CMD_BIT_MODIFY 0x05



void initTask(void);
unsigned char sendMessageSPI250Task(unsigned char command, unsigned char data);


#endif
