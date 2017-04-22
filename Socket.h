#ifndef _SOCKET_H
#define _SOCKET_H
	
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "def.h"

class Socket {
public:
	Socket(char address_[265], int port_);
	~Socket();
	bool init();			// initialization socket 
	bool socketRead(char buf[BUFSIZE]);
	bool socketWrite(char buf[BUFSIZE]);
	bool socketConnect();


private:
	struct sockaddr_in server_addr;		// server's address info
	int socket_fd;
	char server_address[256];
	int server_port;

};


#endif

