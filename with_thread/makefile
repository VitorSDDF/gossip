
CFLAGS=-ansi -Wall -std=c++11 -c -g

all: gossip

gossip: utils.h cliente.o servidor.o
	g++ -g main.cpp cliente.o servidor.o -o gossip.out -pthread

cliente.o: utils.h cliente.cpp
	g++ $(CFLAGS) cliente.cpp -pthread

servidor.o: utils.h servidor.cpp
	g++ $(CFLAGS) servidor.cpp -pthread

clean:
	rm -f *.out
	rm -f *.o   
