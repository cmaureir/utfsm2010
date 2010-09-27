NVCC = nvcc
CC = g++
CXXFLAGS = -Wall $(INCLUDEFLAGS) -fopenmp

ifeq ($(shell hostname -s),gp01)
    CUDA = /opt/cuda
else
    # modificar a gusto
    CUDA = /usr/local/cuda
endif
CUDAHEADERS = $(CUDA)/include
INCLUDEFLAGS = -I $(CUDAHEADERS)
LDFLAGS += -L$(CUDA)/lib64 -L$(CUDA)/lib
LDFLAGS += -lm -lgomp -lcudart

TARGETS = main

all: $(TARGETS)
main: main.o cpu-map.o gpu-map.o
main.o: main.cpp cpu-map.hpp gpu-map.hpp
cpu-map.o: cpu-map.cpp cpu-map.hpp
gpu-map.o: gpu-map.cu gpu-map.hpp
	$(NVCC) $(INCLUDEFLAGS) $< -c -o $@

clean:
	rm -f *.o $(TARGETS)

.PHONY: all clean
