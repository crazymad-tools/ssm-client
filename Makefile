ssm_client:main.o Socket.o
	g++ -o ssm_client main.o Socket.o -pthread 
Socket.o:Socket.cc def.h
	g++ -c Socket.cc 
main.o:main.cc def.h MakePacket.hpp Loop.hpp Operation.hpp
	g++ -c main.cc
clean:
	rm main.o Socket.o
