#ifndef COMMON_HPP
#define COMMON_HPP

////Medidas
#define ScreenWidth 1901
#define ScreenHeight 1000
#define LastXPixel 1900
#define LastYPixel 1000
////Tipos de Celda
#define CeldaLibre 0
#define CeldaObstaculo 1
#define CeldaInicial 2
#define CeldaFinal 3
#define CeldaParada 4
#define CeldaLibreVisitada 5
#define CeldaParadaVisitada 6
////Colores
#define ColorCeldaLibre al_map_rgb(0,0,0)               //negro fin
#define ColorCeldaObstaculo al_map_rgb(255,255,0)       //amarillo fin
#define ColorCeldaInicial al_map_rgb(75,0,130)          //violeta fin
#define ColorCeldaFinal al_map_rgb(255,255,255)         //blanco fin
#define ColorCeldaParada al_map_rgb(255,0,0)            //rojo  fin
#define ColorCeldaLibreVisitada al_map_rgb(255,0,255)   //magenta fin
#define ColorCeldaParadaVisitada al_map_rgb(36,231,17)  //verde fin
#define ColorCoche al_map_rgb(0,255,255)                //azul fin
////Opciones
#define OpcionManual 0
#define OpcionAleatoria 1
#define OpcionFichero 2
////////////////////////TEMPORALES PARA MOVIMIENTOS CON EL TECLADO
#define MovimientoArriba 0
#define MovimientoAbajo 1
#define MovimientoDerecha 2
#define MovimientoIzquierda 3
////////////////////////
//Librerias
#include <string>
#include <iostream>


extern const double FPS;

typedef unsigned short int my_size_t;

extern bool undefined;

extern my_size_t Opcion;
extern bool Salida;

extern std::string nombre_fichero_entrada;
extern std::string nombre_fichero_salida;
extern double Porcentaje;
extern my_size_t numero_paradas;

extern my_size_t Filas;
extern my_size_t Columnas;

extern my_size_t EscaladoPixelsX;
extern my_size_t EscaladoPixelsY;


void calcular_escalado(void);

struct point_t
{
  my_size_t x;
  my_size_t y;
};

#endif // COMMON_HPP
