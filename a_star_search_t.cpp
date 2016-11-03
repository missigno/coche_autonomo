#include "a_star_search_t.h"

a_star_search_t::a_star_search_t(map_t *map):
  c_list(),
  a_list(),
  best_path(),
  map_(map)
  {}

a_star_search_t::~a_star_search_t(void)
{
  map_ = nullptr;
  while(c_list.size())
  {
    delete c_list[c_list.size()-1];
    c_list.pop_back();
  }
  while(a_list.size())
  {
    delete a_list[a_list.size()-1];
    a_list.pop_back();
  }
}

void a_star_search_t::add_node_a_list(a_star_search_node_t* node)
{
  my_size_t i=0;
  my_size_t cost = node->get_c_total();
  while((a_list.size()>i) && (cost < a_list[i]->get_c_total()))
      i++;
  //REVISAR
  //ListaA.insertElementAt(nodo, i);
  a_list.emplace(a_list.begin()+i,node);
}

bool a_star_search_t::contain_c_list(a_star_search_node_t* node) const
{
  for(my_size_t i=0; i<c_list.size(); ++i)
  {
    if((*node)==c_list[i])
      return(1);
  }
  return(0);
}

bool a_star_search_t::contain_a_list(a_star_search_node_t* node) const
{

  for(my_size_t i=0; i<a_list.size(); ++i)
  {
    if((*a_list[i])==node)
      return(1);
  }
  return(0);
}

std::vector<a_star_search_node_t*> a_star_search_t::search_adjacent_nodes(a_star_search_node_t* current, a_star_search_node_t* end) const
{
  std::vector<a_star_search_node_t*> adjacent_nodes;

  //insertar abajo
  if(map_->visitable(current->get_y()+1,current->get_x())&&current->get_y()+1<map_->get_n())
  {
    if(current->get_prev()!=nullptr)
    {
      if((current->get_prev()->get_x()!=current->get_x()||current->get_prev()->get_y()!=current->get_y()+1))
        adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x(),current->get_y()+1,current->get_c_g()+1));
    }
    else
      adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x(),current->get_y()+1,current->get_c_g()+1));
  }

  if(map_->visitable(current->get_y()-1,current->get_x())&&current->get_y()-1<map_->get_n())
  {
    if(current->get_prev()!=nullptr)
    {
      if((current->get_prev()->get_x()!=current->get_x()||current->get_prev()->get_y()!=current->get_y()-1))
        adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x(),current->get_y()-1,current->get_c_g()+1));
    }
    else
      adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x(),current->get_y()-1,current->get_c_g()+1));
  }

  if(map_->visitable(current->get_y(),current->get_x()+1)&&current->get_x()+1<map_->get_m())
  {
    if(current->get_prev()!=nullptr)
    {
      if((current->get_prev()->get_x()!=current->get_x()+1||current->get_prev()->get_y()!=current->get_y()))
        adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x()+1,current->get_y(),current->get_c_g()+1));
    }
    else
      adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x()+1,current->get_y(),current->get_c_g()+1));
  }

  if(map_->visitable(current->get_y(),current->get_x()-1)&&current->get_x()-1<map_->get_m())
  {
    if(current->get_prev()!=nullptr)
    {
      if((current->get_prev()->get_x()!=current->get_x()-1||current->get_prev()->get_y()!=current->get_y()))
        adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x()-1,current->get_y(),current->get_c_g()+1));
    }
    else
      adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x()-1,current->get_y(),current->get_c_g()+1));
  }
/*
  if(map_->visitable(current->get_y()+1,current->get_x())&&
    (current->get_prev()->get_x()!=current->get_x()||
    current->get_prev()->get_y()!=current->get_y()+1))
      adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x(),current->get_y()+1,current->get_c_g()+1));
  //insertar abajo
  if(map_->visitable(current->get_y()-1,current->get_x())&&
    (current->get_prev()->get_x()!=current->get_x()||
    current->get_prev()->get_y()!=current->get_y()-1))
      adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x(),current->get_y()-1,current->get_c_g()+1));
  //insertar derecha
  if(map_->visitable(current->get_y(),current->get_x()+1)&&
    (current->get_prev()->get_x()!=current->get_x()+1||
    current->get_prev()->get_y()!=current->get_y()))
      adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x()+1,current->get_y(),current->get_c_g()+1));
  //insertar izquierda
  if(map_->visitable(current->get_y(),current->get_x()-1)&&
    (current->get_prev()->get_x()!=current->get_x()-1||
    current->get_prev()->get_y()!=current->get_y()))
      adjacent_nodes.push_back(new a_star_search_node_t(current,end,current->get_x()-1,current->get_y(),current->get_c_g()+1));
*/

  return(adjacent_nodes);
}

std::vector<point_t> a_star_search_t::search(const my_size_t s_x, const my_size_t s_y, const my_size_t e_x, const my_size_t e_y)
{
  a_star_search_node_t* last = new a_star_search_node_t(nullptr,nullptr,e_x,e_y,0);
  a_star_search_node_t* first = new a_star_search_node_t(nullptr,last, s_x, s_y,0);
  //tal vez no hace falta el nodo inicio
  point_t dummy;
  add_node_a_list(first);
  //my_size_t cont=0;
  while(a_list.size())
  {
    a_star_search_node_t* current = a_list[a_list.size()-1];
    if((*current)==last)
    {
      while(current!=nullptr)
      {
        dummy.x=current->get_x();
        dummy.y=current->get_y();
        best_path.push_back(dummy);
        //best_path.push_back(point_t{current->get_x(),current->get_y()});
        current=current->get_prev();
      }
      return(best_path);
    }
    //a_list[a_list.size()-1] delete
    a_list.pop_back();

    std::vector<a_star_search_node_t*> possible_nodes=search_adjacent_nodes(current, last);
    //cambiar
    //revisar

    for(my_size_t i=0; i<possible_nodes.size(); ++i)
    {
      if(!contain_c_list(possible_nodes[i]))
      {
        if(contain_a_list(possible_nodes[i]))
        {

        }
        else
          add_node_a_list(possible_nodes[i]);
      }
    }

      /*
    for(auto& possible_node: possible_nodes)
    {
      if(!contain_c_list(possible_node))
      {
        if(contain_a_list(possible_node))
        {
          if(possible_node->get_c_g()>=current->get_c_g())
            continue;
        }
        add_node_a_list(possible_node);
      }
    }
    */
    c_list.push_back(current);
  }
  std::vector<point_t> aux;
  return(aux);
}
