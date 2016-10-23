#ifndef MAP_T_H
#define MAP_T_H
#include "common.hpp"

#include <fstream> //ficheros
#include <cstdlib> //srand y rand
#include <time.h>  //time

typedef unsigned short int cell_t;
class map_t
{
  private:
    cell_t* cells_;
    my_size_t n_;
    my_size_t m_;
  public:
    map_t(void);
    map_t(const cell_t n, const cell_t m);
    ~map_t(void);

    void read_file(std::string file_name);
    void write_file(std::string file_name);
    void resize(my_size_t n, my_size_t m);

    my_size_t get_n(void) const;
    my_size_t get_m(void) const;
    cell_t get(const my_size_t i, const my_size_t j) const;
    void set(const my_size_t i, const my_size_t j, const cell_t &x);
    cell_t& get_set(const my_size_t i, const my_size_t j);
    cell_t operator()(const my_size_t i, const my_size_t j) const;
    cell_t& operator()(const my_size_t i, const my_size_t j);
    bool visitable(const my_size_t i, const my_size_t j) const;
    void visitar(const my_size_t i, const my_size_t j);
    bool final(const my_size_t i, const my_size_t j) const;
    bool paradas_visitadas(void) const;

    void get_pos_coche(my_size_t &x, my_size_t &y);
    void generar_aleatorio(const double porcentaje, const my_size_t numero_paradas);
    //get_paradas
    //get_final
  private:
    my_size_t pos(const my_size_t i, const my_size_t j) const;
    void create_map(void);
    void destroy_map(void);

};

#endif // MAP_T_H
