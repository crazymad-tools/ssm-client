/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-22 19:20
 * Filename         : ConfigData.hpp
 * Description      : 
 *********************************************************/

#ifndef _CONFIGDATA_H
#define _CONFIGDATA_H

class ConfigData {
public:
	uint32_t ssmId;		// SSM_ID
	uint8_t ssmLable[16];
	uint8_t	controlPasswd[8];			// 设备的控制密码
	// 时间段1
	uint8_t timed1H;		// 时间段1的起始小时数
	uint8_t timed1M;		// 时间段1的起始分钟数
	uint8_t timed1Len;		// 时间段1的持续工作时间
	// 时间段2
	uint8_t timed2H;		// 时间段2的起始小时数
	uint8_t timed2M;		// 时间段2的起始分钟数
	uint8_t timed2Len;		// 时间段2的持续工作时间
	// 时间段3
	uint8_t timed3H;		// 时间段3的起始小时数
	uint8_t timed3M;		// 时间段3的起始分钟数
	uint8_t timed3Len;		// 时间段3的持续工作时间
	// 时间段4
	uint8_t timed4H;		// 时间段4的起始小时数
	uint8_t timed4M;		// 时间段4的起始分钟数
	uint8_t timed4Len;		// 时间段4的持续工作时间

};

#endif
