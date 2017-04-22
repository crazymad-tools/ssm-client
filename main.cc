/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-19 20:58
 * Filename         : main.cc
 * Description      : 
 *********************************************************/

#include "def.h"
#include "Socket.h"
#include "MakePacket.hpp"

int main(int argc, char* argv[]) {
	Socket socks("182.254.219.134", 8002);
	socks.socketConnect();
	char buf[BUFSIZE];
	strcpy(buf, argv[1]);
	memset(buf, 0, sizeof buf);
	socks.socketRead(buf);
	printf("%s\n", buf);

	return 0;
}
