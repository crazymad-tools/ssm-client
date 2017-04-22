/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-19 22:05
 * Filename         : Loop.h
 * Description      : 
 *********************************************************/

#ifndef _LOOP_H
#define _LOOP_H

#include "def.h"
#include "Socket.h"
#include "MakePacket.hpp"
#include "Device.hpp"
#include "MessageParse.hpp"
#include "Operation.hpp"

class Loop {
public:
	Loop(Socket* socket_) 
		: socket_(socket_), device_(), makePacket_(&device_), parse_(&device_)
   	{ }
	void loop() {
		while (true) {
			bool ret = socket_->socketConnect();
			if (ret) {
				break;
			} else {
				socket_->closeFd();
			}
			sleep(10);
		}
		login();
		while (true) {
			uint8_t buf[BUFSIZE] = { 0 };
			bool ret = socket_->socketRead(buf);
			if (!ret) {
				while (!ret) {
					ret = socket_->socketConnect();
				}
				login();
			}
			uint16_t timeLen;
			int cmdType = parse_.parse(buf);
			switch (cmdType) {
			case -1:			// 无效数据包
				//printf("无效数据包\n");
				break;
			case 0x05:			// 读取运行状态
				bzero(buf, sizeof buf);
				makePacket_.makeRunStatus(buf);
				socket_->socketWrite(buf);
				break;
			case 0x08:			// 强制打开风扇
				memcpy(&timeLen, buf+27, 2);
				timeLen = htobe16(timeLen);
				operation_.openFan(timeLen);
				break;	
			case 0x09:			// 强制打开电机
				memcpy(&timeLen, buf+27, 2);
				timeLen = htobe16(timeLen);
				operation_.openMotor(timeLen);
				break;
			default:
				break;
			}
		}
	}
	void login() {
		uint8_t sendBuf[BUFSIZE] = { 0 };
		uint8_t recvBuf[BUFSIZE] = { 0 };
		makePacket_.makeLogin(sendBuf);
		while (true) {
			socket_->socketWrite(sendBuf);
			//sleep(1);
			//socket_->socketWrite(sendBuf);
			//socket_->socketWrite(sendBuf);
			socket_->socketRead(recvBuf);
			uint32_t source_id;
			memcpy(&source_id, recvBuf+9, 4);
			printf("%d\n", htobe32(source_id));
			if (source_id == device_.ssm_id) {
				break;
			}
		}
		printf("login seccuess\n");
	}

private:
	Socket *socket_;
	MakePacket makePacket_;
	MessageParse parse_;
	Device device_;
	Operation operation_;
};

#endif

