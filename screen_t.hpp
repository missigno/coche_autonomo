#ifndef SCREEN_T_H
#define SCREEN_T_H
//#include "common.hpp"
//#include "map_t.h"
#include "a_star_search_t.h"
#include "coche_autonomo_t.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>


class screen_t
{
  private:
    ALLEGRO_DISPLAY *display_;
    ALLEGRO_EVENT_QUEUE *event_queue_;
    ALLEGRO_TIMER *timer_;
    map_t map_;
    coche_autonomo_t coche_;
  public:
    screen_t(void);
    ~screen_t(void);
    void load_map(void);
    void draw_cell(const my_size_t i, const my_size_t j);
    void run(void);
    void visitar_celda(const my_size_t x, const my_size_t y);
    void draw_coche(const my_size_t x, const my_size_t y);

    bool end(void) const;

    void edit_map_opcion_manual(void);
    void poner_obstaculos(void);

};

#endif // SCREEN_T_H
