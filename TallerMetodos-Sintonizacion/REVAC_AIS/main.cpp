#include "includes.h"
#include "globales.h"

void leer_archivo_configuracion(void)
{
  FILE *archivo;
  archivo = fopen(archivo_configuracion, "r");
  fscanf(archivo, "%d", &cantidad_parametros);
  cout<<cantidad_parametros<<endl;

  if(cantidad_parametros < 0){
    printf("Invalida cantidad de parametros");
    fclose(archivo);
    exit(1);
  }
  configuracion_parametros = new( struct configuracion [cantidad_parametros] );
  
  for(int i=0; i< cantidad_parametros; i++){
    fscanf(archivo, "%s", configuracion_parametros[i].nombre);
    printf("nombre leido: %s\n", configuracion_parametros[i].nombre);
    fscanf(archivo, "%d", &configuracion_parametros[i].limite_minimo);
    printf("lim_min: %d\n", configuracion_parametros[i].limite_minimo);
    fscanf(archivo, "%d", &configuracion_parametros[i].limite_maximo);
    printf("lim_max: %d\n", configuracion_parametros[i].limite_maximo);
    fscanf(archivo, "%d", &configuracion_parametros[i].decimales);
    printf("decimales: %d\n", configuracion_parametros[i].decimales);
  }
  fclose(archivo);
  
  valores_parametros=new(int *[cantidad_parametros]);
  for(int i=0; i<cantidad_parametros; i++)
    valores_parametros[i]=new(int[N]);
  
  return;
}

int int_rand (int a, int b)
{ 
  //drand48() devuelve valores en el intervalo [0.0, 1.0)
  int retorno = 0;
  
  if (a < b)
    {
      retorno = (int) ((b - a) * drand48 ());
      retorno = retorno + a;
    }
  else
    {
      retorno = (int) ((a - b) * drand48 ());
      retorno = retorno + b;
    }
  
  return retorno;
}

void mostrar_calibraciones(void)
{
  cout<<"-----------------------Calibraciones-------------------------"<<endl;
  for (vector < calibracion >::iterator c = conjunto_calibraciones.begin (); c != conjunto_calibraciones.end (); c++){
    for(int i=0; i<cantidad_parametros; i++)
      {
	cout<<c->parametro[i]<<" : ";
      }
    cout<<" :: ";
    cout<<c->aptitud_promedio<<" :: ";
    cout<<c->nacimiento;
    cout<<endl;
  }
  return;
}

void calcular_aptitud_calibracion(calibracion *cal_temp)
{
  float f = 0.00;
  ifstream resultados;
  FILE * sh;
  
  char archivo_resultados[1000];
  char archivo_sh[1000];
//  strcpy (archivo_resultados, "resultados-");
//  strcat (archivo_resultados, directorio);
//  strcat (archivo_resultados, ".res");
  strcpy(archivo_resultados, "resultados-instancias.res");

  strcpy (archivo_sh, "ejecutar-");
  strcat (archivo_sh, directorio);
  strcat (archivo_sh, ".sh");

  char comando[256];
  char comando2[256];
  int numero_mediciones;
  float aptitud;
  float suma_aptitud;

  for(int i=0; i< cantidad_parametros; i++)
    {
      cout<<cal_temp->parametro[i]<<" ";
    }
  fflush(stdout);
  sprintf(comando, "rm -rf %s", archivo_resultados);
  system(comando);
     
  int semilla = int_rand(0, 100);
 
  sprintf(comando, "sh %s %s %s %d", ejecutable, directorio, archivo_resultados, semilla);

  for(int i=0; i< cantidad_parametros; i++)
    { 
      sprintf(comando2," -%s %.1f", configuracion_parametros[i].nombre, ((cal_temp->parametro[i]/((float)configuracion_parametros[i].decimales))));
  //	  printf(" -%s %f", configuracion_parametros[i].nombre, cal_temp->parametro[i]);
      strcat(comando, comando2);
      //printf("%s", comando);
      //getchar();
    }
   
  system(comando);
  resultados.open(archivo_resultados);
  numero_mediciones=0;
  suma_aptitud=0.00;
  //printf("%s\n ", archivo_resultados);
  //getchar();
  while(resultados)
    {
      resultados>>aptitud;
      //cout<<aptitud<<endl;
      suma_aptitud += aptitud;
      numero_mediciones++;
    }
  
  resultados.close();
  f=suma_aptitud/((float) numero_mediciones);
  printf("Aptitud: %.2f\n\n",f);
  (cal_temp->aptitud_promedio) = f;
  return;
}

