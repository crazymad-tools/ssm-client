/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-20 05:38
 * Filename         : MakePacket.hpp
 * Description      : 
 *********************************************************/

#ifndef _MAKEPACKET_H
#define _MAKEPACKET_H

#include "def.h"
#include "Device.hpp"
#include <netinet/in.h>

class MakePacket {
public:
	MakePacket(Device* device_) 
		: SERV({0x53, 0x45, 0x52, 0x56}), device_(device_)
   	{
		memset(FF_4, 0xFF, sizeof FF_4);		// 将FF_4初始化为0xFFFFFFFF
	}
	void makeLogin(dataBuf buf) {
		makeHeadTail(buf, 87);					// head and Channel		4byte
		memcpy(buf+5, FF_4, 4);			// Source 填充为0xFF	4byte
		memcpy(buf+9, SERV, 4);			// Dest					4byte
		buf[13] = 0x04;					// CmdTyep login操作	1byte
		buf[14] = 0x01;					// Op_Status			1byte
		//uint32_t ssm_id = device_.ssm_id;
		//ssm_id = htobe32(ssm_id);
		memcpy(buf+15, &(device_->ssm_id), 4);
		//makeRunStatuData(buf+19);		// RunStatuData			
		device_->makeStatus(buf+19);
		//uint16_t len = 87;
	}
	void makeRunStatus(dataBuf buf) {
		makeHeadTail(buf, 68);
		memcpy(buf+5, &(device_->ssm_id), 4);
		memcpy(buf+9, SERV, 4);
		buf[13] = 0x05;					// 操作代码
		buf[14] = 0x01;					// 操作成功
		device_->makeStatus(buf+15);	// 生成设备状态数据包内容
	}
	void makeHeadTail(dataBuf buf, uint16_t len) {
		int len_ = htobe16(len);
		buf[0] = 0x7E;			// 引导头
		memcpy(buf+1, &len_, 2);
		buf[3] = 0x00;			// 数据传输通道
		len_ = htobe16(len-2);
		memcpy(buf+len, &len_, 2);
		buf[4] = 0x01;					// Direction			1byte
	}
private:
	uint8_t FF_4[4];			// 4位全部为FF
	uint8_t SERV[4];			// 
	Device *device_;
};


#endif


