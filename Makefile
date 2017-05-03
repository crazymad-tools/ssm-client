ssm_client:main.o Socket.o
	g++ -o ssm_client main.o Socket.o -pthread -lbcm2835
Socket.o:Socket.cc def.h
	g++ -c Socket.cc 
main.o:main.cc def.h MakePacket.hpp Loop.hpp Operation.hpp
	g++ -c main.cc
clean:
	rm main.o Socket.o
