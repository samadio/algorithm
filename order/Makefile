CXX = gcc
CXXFLAGS =-lm -I include
SRC= source/cases.c source/build_heap.c source/sorting.c source/sorting_no_comparison.c source/utils.c
LIN= source/build_heap.c source/linear_main.c source/sorting_no_comparison.c source/utils.c
NONLIN= source/sorting.c source/utils.c source/nonlinear_main.c source/build_heap.c
all: cases.x linear.x nonlinear.x

cases.x: ${SRC}
	$(CXX) $^ -o $@ $(CXXFLAGS)

linear.x: ${LIN}
	$(CXX) $^ -o $@ $(CXXFLAGS)
	
nonlinear.x: ${NONLIN}
	$(CXX) $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf *.x */*~ *~

.PHONY: clean all