void rangos(int *v_min, int *v_max, int pos, int par)
{
  if((pos + H) > (N - 1))
    { //H hacia atras
      *v_max = valores_parametros[par][N - 1];
    }
  else
    {
      *v_max = valores_parametros[par][pos + H];
    }
  
  if((pos - H) < 0)
    { //H hacia adelante
      *v_min = valores_parametros[par][0];
    }
  else
    {
      *v_min = valores_parametros[par][pos - H];
    } 
  return;
}

int seleccionar_valor_parametro(int parametro)
{
  int valor_parametro;
  int valor_minimo, valor_maximo;
  int pos = int_rand(0, N); //entre 0 y N-1
  
  rangos(&valor_minimo, &valor_maximo, pos, parametro);
  valor_parametro = int_rand(valor_minimo, (valor_maximo+1));
  return valor_parametro;
}

void agregar_calibracion_cruzada_y_mutada(int nacimiento)
{
  calibracion calibracion_temp;
  calibracion_temp.parametro = new (int[cantidad_parametros]);
  
  for(int i = 0; i< cantidad_parametros; i++)
    {
      calibracion_temp.parametro[i] = seleccionar_valor_parametro(i);
    }
  calibracion_temp.nacimiento = nacimiento;
  calcular_aptitud_calibracion(&calibracion_temp);
  conjunto_calibraciones.push_back(calibracion_temp);
  return;
}

void crear_conjunto_calibraciones_inicial(int tamano)
{
  int nacimiento = 0;
  for(int i=0; i < tamano; i++)
    {
      calibracion calibracion_temp;
      calibracion_temp.parametro = new (int[cantidad_parametros]);
      cout<<"(calibracion "<<i<<") ";
      for(int i = 0; i< cantidad_parametros; i++)
	{
	  calibracion_temp.parametro[i] = int_rand(configuracion_parametros[i].limite_minimo, (configuracion_parametros[i].limite_maximo+1));//Incluyendo el valor de limite maximo
	  cout<<calibracion_temp.parametro[i]<< " ";
	}
      cout<<endl;
      calibracion_temp.nacimiento = nacimiento;
      calcular_aptitud_calibracion(&calibracion_temp);
      //Se agrega al conjunto de calibraciones
      conjunto_calibraciones.push_back(calibracion_temp);
    }
  return;
}

float entropia_parametro_en_conjunto_calibraciones(int parametro)
{
  float entropia = 0;
  float proporcion;
  bool encontrado;
  valores temp;
  list<valores> valores_presentes;

  for (vector < calibracion >::iterator c = conjunto_calibraciones.begin (); c != conjunto_calibraciones.end (); c++)
    {
      encontrado = false;
      for (list < valores >::iterator s = valores_presentes.begin (); s != valores_presentes.end (); s++)
	{
	  if((c->parametro[parametro]) == (s->valor)){
	    encontrado = true;
	    s->frecuencia++;
	  }
	}
      if(!encontrado)
	{
	  temp.frecuencia = 1;
	  temp.valor = c->parametro[parametro];
	  valores_presentes.push_back(temp);
	}
    }
  
  int total = 0;
  
  for (list < valores >::iterator s = valores_presentes.begin (); s != valores_presentes.end (); s++)
    {
      proporcion = (s->frecuencia / ((float)conjunto_calibraciones.size()));
      entropia += proporcion*log(1.00/proporcion);
      //Revision
    }
  valores_presentes.clear();
  return entropia;
}

