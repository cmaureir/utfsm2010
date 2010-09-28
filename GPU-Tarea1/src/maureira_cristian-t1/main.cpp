#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "cpu-map.hpp"
#include "gpu-map.hpp"

// (1 << n) == (2 elevado a n)
static const unsigned N = 1 << 16;
static const char *data_file_name = "/home/utfsm/rbonvall/data_2^26";
int M = 10000;

int main(int argc, char *argv[]) {

    // Paso por parametro del valor de M
    if(argc > 1){
		M = atoi(argv[1]);
    }



    // Los vectores en C++ son escencialmente arreglos en C con una interfaz
    // más conveniente. Donde sea que se pueda usar arreglos, se puede usar
    // vectores. Cuando se necesita la dirección de memoria de un arreglo, hay
    // que usar la dirección del primer elemento del vector: &x[0].  x por sí
    // solo no sirve ya que es un objeto que encapsula al verdadero arreglo.

    std::vector<float> x1;
    x1.reserve(N);
    x1.resize(N);

    // copiar datos del archivo de entrada al vector
    std::ifstream input_file(data_file_name, std::ios::binary | std::ios::in);
    if (!input_file) {
        std::cerr << "No se pudo abrir el archivo " << data_file_name << std::endl;
        std::exit(-1);
    }
    input_file.read((char *) &x1[0], N * sizeof(float));
    input_file.close();

    // crear una copia del vector, de modo de tener
    // uno para mapear en la GPU y otro en la CPU
    std::vector<float> x2(x1);
    // mapear x1 en la CPU y x2 en la GPU
    cpu_map(x1, M);
    gpu_map(&x2[0], x2.size(), M);

    // verificar que los resultados son prácticamente iguales
    float squared_diff_norm = 0.0;
#   define SQUARED(x) ((x) * (x))
#   pragma omp parallel reduction(+: squared_diff_norm)
    for (unsigned i = 0; i < N; ++i)
        squared_diff_norm += SQUARED(x1[i] - x2[i]);
	// Comentar para tests
    std::cout << "Norma de la diferencia: " << std::sqrt(squared_diff_norm) << std::endl;

	// Descomentar para tests
    //std::cout << std::sqrt(squared_diff_norm) << std::endl;
}

