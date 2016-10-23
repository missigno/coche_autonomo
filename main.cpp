#include "mainwindow.h"
#include <QApplication>


#include "screen_t.hpp"
#include "common.hpp"


//#define ScreenWidth 800
//#define ScreenHeight 600

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  a.exec();
  if(undefined)
  {
    std::clog<<"Cerrando el programa."<<std::endl;
    exit(EXIT_SUCCESS);
  }
  //calcular_escalado();
  switch(Opcion)
  {
    case OpcionManual:
      std::clog<<"Opción Manual activada."<<std::endl;
      break;
    case OpcionAleatoria:
      std::clog<<"Opción Aleatoria activada, porcentaje: "<<Porcentaje<<std::endl;
      break;
    case OpcionFichero:
      std::clog<<"Opción Fichero activada, fichero de entrada: "<<nombre_fichero_entrada<<std::endl;
      break;
    default:
      std::cerr<<"ERROR: opción no reconocida."<<std::endl;
      exit(EXIT_FAILURE);
      break;
  }
  if(Salida)
    std::clog<<"Opción Salida activada, fichero de salida: "<<nombre_fichero_salida<<std::endl;
  else
    std::clog<<"Opción Salida desactivada."<<std::endl;

  screen_t screen;
  screen.run();
    //return a.exec();
}
