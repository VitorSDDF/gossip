CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=main.cpp cliente.cpp servidor.cpp gossip.h
OBJS=$(subst .cpp,.o,$(SRCS))

all: gossip

gossip: $(OBJS)
    $(CXX) $(LDFLAGS) -o gossip $(OBJS) $(LDLIBS) 

cliente.o: cliente.cpp gossip.h

servidor.o: servidor.cpp gossip.h

clean:
    $(RM) $(OBJS)

dist-clean: clean
    $(RM) gossip
