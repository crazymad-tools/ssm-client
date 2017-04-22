/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-19 20:58
 * Filename         : main.cc
 * Description      : 
 *********************************************************/

#include "def.h"
#include "Socket.h"
#include "MakePacket.hpp"
#include "Loop.hpp"

int main(int argc, char* argv[]) {
	Socket socks("182.254.219.134", 8002);
	Loop loop_(&socks);
	loop_.loop();

	return 0;
}
