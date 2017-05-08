/*********************************************************
 * Author           : crazy_mad
 * Last modified    : 2017-05-03 22:12
 * Filename         : Timer.hpp
 * Description      : 
 *********************************************************/

#ifndef _TIMER_H
#define _TIMER_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <set>

int getDistance(int hour, int min) {
	int distance;
	struct timespec time_;
	clock_gettime(CLOCK_REALTIME, &time_);
	struct tm nowtime;
	localtime_r(&time_.tv_sec, &nowtime);
	distance = (hour - nowtime.tm_hour)*3600 + (min - nowtime.tm_min)*60 - nowtime.tm_sec;
	return distance;
}

class Timer {
public:
	Timer(int) {
		memset(hour, -1, sizeof hour);
		memset(min, -1, sizeof min);
		// 创建四个timerfd
		printf("timerfds: ");
		for (int i = 0; i < 4; i++) {
			timer_fd[i] = timerfd_create(CLOCK_MONOTONIC, 0);
			printf("%d ", timer_fd[i]);
		}
		printf("\n");
	}
	void init(int hour[], int min[]) {
		// 设置四个定时器的时间
		for (int i = 0; i < 4; i++) {
			settime(i, hour[i], min[i]);
		}
	}
	void settime(int index, int hour, int min) {
		if (hour == this->hour[index] && min == this->min[index]) {
			return;			// 时间一致，没有必要重置时间和计时器
		} else {
			this->hour[index] = hour;
			this->min[index] = min;
			printf("hour:%d\tmin:%d\t", hour, min);
		}
		int distance = getDistance(hour, min);
		if (distance < 0) {
			distance = 24*3600 + distance;
		}
		printf("distance:%d\n", distance);
		struct itimerspec time_, interval;
		time_.it_value.tv_sec = distance;
		time_.it_value.tv_nsec = 0;
		timerfd_settime(timer_fd[index], 0, &time_, 0);
	}
	void reset(int index) {			// 重置定时器
		int distance = getDistance(hour[index], min[index]);
		struct itimerspec time_, interval;
		time_.it_value.tv_sec = distance;
		time_.it_value.tv_nsec = 0;
		timerfd_settime(timer_fd[index], 0, &time_, 0);
	}
	int timer_fd[4];			// 4个定时器的文件描述符(直接四个定时器解决问题，不复杂化)
private:
	int hour[4];				// 4个定时器的小时数
	int min[4];					// 4个定时器的分钟数
};

class Select {
public:
	
private:

};

#endif
