/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-22 14:50
 * Filename         : Device.hpp
 * Description      : 
 *********************************************************/

#ifndef _DEVICE_H
#define _DEVICE_H

#include "def.h"

class Device {
public:
	uint8_t ssm_status;
	uint32_t ssm_id;
	uint8_t ssm_lable[16];
	uint8_t motorStatus;
	uint8_t resetReason;
	uint32_t uptime;
	uint32_t alltime;
	uint32_t repUTCTime;
	uint16_t temp;				// 温度
	uint16_t hum;				// 湿度
	uint8_t MB_level;			// 药瓶液位
	uint8_t MT_level;			// 主箱液位

	Device() {
		ssm_status = 0x01;
		ssm_id = htobe32(uint32_t(1));
		strncpy((char*)ssm_lable, "CRAZY_MAD", strlen("CRAZY_MAD"));
		motorStatus = 0x01;
		resetReason = 0x01;
		uptime = htobe32(uint32_t(1000));
		alltime = htobe32(uint32_t(2000));
		temp = htobe16(uint16_t(20));
		hum = htobe16(uint16_t(80));
		MB_level = 0x01;
		MT_level = 0x01;
	}

	void makeStatus(dataBuf buf) {
		buf[0] = 0xA1;			// 厂家代码	1
		memcpy(buf+1, &ssm_status, 1);	// 主板子状态 2
		buf[2] = 0x01;			// 3
		buf[3] = 0x01;			// 4
		memcpy(buf+4, &ssm_id, 4);		// SSM_ID 8
		memcpy(buf+8, ssm_lable, 16);	// SSM_Lable 24
		memcpy(buf+24, &motorStatus, 1);	// Motor Status 25
		buf[25] = 0x00;					// 26
		memcpy(buf+26, &resetReason, 1);	// 复位原因 27
		memcpy(buf+27, &uptime, 4);		// 持续运行时间 31
		memcpy(buf+31, &alltime, 4);	// 从出厂持续到现在运行时间 35 
		memcpy(buf+35, &repUTCTime, 4);	// 数据包上传是UTC时间 39
		buf[39] = 0x00;					// 40
		memcpy(buf+40, &temp, 2);		// 温度 42
		memcpy(buf+42, &hum, 2);		// 湿度
		memcpy(buf+44, &MB_level, 1);	// MB_Level
		memcpy(buf+45, &MT_level, 1);	// MT_Level	
		// 46 + 18 + 2 = 66
	}
};

#endif
