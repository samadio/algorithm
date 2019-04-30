CXX = gcc
CXXFLAGS =-I include
CHAIN= source/*.c
all: chain.x

chain.x: ${CHAIN}
	$(CXX) $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf *.x */*~ *~

.PHONY: clean all


