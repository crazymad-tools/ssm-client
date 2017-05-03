/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-27 21:46
 * Filename         : Dig.hpp
 * Description      : 
 *********************************************************/

#ifndef _DIG_H
#define _DIG_H

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>

class Dig {
public:
	Dig(int port) 
	{
		if (port == 11) {
			PIN = RPI_GPIO_P1_11;
		} else if (port == 15) {
			PIN = RPI_GPIO_P1_15;
		}
		if (!bcm2835_init()) {
			exit(1);
		}
		bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
	}
	void open(/*int sec_*/) {
		bcm2835_gpio_write(PIN, HIGH);
		//bcm2835_delay(sec_*1000);
		//bcm2835_gpio_write(PIN, LOW);
	}
	void close() {
		bcm2835_gpio_write(PIN, LOW);
	}

private:
	int PIN;
};

#endif