void calcular_K(void){
  int menor, mayor;
  bool todo_igual=true;
  cout<<"Parametro  |    H0    |    K    |   Rango   | Rango Inicial | "<<endl;
  for(int i=0; i<cantidad_parametros; i++)
    {
      menor = valores_parametros[i][0];
      mayor = valores_parametros[i][N-1]; // OJO solo esta considerando los 50!(N) mejores individuos 
      if (menor != mayor)
	todo_igual = false;
      
      K[i] = entropia_parametro_en_conjunto_calibraciones(i);
      cout<< i << "     " <<H0[i]<<"     "<<K[i]<<"    [ "<<menor<<" : "<<mayor<<"]"<<"    [ "<<configuracion_parametros[i].limite_minimo<<" : "<<configuracion_parametros[i].limite_maximo<<"]"<<endl;
    }
  cout<<endl;
  
  //Condicion de convergencia
  if(todo_igual){
    I = MAX_ITER; //Esto se acabo
  }  
  return;
}

void eliminar_individuo_mas_viejo(void)
{
  //En ambos ciclos la busqueda no debe incluir al mejor individuo, de forma que no sea eliminado
  int menor = I;
  calibracion *m;
  
  for (vector < calibracion >::iterator c = (conjunto_calibraciones.begin () + 1 ); c != conjunto_calibraciones.end (); c++)
    {
      if(c->nacimiento <= menor)
	{
	  menor = c->nacimiento;
	}
    }
  
  for (vector < calibracion >::iterator c = (conjunto_calibraciones.end () - 1); c != (conjunto_calibraciones.begin ()); c--)
    {
      if(c->nacimiento == menor)
	{
	  conjunto_calibraciones.erase(c);
	  return;
	}
    }
  
  return;
}

void guardar_optimo(void)
{
  optimo = conjunto_calibraciones.front();
  for (vector < calibracion >::iterator c = conjunto_calibraciones.begin (); c != conjunto_calibraciones.end (); c++){
    conjunto_calibraciones.erase(c);
    return;
  }
}

void generar_y_ordenar_matriz_valores_parametros(int Total, int **matriz_valores)
{
  int contador = 0;
  
  //Recojo los valores que tienen los parametros de los N  mejores individuos
  for (vector < calibracion >::iterator c = conjunto_calibraciones.begin (); c != conjunto_calibraciones.end (); c++)
    {
      if(contador == Total)
	{
	  break;
	}
      for(int i = 0; i<cantidad_parametros; i++)
      {
	matriz_valores[i][contador] = c->parametro[i];
      }
      contador++;
    }
  
 //Mostrar listado
//  cout<<endl;
//  for(int i=0; i<cantidad_parametros; i++)
//  {
// 	cout<<"i: "<<i<<"-";
//  	for(int j=0; j<(Total); j++)
// 		cout<<matriz_valores[i][j]<<" ";
// 	cout<<endl;
//  } 

  int aux;
  for(int i = 0; i < cantidad_parametros; i++)
    {
      for(int j=0; j < (Total-1); j++)
	{
	  for(int k = (j+1); k < Total ; k++)
	    {
	      if(matriz_valores[i][j] >  matriz_valores[i][k])
		{
		  aux = matriz_valores[i][j];
		  matriz_valores[i][j] = matriz_valores[i][k];
		  matriz_valores[i][k] = aux;
		}
	    }
	}    
    }
 //Mostrar listado
//  cout<<endl;
//  for(int i=0; i<cantidad_parametros; i++)
//  {
// 	cout<<"i: "<<i<<"-";
//  	for(int j=0; j<(Total); j++)
// 		cout<<matriz_valores[i][j]<<" ";
// 	cout<<endl;
//  } 
  return;
}

void transformar_calibracion(int cantidad)
{
  sort(conjunto_calibraciones.begin(), conjunto_calibraciones.end());
  for(int i=0; i <cantidad; i++)
    {
      eliminar_individuo_mas_viejo();
    }
  /*************************************************************/
  //mostrar_calibraciones();
  generar_y_ordenar_matriz_valores_parametros(N, valores_parametros);
  /*************************************************************/
  for(int i=0; i <cantidad; i++)
    {
      cout<<"(calibracion "<<i<<") ";
      agregar_calibracion_cruzada_y_mutada(I);
    }
  return;
}

