/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-22 18:27
 * Filename         : Operation.hpp
 * Description      : 
 *********************************************************/

#ifndef _OPERATION_H
#define _OPERATION_H

#include "def.h"
#include <sys/time.h>
#include <sys/select.h>
#include <time.h>
//#include "Dig.hpp"
//#include "Thread.hpp"

void threadOpenM(int len) {
	//sleep(len);
	//Dig dig;
	//dig.open();
	/*struct timeval timer;
	timer.tv_sec = len;
	select(0, NULL, NULL, NULL, &timer);
	//dig.close();
	printf("close Motor!\n");
	exit(1);
	*/
	char param[3][10];
	sprintf(param[0], "%d", len);
	sprintf(param[1], "%d", 11);
	sprintf(param[2], "%s", "Motor");
	execl("./open/open", "./open/open", param[0], param[1], param[2]);
}
void threadOpenF(int len) {
	//sleep(len);
	/*struct timeval timer;
	timer.tv_sec = len;
	select(0, NULL, NULL, NULL, &timer);
	printf("close Fan!\n");
	exit(1);*/
	char param[3][10];
	sprintf(param[0], "%d", len);
	sprintf(param[1], "%d", 11);
	sprintf(param[2], "%s", "Motor");
	execl("./open/open", "./open/open", param[0], param[1], param[2]);
}

class Operation {
public:
	void openMotor(uint16_t timeLen) {
		printf("open motor for %d seconds\n", static_cast<int>(timeLen));
		if (fork() == 0) {			// 子进程
			threadOpenM(static_cast<int>(timeLen));
		} else {					// 父进程
			return;
		}
		//printf("...\n");
		//sleep(static_cast<int>(timeLen));
		//printf("close motor\n");
		/*for (int i = 0; i < 4; i++) {
			if (!threads[i].statu()) {
				threads[i].start(boost::bind(&threadOpenM, static_cast<int>(timeLen)));
				break;
			}
		}*/
	}
	void openFan(uint16_t timeLen) {
		printf("open fan for %d seconds\n", static_cast<int>(timeLen));
		if (fork() == 0) {			// 子进程
			threadOpenF(static_cast<int>(timeLen));
		} else {					// 父进程
			return;
		}
		//printf("...\n");
		//sleep(static_cast<int>(timeLen));
		//printf("close fan\n");
		/*for (int i = 0; i < 4; i++) {
			if (!threads[i].statu()) {
				threads[i].start(boost::bind(&threadOpenF, static_cast<int>(timeLen)));
				break;
			}
		}*/
	}

private:
	//Thread threads[4];
};

#endif
