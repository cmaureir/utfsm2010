
struct configuracion
{
  char nombre[30];
  int limite_minimo, limite_maximo;
  int decimales;
};


struct valores
{
  int frecuencia;
  int valor;
};

class calibracion
{
  public:
  float aptitud_promedio;
  int nacimiento;
  int *parametro;

  bool operator< (const calibracion &a) const
  {
    return(a.aptitud_promedio > aptitud_promedio);
  }
};

/*******************************************************************/
#ifndef externo
vector <calibracion> conjunto_calibraciones;
float *K, *H0;
list <valores> *ruleta_parametro;
int I;
calibracion optimo;
char *archivo_configuracion;
char *directorio;
char * ejecutable;
struct configuracion *configuracion_parametros;
int cantidad_parametros;
int **valores_parametros;
#endif
#ifdef externo
extern vector <calibracion> conjunto_calibraciones;
extern float *K, *H0;
extern list <valores> *ruleta_parametro;
extern int I;
extern calibracion optimo;
extern char *archivo_configuracion;
extern char *directorio;
extern char * ejecutable;
extern struct configuracion *configuracion_parametros;
extern int cantidad_parametros;
int **valores_parametros;
#endif

/*******************************************************************/

