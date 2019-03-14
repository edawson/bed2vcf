CXX=g++
CXXFLAGS=-O3 -g
LD_INC_FLAGS=-I./libvcfh -I./tinyfa -I./tinyfa/pliib
LD_LIB_FLAGS= -L./libvcfh -lvcfh

bed2vcf: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LD_INC_FLAGS) $(LD_LIB_FLAGS)
