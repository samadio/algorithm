CXX = gcc
CXXFLAGS =-lm -I ./
SRC= build_heap.c main.c dijkstra.c
all: dijkstra.x

dijkstra.x: ${SRC}
	$(CXX) $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf *.x */*~ *~

.PHONY: clean all


