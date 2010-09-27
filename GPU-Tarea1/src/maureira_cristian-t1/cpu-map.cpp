#include "cpu-map.hpp"
#include <cmath>
#include <ctime>
#include <iostream>

float f(float x, int M) {
    float s = 0.0;
    for (int k = 1; k <= M; ++k) {
        s += std::sin(2 * M_PI * k * x);
    }
    return s;
}

void cpu_map(std::vector<float>& x, int M) {

    int n = x.size();
    clock_t start = clock();

    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        x[i] = f(x[i], M);
    }

    /* El ciclo for está paralelizado usando OpenMP.
     *
     * La directiva "#pragma omp parallel for" indica al compilador que las
     * iteraciones del ciclo pueden ejecutarse en paralelo. Para activar la
     * paralelización, hay que compilar con el flag -fopenmp.
     *
     * Por omisión serán creadas tantas hebras como cores haya disponibles.
     * Haga la prueba de ejecutar el ciclo con y sin paralelización, y compare
     * los tiempos de ejecución.
     */

    clock_t end = clock();
    double time = double(end - start) / CLOCKS_PER_SEC;

    // Comentar para tests
	std::cout << "Tiempo CPU: " << time << std::endl;
	
	// Descomentar para tests
    //std::cout <<  time << " ";
}
