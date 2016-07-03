
CFLAGS=-ansi -Wall -std=c++11 -c -g

all: gossip

gossip: gossip.h cliente.o servidor.o
	g++ -g main.cpp cliente.o servidor.o -o gossip.out

#main.o: gossip.h main.cpp
#    g++ $(CFLAGS) main.cpp -lstdc++

cliente.o: cliente.cpp
	g++ $(CFLAGS) cliente.cpp

servidor.o: gossip.h servidor.cpp
	g++ $(CFLAGS) servidor.cpp

clean:
	rm -f *.out
	rm -f *.o   
