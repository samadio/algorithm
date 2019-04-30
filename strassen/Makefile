CXX = gcc
CXXFLAGS =-I include
OLD= source/main.c  source/matrix.c source/strassen.c
NEW= source/main.c  source/matrix.c source/new_strassen.c
all: old_strassen.x new_strassen.x

old_strassen.x: ${OLD}
	$(CXX) $^ -o $@ $(CXXFLAGS)

new_strassen.x: ${NEW}
	$(CXX) $^ -o $@ $(CXXFLAGS)

clean:
	rm -rf *.x */*~ *~

.PHONY: clean all


