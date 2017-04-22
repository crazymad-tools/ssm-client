/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-19 21:09
 * Filename         : Socket.cc
 * Description      : 
 *********************************************************/

#include "Socket.h"

Socket::Socket(char address_[256], int port_) 
	: server_port(port_) 
{
	strcpy(server_address, address_);
}

Socket::~Socket() {
	::close(socket_fd);		// close the file descriptor
}

bool Socket::socketConnect() {
	printf("connect...\n");
	int on;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	//assert(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on) != -1);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port);
	server_addr.sin_addr.s_addr = inet_addr(server_address);
	if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof server_addr) == -1) {
		perror("connect");
		return false;
	} else {
		return true;
	}	
}

bool Socket::socketRead(dataBuf buf) {
	::read(socket_fd, buf, BUFSIZE);
	return true;
}

bool Socket::socketWrite(dataBuf buf) {
	::write(socket_fd, buf, BUFSIZE);
	return true;
}
