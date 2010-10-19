#include <iostream>
#include <iomanip>
#include <cmath>

#define SQ(x) ((x) * (x))

static const float A = -4.0, B = 4.0;  // limites de integración
static const int N = 1 << 22;          // número de intervalos = 2^22
static const float H = (B - A) / N;    // tamaño del intervalo de integración
static const float PI(M_PI);           // π con precision simple

float h(float x) {
    return .5f + 1.5f / (1.0f + 50.0f * SQ(x));
}

float f(float x) {
    int i;
    float sum = 0.0f, x0;
    for (i = 0; i < 10; ++i){
        x0 = -3.3f + i * 0.7f;
        sum += h(x - x0);
	}
    return sum/10.0f;
}

float g(float x) {
    float c = std::cos(2.0f * PI * f(x) * x);
    return std::exp(-x/16.0f) * SQ(c);
}

int main() {
    float sum = 0.0;
    float x;

    // Regla de Simpson:
    // se evalúa la función g tanto en los puntos frontera entre los subintervalos como
    // en los puntos medios.
    // * los extremos A y B del dominio se ponderan con factor 1;
    // * los puntos medios de cada subintervalo se ponderan con factor 4;
    // * los puntos frontera entre subintervalos se ponderan con factor 2.
    // El valor aproximado de la integral es
    // H/6 por la suma ponderada de las evaluaciones.

#   pragma omp parallel for private(x) reduction(+: sum)
    for (int i = 1; i < 2 * N; ++i) {
        x = A + i * (H / 2);
        sum += (i % 2 == 0 ? 4 : 2) * g(x);
    }
    sum += g(A) + g(B);
    float integral = sum * H / 6.0f;

    std::cout << std::setprecision(7) << integral << std::endl;

    // La integración está paralelizada usando OpenMP.
    // Haga la prueba de correr el programa paralelo (con el pragma)
    // y serial (sin el pragma) en un computador multicore.
    //
    // ¿Cambia el tiempo de ejecución?
    // ¿Es lineal la mejora (8 cores ⇒ tiempo baja 1/8)?
    // Puede medir el tiempo ejecutando así:  time ./integral-cpu
    //
    // ¿Cambia el resultado de la integral? ¿Por qué?
}
