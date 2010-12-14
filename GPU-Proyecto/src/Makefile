NVCC = nvcc
CC = g++
CUFLAGS = -G #--device-emulation
CXXFLAGS = -Wall -lm -lrt

# si trabaja en otro computador,
# cambie esto al directorio donde tenga instalado CUDA
CUDA = /opt/cuda

CUDAHEADERS = $(CUDA)/include
INCLUDEFLAGS = -I $(CUDAHEADERS)
LDFLAGS += -L$(CUDA)/lib64 -L$(CUDA)/lib  # quitar el primero en arq. 32 bits
LDFLAGS += -lm -lgomp -lcudart

all: matrix-mult matrix-mult-cpu

matrix-mult: matrix-mult.cu
	$(NVCC) $(CUFLAGS) $(INCLUDEFLAGS) $< -o $@

matrix-mult-cpu: matrix-mult.cpp
	$(CC) $(CXXFLAGS) $< -o $@

clean:
	rm matrix-mult matrix-mult-cpu
.PHONY: all clean
