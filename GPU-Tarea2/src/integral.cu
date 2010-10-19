#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <cuda_runtime_api.h>

#define SQ(x) ((x) * (x))

static const float A = -4.0, B = 4.0;  // limites de integración
static const int N = 1 << 22;          // número de intervalos = 2^22
static const float H = (B - A) / N;    // tamaño del intervalo de integración
static const float PI(M_PI);           // π con precision simple

__device__ float h(float x) {
    return .5f + 1.5f / (1.0f + 50.0f * SQ(x));
}

float host_h(float x) {
    return .5f + 1.5f / (1.0f + 50.0f * SQ(x));
}

__device__ float f(float x) {
    int i;
    float sum = 0.0f, x0;
    for (i = 0; i < 10; ++i){
        x0 = -3.3f + i * 0.7f;
        sum += h(x - x0);
    }
    return sum/10.0f;
}

float host_f(float x) {
    int i;
    float sum = 0.0f, x0;
    for (i = 0; i < 10; ++i){
        x0 = -3.3f + i * 0.7f;
        sum += host_h(x - x0);
   }
    return sum/10.0f;
}

__device__ float g(float x) {
    float c = cosf(2.0f * PI * f(x) * x);
    return expf(-x/16.0f) * SQ(c);
}


float host_g(float x) {
    float c = cosf(2.0f * PI * host_f(x) * x);
    return expf(-x/16.0f) * SQ(c);
}

__global__ void
integrate_blocks(float subtotals[]) {

	// Inicializar variable __shared__ 
	extern __shared__ float partialValues[];

	int i = threadIdx.x + blockIdx.x * blockDim.x;
	int tx = threadIdx.x;

	// Cada thread según su id, calcula la función de g(x)
	float x = 0; 

	// Realizamos el cálcul
	x = A + i * (H / 2);
	partialValues[tx] += (i % 2 == 0 ? 4 : 2) * g(x);


	 // Sincronizamos las hebras una vez que termine
	__syncthreads(); 

	// Hacer una suma por reduccion con los valores del arreglo subtotals[]
	for (int offset = blockDim.x/2; offset > 0; offset >>=1){
	        if (tx < offset)
	        {
	            //Añadimos una suma parcial con el offset
	            partialValues[tx] += partialValues[tx+offset];
	        }
	        __syncthreads();
	}
        // Escribimos el resultado del primer elemento de nuestro arreglo
        if(tx == 0)
        {
        // Resultados lo guarda por bloques y no por hebras
        subtotals[blockIdx.x] = partialValues[0];
        }
}


int main(int argc, char *argv[]) {

    // El programa recibe como parámetro el número de hebras por bloque.
    // Recuerden que este número debe ser múltiplo de 32 (tamaño del warp)
    // y puede ser a lo más 512 (limitación del hardware).

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " threads_per_block" << std::endl;
        std::exit(1);
    }
    int block_size = std::atoi(argv[1]);

    // Al usar N subintervalos, hay que evaluar la función en 2N + 1 puntos.
    // Para paralelizar, mejor evaluar 2N puntos y sumar el último al final.
    // Por lo tanto, necesitamos 2N hebras.
    int nr_blocks = 2 * N / block_size;

    size_t sharedMem = 512 ;

    // Reservar arreglos en RAM y en la GPU para guardar los resultados.
    float *subtotals_h, *subtotals_d;
    subtotals_h = new float[nr_blocks];
    cudaMalloc((void **) &subtotals_d, sizeof(float) * nr_blocks);

    integrate_blocks<<<nr_blocks, block_size,sharedMem>>>(subtotals_d);

    // En la parte (a) de la tarea,
    // la reducción global la hacemos en la CPU.

    cudaMemcpy(subtotals_h, subtotals_d,
               sizeof(float) * nr_blocks, cudaMemcpyDeviceToHost);

    float sum = 0.0;
#   pragma omp parallel for reduction(+: sum)
    for (int b = 0; b < nr_blocks; ++b) {
        sum += subtotals_h[b];
    }
    
    sum+= host_g(B) + host_g(A);

    float integral = sum * H / 6.0f;

    std::cout << "Integral: " << std::setprecision(5) << integral << std::endl;
    sum = 0.0;
    cudaFree(subtotals_d);
    std::free(subtotals_h);
}

