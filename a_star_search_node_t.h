#ifndef A_STAR_SEARCH_NODE_T_H
#define A_STAR_SEARCH_NODE_T_H
#include "common.hpp"

//class a_star_search_node_t;

class a_star_search_node_t
{
  private:
    a_star_search_node_t* prev_;
    a_star_search_node_t* end_;
    my_size_t x_;
    my_size_t y_;
    my_size_t c_total_;
    my_size_t c_g_;
  public:
    a_star_search_node_t(a_star_search_node_t* prev, a_star_search_node_t* end, const my_size_t x, const my_size_t y, const my_size_t cost);
    ~a_star_search_node_t(void);
    //Calcula distancia de Manhattan
    my_size_t calculate_cost(void) const;
    bool operator==(a_star_search_node_t* x) const;
    bool operator!=(a_star_search_node_t* x) const;
    my_size_t get_x(void) const;
    my_size_t get_y(void) const;
    my_size_t get_c_total(void) const;
    my_size_t get_c_g(void) const;
    a_star_search_node_t* get_prev(void) const;
};

#endif // A_STAR_SEARCH_NODE_T_H
