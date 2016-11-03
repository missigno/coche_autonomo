#include "screen_t.hpp"

screen_t::screen_t(void):
  display_(nullptr),
  event_queue_(nullptr),
  timer_(nullptr),
  map_(),
  coche_()
  {
    if(!al_init())  //iniciando allegro 5
    {
      al_show_native_message_box(nullptr, "Coche Autónomo", "Error", "No se ha podido iniciar Allegro 5.",nullptr,ALLEGRO_MESSAGEBOX_ERROR);
      exit(EXIT_FAILURE);
    }
    else
      std::clog<<"Alegro 5 iniciado."<<std::endl;
    display_=al_create_display(ScreenWidth,ScreenHeight); //inicializando la ventana
    if(!display_)
    {
      al_show_native_message_box(nullptr, "Coche Autónomo", "Error", "No se ha podido crear o iniciar el display.", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      exit(EXIT_FAILURE);
    }
    else
      std::clog<<"Display creado e inicializado."<<std::endl;
    al_set_window_title(display_, "Coche Autónomo"); //editando el nombre de la ventana
    al_install_keyboard();  //para detectar acciones de teclado
    if(!al_is_keyboard_installed())
    {
      al_show_native_message_box(nullptr, "Coche Autónomo", "Error", "No se ha podido instalar el teclado.", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      exit(EXIT_FAILURE);
    }
    else
      std::clog<<"Teclado instalado."<<std::endl;
    al_install_mouse(); //para detectar acciones del ratón
    if(!al_is_mouse_installed())
    {
      al_show_native_message_box(nullptr, "Coche Autónomo", "Error", "No se ha podido instalar el ratón.", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      exit(EXIT_FAILURE);
    }
    else
      std::clog<<"Ratón instalado."<<std::endl;
    event_queue_=al_create_event_queue(); //creando cola de eventos
    if(!event_queue_)
    {
      al_show_native_message_box(nullptr, "Coche Autónomo", "Error", "No se ha podido crear la cola de eventos.", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      exit(EXIT_FAILURE);
    }
    else
      std::clog<<"Cola de eventos creada."<<std::endl;

    timer_=al_create_timer(1.0/FPS);
    // añadiendo fuentes de eventos a la cola de eventos
    al_register_event_source(event_queue_, al_get_display_event_source(display_)); //para eventos como cerrar la ventana
    al_register_event_source(event_queue_,al_get_keyboard_event_source());  //eventos de teclado
    al_register_event_source(event_queue_, al_get_mouse_event_source());  //eventos de raton
    al_register_event_source(event_queue_, al_get_timer_event_source(timer_));
    al_start_timer(timer_);
    switch(Opcion)
    {
      case OpcionAleatoria:
        map_.resize(Filas,Columnas);
        calcular_escalado();
        map_.generar_aleatorio(Porcentaje,numero_paradas);
        break;
      case OpcionManual:
        map_.resize(Filas,Columnas);
        calcular_escalado();
        load_map();
        edit_map_opcion_manual();
        break;
      case OpcionFichero:
        map_.read_file(nombre_fichero_entrada);
        Filas=map_.get_n();
        Columnas=map_.get_m();
        calcular_escalado();
        break;
    }
    map_.get_pos_coche(coche_.get_set_x(),coche_.get_set_y());
    load_map();
  }

screen_t::~screen_t(void)
{
  al_destroy_display(display_);
  al_destroy_timer(timer_);
  al_destroy_event_queue(event_queue_);
}

void screen_t::load_map(void)
{
  for(my_size_t i=1; i<=map_.get_n(); i++)
    for(my_size_t j=1; j<=map_.get_m(); j++)
      draw_cell(i,j);
}

void screen_t::draw_cell(const my_size_t i, const my_size_t j)
{
  my_size_t x1= (j-1)*EscaladoPixelsX;
  my_size_t x2= x1+EscaladoPixelsX;
  my_size_t y1= (i-1)*EscaladoPixelsY;
  my_size_t y2= y1+EscaladoPixelsY;
  switch(map_(i,j))
  {
    case CeldaLibreVisitada:
      al_draw_filled_rectangle(x1,y1,x2,y2,ColorCeldaLibreVisitada);
      break;
    case CeldaObstaculo:
      al_draw_filled_rectangle(x1,y1,x2,y2,ColorCeldaObstaculo);
      break;
    case CeldaParadaVisitada:
      al_draw_filled_rectangle(x1,y1,x2,y2,ColorCeldaParadaVisitada);
      break;
    case CeldaInicial:
      al_draw_filled_rectangle(x1,y1,x2,y2,ColorCeldaInicial);
      break;
    case CeldaFinal:
        al_draw_filled_rectangle(x1,y1,x2,y2,ColorCeldaFinal);
      break;
    case CeldaLibre:
      al_draw_filled_rectangle(x1,y1,x2,y2,ColorCeldaLibre);
      break;
    case CeldaParada:
      al_draw_filled_rectangle(x1,y1,x2,y2,ColorCeldaParada);
      break;
    default:
      std::cerr<<"Error: tipo de celda no reconocido"<<std::endl;
      exit(EXIT_FAILURE);
      break;
  }
}

void screen_t::run(void)
{
  ALLEGRO_KEYBOARD_STATE keyState;
  //al_set_target_bitmap(al_get_backbuffer(display_));
  // poner una ventanita con las instrucciones
  bool done=0;
  bool draw=0;
  clock_t t_s, t_e;
  draw_coche(coche_.get_x(),coche_.get_y());
  al_flip_display();
  draw_cell(coche_.get_y(),coche_.get_x());
  do
  {
    ALLEGRO_EVENT events;
    al_wait_for_event(event_queue_, &events);
    if(events.type==ALLEGRO_EVENT_KEY_UP)
    {
      if(events.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
        done=1;
    }
    else
      if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
          done=1;
    if(events.type == ALLEGRO_EVENT_TIMER)
    {
      al_get_keyboard_state(&keyState);
      /*
      if(al_key_down(&keyState,ALLEGRO_KEY_DOWN)&&map_.visitable(coche_.get_y()+1,coche_.get_x()))
      {
        visitar_celda(coche_.get_x(),coche_.get_y());
        coche_.inc_y();
        draw=1;
      }
      else if(al_key_down(&keyState,ALLEGRO_KEY_UP)&&map_.visitable(coche_.get_y()-1,coche_.get_x()))
      {
        visitar_celda(coche_.get_x(),coche_.get_y());
        coche_.decr_y();
        draw=1;
      }
      else if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT)&&map_.visitable(coche_.get_y(),coche_.get_x()+1))
      {
        visitar_celda(coche_.get_x(),coche_.get_y());
        coche_.inc_x();
        draw=1;
      }
      else if(al_key_down(&keyState,ALLEGRO_KEY_LEFT)&&map_.visitable(coche_.get_y(),coche_.get_x()-1))
      {
        visitar_celda(coche_.get_x(),coche_.get_y());
        coche_.decr_x();
        draw=1;
      }*/
      /*else*/
      if(al_key_down(&keyState,ALLEGRO_KEY_P))
      {
        poner_obstaculos();
      }
      else if(al_key_down(&keyState,ALLEGRO_KEY_R))
      {
        std::clog<<"Intentando resolver.."<<std::endl;
        t_s=clock();
        a_star_search_t a_star(&map_);
        my_size_t x,y;
        map_.get_pos_end(x,y);
        std::vector<point_t> path=a_star.search(coche_.get_x(),coche_.get_y(),x,y);
        t_e=clock();
        t_e-=t_s;
        printf("%d ciclos de reloj (%f segundos).\n",t_e,((float)t_e)/CLOCKS_PER_SEC);
        if(path.size())
        {
          std::cout<<"Se ha encontrado una solución."<<std::endl;

          //my_size_t answer =al_show_native_message_box(nullptr, "coche autónomo", "Se ha encontrado una solución", "¿Desea que se muestre?",nullptr,ALLEGRO_MESSAGEBOX_YES_NO);
          //if(answer==1)
          {
            map_.write_file("./map_not_solved.txt");
            std::cout<<"Número de paradas visitadas: "<<map_.paradas_visitadas()<<std::endl;
            std::cout<<"Número de paradas sin visitar: "<<map_.paradas_no_visitadas()<<std::endl;
            for(my_size_t i=0; i<path.size(); i++)
            {
              coche_.set(path[i].x,path[i].y);
              visitar_celda(coche_.get_x(),coche_.get_y());
              draw_coche(coche_.get_x(),coche_.get_y());
              al_flip_display(); //actualizar imagen
              draw_cell(coche_.get_y(),coche_.get_x());
            }
          }
        }
        else
          std::cout<<"No se ha encontrado ninguna solución."<<std::endl;
      }
    }
    if(draw)
    {
      draw=0;
      draw_coche(coche_.get_x(),coche_.get_y());
      al_flip_display(); //actualizar imagen
      draw_cell(coche_.get_y(),coche_.get_x());
      //if(end())
        //done=1;
    }
  }
  while(!done);
  if(end())
    std::clog<<"Ruta finalizada."<<std::endl;
  if(Salida)
    map_.write_file(nombre_fichero_salida);
}

void screen_t::visitar_celda(const my_size_t x, const my_size_t y)
{
  map_.visitar(y,x);
  draw_cell(y,x);
}

void screen_t::draw_coche(const my_size_t x, const my_size_t y)
{
  my_size_t x1= (x-1)*EscaladoPixelsX;
  my_size_t x2= x1+EscaladoPixelsX;
  my_size_t y1= (y-1)*EscaladoPixelsY;
  my_size_t y2= y1+EscaladoPixelsY;
  al_draw_filled_rectangle(x1,y1,x2,y2,ColorCoche);
}

bool screen_t::end(void) const
{
  return(map_.final(coche_.get_y(),coche_.get_x())&&map_.paradas_visitadas());
}

void screen_t::edit_map_opcion_manual(void)
{
  double x,y;
  my_size_t celda_x, celda_y;
  bool done=0, draw=0;
  al_flip_display();  //mostrar pantalla
  std::clog<<"Introduciendo obstáculos."<<std::endl;
  do
  {
    ALLEGRO_EVENT events;
    al_wait_for_event(event_queue_, &events);
    if(events.type==ALLEGRO_EVENT_KEY_UP)
    {
      if(events.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
        done=1;
    }
    else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      done=1;
    else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
      x=events.mouse.x;
      y=events.mouse.y;
    }
    else if(events.type ==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

      celda_x=x/EscaladoPixelsX+1;
      celda_y=y/EscaladoPixelsY+1;
      if(events.mouse.button & 1)
      {
        map_(celda_y,celda_x)=CeldaObstaculo;
      }
      else if(events.mouse.button & 2)
      {
        map_(celda_y,celda_x)=CeldaLibre;
      }
      draw_cell(celda_y,celda_x);
      draw=1;
    }
    if(draw)
    {
      draw=0;
      al_flip_display();
    }
  }
  while(!done);
  std::clog<<"Obstáculos introducidos."<<std::endl;
  done=0;
  std::clog<<"Introduciendo paradas."<<std::endl;
  do
  {
    ALLEGRO_EVENT events;
    al_wait_for_event(event_queue_, &events);
    if(events.type==ALLEGRO_EVENT_KEY_UP)
    {
      if(events.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
        done=1;
    }
    else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      done=1;
    else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
      x=events.mouse.x;
      y=events.mouse.y;
    }
    else if(events.type ==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

      celda_x=x/EscaladoPixelsX+1;
      celda_y=y/EscaladoPixelsY +1;
      if(events.mouse.button & 1)
      {
        map_(celda_y,celda_x)=CeldaParada;
      }
      else if(events.mouse.button & 2)
      {
        map_(celda_y,celda_x)=CeldaLibre;
      }
      draw_cell(celda_y,celda_x);
      draw=1;
    }
    if(draw)
    {
      draw=0;
      al_flip_display();
    }
  }
  while(!done);
  std::clog<<"Paradas introducidas."<<std::endl;
  done=0;
  std::clog<<"Introduciendo inicio."<<std::endl;
  do
  {
    ALLEGRO_EVENT events;
    al_wait_for_event(event_queue_, &events);
    if(events.type==ALLEGRO_EVENT_KEY_UP)
    {
      if(events.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
        done=1;
    }
    else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      done=1;
    else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
      x=events.mouse.x;
      y=events.mouse.y;
    }
    else if(events.type ==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

      celda_x=x/EscaladoPixelsX+1;
      celda_y=y/EscaladoPixelsY +1;
      if(events.mouse.button & 1)
      {
        map_(celda_y,celda_x)=CeldaInicial;
      }
      else if(events.mouse.button & 2)
      {
        map_(celda_y,celda_x)=CeldaLibre;
      }
      draw_cell(celda_y,celda_x);
      draw=1;
    }
    if(draw)
    {
      draw=0;
      al_flip_display();
    }
  }
  while(!done);
  std::clog<<"Inicio introducido."<<std::endl;
  done=0;
  std::clog<<"Introduciendo fin."<<std::endl;
  do
  {
    ALLEGRO_EVENT events;
    al_wait_for_event(event_queue_, &events);
    if(events.type==ALLEGRO_EVENT_KEY_UP)
    {
      if(events.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
        done=1;
    }
    else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      done=1;
    else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
      x=events.mouse.x;
      y=events.mouse.y;
    }
    else if(events.type ==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

      celda_x=x/EscaladoPixelsX+1;
      celda_y=y/EscaladoPixelsY +1;
      if(events.mouse.button & 1)
      {
        map_(celda_y,celda_x)=CeldaFinal;
      }
      else if(events.mouse.button & 2)
      {
        map_(celda_y,celda_x)=CeldaLibre;
      }
      draw_cell(celda_y,celda_x);
      draw=1;
    }
    if(draw)
    {
      draw=0;
      al_flip_display();
    }
  }
  while(!done);
  std::clog<<"Fin introducido."<<std::endl;
}

void screen_t::poner_obstaculos(void)
{
  double x,y;
  my_size_t celda_x, celda_y;
  bool done=0, draw=0;
  std::clog<<"Introduciendo obstáculos."<<std::endl;
  do
  {
    ALLEGRO_EVENT events;
    al_wait_for_event(event_queue_, &events);
    if(events.type==ALLEGRO_EVENT_KEY_UP)
    {
      if(events.keyboard.keycode==ALLEGRO_KEY_ESCAPE)
        done=1;
    }
    else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      done=1;
    else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
      x=events.mouse.x;
      y=events.mouse.y;
    }
    else if(events.type ==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

      celda_x=x/EscaladoPixelsX+1;
      celda_y=y/EscaladoPixelsY +1;
      if(events.mouse.button & 1)
      {
        map_(celda_y,celda_x)=CeldaObstaculo;
      }
      else if(events.mouse.button & 2)
      {
        map_(celda_y,celda_x)=CeldaLibre;
      }
      draw_cell(celda_y,celda_x);
      draw=1;
    }
    if(draw)
    {
      draw=0;
      draw_coche(coche_.get_x(),coche_.get_y());
      al_flip_display();
      draw_cell(coche_.get_y(),coche_.get_x());
    }
  }
  while(!done);
  std::clog<<"Obstáculos introducidos."<<std::endl;
}