void calcular_H0(void){
  for(int i = 0; i< cantidad_parametros; i++){
    H0[i] = entropia_parametro_en_conjunto_calibraciones(i);
    cout<<H0[i]<<" ";
  }
  cout<<endl;
  return;
}

void mostrar_resumen_final(void){
  char conv[100];
  //strcpy(conv, "convergencia-");
  //strcat(conv, directorio);
  //strcat(conv, ".conv");
  strcpy(conv, "convergencia-instancias.conv");
  cout << conv << endl;
  FILE * file_conv;
  if(I==0)//Reiniciar el archivo
    {
      file_conv = fopen(conv, "w");
      fclose(file_conv);
    }
  file_conv = fopen(conv, "a");
  int **valores_parametros_finales;
  valores_parametros_finales=new(int *[cantidad_parametros]);
  for(int i=0; i<cantidad_parametros; i++)
      valores_parametros_finales[i]=new(int[N]);
  
  generar_y_ordenar_matriz_valores_parametros(N, valores_parametros_finales);
  cout<<"------------------------------------------------------------------------"<<endl;
  cout<<"---------------------------- RESUMEN FINAL -----------------------------"<<endl;
  cout<<"------------------------------------------------------------------------"<<endl;
  fprintf(file_conv, "%d ", I);
  for(int i=0; i< cantidad_parametros; i++)
    {
      printf("\t\t%s \t\t%d \t\t[%d .. %d]\n", configuracion_parametros[i].nombre, valores_parametros_finales[i][(int)(5*N/10)], valores_parametros_finales[i][(int)(25*N/100)], valores_parametros_finales[i][(int)(75*N/100)]);
      fprintf(file_conv, "%.2f ",(valores_parametros_finales[i][(int)(5*N/10)]/(float)configuracion_parametros[i].decimales));
    }

  fprintf(file_conv, "\n");
  fclose(file_conv);
  cout<<"------------------------------------------------------------------------"<<endl;
  cout<<"------------------------------------------------------------------------"<<endl;
  return;
}


int main (int argc, char *argv[])
{
  ejecutable = argv[1];
  archivo_configuracion = argv[2];
  directorio = argv[3];
  srand48 (atoi(argv[4]));
  
  cout<<"------------------------------------------------------------------------"<<endl;
  cout<<"---------------------------- INICIALIZACION ----------------------------"<<endl;
  cout<<"------------------------------------------------------------------------"<<endl;
  
  leer_archivo_configuracion();
  optimo.parametro = new (int[cantidad_parametros]);
  H0 = new (float[cantidad_parametros]);
  K = new (float[cantidad_parametros]);
  
  cout<<"------------------------------------------------------------------------"<<endl;
  cout<<"-------------------- CREACION CONJUNTO INICIAL -------------------------"<<endl;
  cout<<"------------------------------------------------------------------------"<<endl;
  crear_conjunto_calibraciones_inicial(M);
  
  cout<<"------------------------------------------------------------------------"<<endl;
  cout<<"------------------------ CALCULANDO H0 ---------------------------------"<<endl;
  cout<<"------------------------------------------------------------------------"<<endl;
  calcular_H0();
  for(I = 0; I < MAX_ITER; I++)
    {
      cout<<"------------------------------------------------------------------------"<<endl;
      cout<<"----------------- ITERACION : "<< I <<" -------------------------------------"<<endl;
      cout<<"------------------------------------------------------------------------"<<endl;
      cout<<"-----------------AGREGANDO NUEVAS CALiBRACIONES ------------------------"<<endl;
      cout<<"------------------------------------------------------------------------"<<endl;
      transformar_calibracion(1);
      cout<<"------------------------------------------------------------------------"<<endl;
      cout<<"----------------------------CALCULANDO K -------------------------------"<<endl;
      cout<<"------------------------------------------------------------------------"<<endl;
      calcular_K();
      sort(conjunto_calibraciones.begin(), conjunto_calibraciones.end());
      mostrar_calibraciones();
	  cout << "resumen" << endl;
      mostrar_resumen_final();
	  cout << "fin resumen" << endl;
    }
  sort(conjunto_calibraciones.begin(), conjunto_calibraciones.end());
  mostrar_calibraciones();
  mostrar_resumen_final();
  return 0;
}
