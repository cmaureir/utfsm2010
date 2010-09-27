#include "gpu-map.hpp"
#include <cuda_runtime_api.h>
#include <math.h>
#include <stdio.h>


// El kernel d_f implementa la función f aplicadas a un valor x cualquiera.
// Este kernel está declarado con el calificador __device__,
// por lo que sólo puede ser llamado por código que está siendo ejecutado
// en la GPU.

__device__ float d_f(float x, int M) {
    float s = 0.0;
    // 10000
    for (int k = 1; k <= M; ++k) {
        s += sinf(2 * float(M_PI) * k * x);
    }
    return s;
}

// El kernel map_f se encarga de que cada hebra
// ejecute la función d_f con el argumento apropiado.

__global__ void map_f(float x[], int M) {
    unsigned i = threadIdx.x + blockIdx.x * blockDim.x;
    x[i] = d_f(x[i],M);
}

// gpu_map debe hacer toda la burocracia de ejecutar código en la GPU:
// reserva memoria, copia el arreglo, lanza el kernel,
// copia el resultado de vuelta y libera la memoria.

void gpu_map(float x[], unsigned n, int M) {

    int threadsPerBlock = 256;
    int blocksPerGrid = n/threadsPerBlock;

    // Variables para manejar los eventos de inicio y fin    
    cudaEvent_t start, stop;

    // Nueva variable para el tiempo en la GPU
    float gpuTime;

    // Nueva variable para el calculo en la GPU
    float *d;

    // Reserva de memoria en GPU
    cudaMalloc( (void**) &d, n*sizeof(float));

    // Copiar el arreglo a la memoria de la GPU
    cudaMemcpy(d, x, n*sizeof(float), cudaMemcpyHostToDevice);

    // Cramos los dos eventos de inicio y fin de procesamiento
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    // Establecemos el inicio del procesamiento
    cudaEventRecord(start, 0); 

    // Llamada del kernel
    map_f<<<blocksPerGrid, threadsPerBlock>>> (d,M);

    // Sincronizamos las hebras una vez que termine el llamado del kernel
    cudaThreadSynchronize();

    // Establecemos el fin del procesamiento
    cudaEventRecord(stop, 0);
    
    // Sincronizamos la detencion del proceso
    cudaEventSynchronize(stop);

    // Obtenemos el tiempo que demoró el proceso en milisegundos
    cudaEventElapsedTime(&gpuTime, start, stop);

    // Eliminamos ambos eventos
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    // Copiar resultado de vuelta
    cudaMemcpy(x,d, n * sizeof(float), cudaMemcpyDeviceToHost);

    // Liberación de memoria
    cudaFree(d);

	// Comentar para tests
    printf("Tiempo GPU: %f\n",gpuTime/1000);
	
	// Descomentar para tests
    // printf("%f ",gpuTime/1000);

}

