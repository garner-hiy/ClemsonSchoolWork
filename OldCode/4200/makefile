
CXX = g++
CXXFLAGS = -std=c++11

all: HW1

HW1: HW1code_AJ_Garner.o
	$(CXX) $(CXXFLAGS) -o HW1 HW1code_AJ_Garner.o

HW1code_AJ_Garner.o: HW1code_AJ_Garner.cpp
	$(CXX) $(CXXFLAGS) -c HW1code_AJ_Garner.cpp

clean:
	rm -f *.o HW1 

run: HW1
	./HW1

.PHONY: all clean run