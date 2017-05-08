/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-22 16:32
 * Filename         : MessageParse.hpp
 * Description      : 
 *********************************************************/

#ifndef _MESSAGEPARSE_H
#define _MESSAGEPARSE_H

#include "def.h"
#include "Device.hpp"

class MessageParse {
public:
	MessageParse(Device* device_)
		: device_(device_)
	{ }
	uint8_t parse(dataBuf buf) {
		/*for (int i = 0; i < 100; i++) {
			printf("%02X ", (int)buf[i]);
		}
		printf("\n");*/
		if (buf[0] != 0x7E && buf[0] != 0x6E /*|| buf[4] != 0x00*/) {
			return -1;			// -1 表示数据无效
		}
		uint16_t len;
		memcpy(&len, buf+1, 2);	// 网络字节序的数据包长度
		len = htobe16(len);
		uint32_t dest;
		memcpy(&dest, buf+9, 4);
		//if (dest != device_->ssm_id) {
		//	return -1;
		//}
		uint8_t cmdType;
		memcpy(&cmdType, buf+13, 1);
		if (cmdType > 0x0A) {
			return -1;
		}
		printf("cmdType:%d\n", (int)cmdType);
		return static_cast<int>(cmdType);
	}	
private:
	Device* device_;
};

#endif
