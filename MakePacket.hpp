/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-20 05:38
 * Filename         : MakePacket.hpp
 * Description      : 
 *********************************************************/

#ifndef _MAKEPACKET_H
#define _MAKEPACKET_H

#include "def.h"

class MakePacket {
public:
	MakePacket() 
		: SERV({0x53, 0x45, 0x52, 0x56})
   	{
		memset(FF_4, 0xFF, sizeof FF_4);		// 将FF_4初始化为0xFFFFFFFF
	}
	void makeLogin(dataBuf buf) {
		makeHeadTail(buf, 70);					// head and Channel		4byte
		buf[4] = 0x01;					// Direction			1byte
		memcpy(buf+5, FF_4, 4);			// Source 填充为0xFF	4byte
		memcpy(buf+9, SERV, 4);			// Dest					4byte
		buf[13] = 0x04;					// CmdTyep login操作	1byte
		buf[14] = 0x01;					// Op_Status			1byte
		makeRunStatuData(buf+15);		// RunStatuData			
		uint16_t len = 70;
	}
	void makeRunStatuData(dataBuf buf) {
		buf[0] = 0xA1;					// Factory_code			1byte
		buf[1] = 0x01;					// EMS主板状态	0x01表示正常	1byte
		buf[2] = 0x01;					// SSM主板硬件版本		1byte
		buf[3] = 0x01;					// 
	}
	void makeHeadTail(dataBuf buf, uint16_t len) {
		buf[0] = 0x7E;			// 引导头
		memcpy(buf+1, &len, 2);
		buf[3] = 0x00;			// 数据传输通道
		memcpy(buf+len, &len, 2);
	}
private:
	uint8_t FF_4[4];			// 4位全部为FF
	uint8_t SERV[4];			// 
};


#endif


