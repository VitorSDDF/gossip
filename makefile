all: gossip

gossip: main.o cliente.o servidor.o \
    gcc main.o cliente.o servidor.o -o gossip

main.o: main.cpp \
    gcc -c main.cpp -lstdc++

cliente.o: cliente.cpp \
    gcc -c cliente.cpp

servidor.o: servidor.cpp \
    gcc -c servidor.cpp

clean:  \
    rm *o gossip 
