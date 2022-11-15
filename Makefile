CXXFLAGS = -g -O -std=c++14 -Wall
LDFLAGS = -g
OBJS    = service.o client.o main.o

all:    demo

demo:   $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

clean:
	rm -f demo *.o
###
client.o: client.cpp service_interface.h client_interface.h
main.o: main.cpp client_interface.h
service.o: service.cpp service_interface.h client_interface.h
