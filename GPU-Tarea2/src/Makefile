NVCC = nvcc
CUFLAGS = #--device-emulation
CXXFLAGS = -Wall -lm -fopenmp

# si trabaja en otro computador,
# cambie esto al directorio donde tenga instalado CUDA
CUDA = /opt/cuda

CUDAHEADERS = $(CUDA)/include
INCLUDEFLAGS = -I $(CUDAHEADERS)
LDFLAGS += -L$(CUDA)/lib64 -L$(CUDA)/lib  # quitar el primero en arq. 32 bits
LDFLAGS += -lm -lgomp -lcudart

all: integral integral-cpu

integral-cpu: integral-cpu.cpp

integral: integral.cu
	$(NVCC) $(CUFLAGS) $(INCLUDEFLAGS) $< -o $@

clean:
	rm integral-cpu integral
.PHONY: all clean
