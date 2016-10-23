#include "common.hpp"

const double FPS=10.0;


bool undefined=1;

my_size_t Opcion;
bool Salida=0;

std::string nombre_fichero_entrada;
std::string nombre_fichero_salida;
double Porcentaje;
my_size_t numero_paradas;

my_size_t Filas=1;
my_size_t Columnas=1;

my_size_t EscaladoPixelsX=10;
my_size_t EscaladoPixelsY=10;

void calcular_escalado(void)
{
  EscaladoPixelsX=LastXPixel/Columnas;
  EscaladoPixelsY=LastYPixel/Filas;
/*
  my_size_t aux=LastXPixel;
  EscaladoPixelsX=aux/Columnas;
  aux=LastYPixel;
  EscaladoPixelsY=aux/Filas;
  */
}
//  /home/missigno/coche_autonomo/map.txt
