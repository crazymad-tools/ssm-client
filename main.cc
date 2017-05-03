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
#include "Dig.hpp"

int main(int argc, char* argv[]) {
	Dig dig(15);
	dig.close();
	freopen("/home/pi/ssm-client/config", "r", stdin);
	char addr[100];
	int port;
	scanf("%d\n%s", &port, addr);
	printf("%s %d\n", addr, port);
	Socket socks(addr, port);
	Loop loop_(&socks);
	loop_.loop();

	return 0;
}
