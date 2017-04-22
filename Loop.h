/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-19 22:05
 * Filename         : Loop.h
 * Description      : 
 *********************************************************/

#ifndef _LOOP_H
#define _LOOP_H

#include "Socket.h"

class Loop {
public:
	Loop(Socket* socket_);
	void loop();

private:
	Socket* socket_;

};

#endif

