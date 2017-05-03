/*********************************************************
 * Author           : crazy_mad
 * Last modified    : 2017-05-03 17:31
 * Filename         : main.cc
 * Description      : 
 *********************************************************/

#include "Dig.hpp"

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

int main(int argc, char *argv[]) {
	int length;
	int pinNum;
	sscanf(argv[1], "%d", &length);
	sscanf(argv[2], "%d", &pinNum);
	printf("open %s for %ds  pinNum:%d\n", argv[3], length, pinNum);
	Dig dig(pinNum);
	dig.open();
	struct timeval timer;
	timer.tv_sec = length;
	select(0, NULL, NULL, NULL, &timer);
	dig.close();
	printf("close %s\n", argv[3]);

	return 0;
}
