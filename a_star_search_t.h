#ifndef A_STAR_SEARCH_T_H
#define A_STAR_SEARCH_T_H
#include "common.hpp"
#include "map_t.h"
#include "a_star_search_node_t.h"
#include <vector>
//revisar libreria map

class a_star_search_t
{
  private:
    std::vector<a_star_search_node_t*> c_list;
    std::vector<a_star_search_node_t*> a_list;
    std::vector<point_t> best_path;
    map_t* map_;//podria evitarse
  public:
    a_star_search_t(map_t *map);
    //~a_star_search_t(void);
    std::vector<point_t> search(const my_size_t s_x, const my_size_t s_y, const my_size_t e_x, const my_size_t e_y);
  private:
    void add_node_a_list(a_star_search_node_t* node);
    bool contain_c_list(a_star_search_node_t* node) const;
    bool contain_a_list(a_star_search_node_t* node) const;
    std::vector<a_star_search_node_t*> search_adjacent_nodes(a_star_search_node_t* current, a_star_search_node_t* end) const;


};

#endif // A_STAR_SEARCH_T_H
