/*********************************************************
 * Author           : none
 * Last modified    : 2017-04-19 21:09
 * Filename         : Socket.cc
 * Description      : 
 *********************************************************/

#include "Socket.h"
#include <fcntl.h>

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
	//int flags = fcntl(socket_fd, F_GETFL, 0);
	//fcntl(socket_fd, F_SETFL, flags&~O_NONBLOCK);    //设置成阻塞模式；
	if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof server_addr) == -1) {
		//printf("connect error:%s\n", strerror(errno));
		printf("connect failed!\n");
		return false;
	} else {
		printf("connect success! socket_fd=%d\n", socket_fd);
		return true;
	}	
}

bool Socket::socketRead(dataBuf buf) {
	int ret = read(socket_fd, buf, BUFSIZE);
	printf("socket_fd=%d ret=%d\n", socket_fd, ret);
	if (ret <= 0) {			// 连接异常
		return false;	
	}
	return true;
}

bool Socket::socketWrite(dataBuf buf) {
	int ret = write(socket_fd, buf, BUFSIZE);
	if (ret < 0) {			// 连接异常
		return false;
	}
	return true;
}

void Socket::closeFd() {
	close(socket_fd);
}
