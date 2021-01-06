CXXFLAGS = -g -O -std=c++14 -Wall
LDFLAGS = -g
OBJS    = service.o client.o

all:    demo

demo:   $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

clean:
	rm -f demo *.o
