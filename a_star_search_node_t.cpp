#include "a_star_search_node_t.h"

a_star_search_node_t::a_star_search_node_t(a_star_search_node_t* prev, a_star_search_node_t* end, const my_size_t x, const my_size_t y, const my_size_t cost):
  prev_(prev),
  end_(end),
  x_(x),
  y_(y),
  c_total_(0),
  c_g_(cost)
  {
    if(end_!=nullptr)
      c_total_=c_g_+calculate_cost();
  }
a_star_search_node_t::~a_star_search_node_t(void)
{}

my_size_t a_star_search_node_t::calculate_cost(void) const
{
  //(x_<end_->x_ ? end_->x_-x_ : x_-end_->x_ )+(y_<end_->y_ ? end_->y_-y_ : y_-end_->y_ )
  return((x_<end_->x_ ? end_->x_-x_ : x_-end_->x_ )+(y_<end_->y_ ? end_->y_-y_ : y_-end_->y_ ));
  //return Math.abs(this.getX()  - NodoFinal.getX()) + Math.abs(this.getY() - NodoFinal.getY());
}

bool a_star_search_node_t::operator==(a_star_search_node_t* x) const
{
  return(x_==x->x_&&y_==x->y_);
}

bool a_star_search_node_t::operator!=(a_star_search_node_t* x) const
{
  return(x_!=x->x_||y_!=x->y_);
}

my_size_t a_star_search_node_t::get_x(void) const
{
  return(x_);
}

my_size_t a_star_search_node_t::get_y(void) const
{
  return(y_);
}

my_size_t a_star_search_node_t::get_c_total(void) const
{
  return(c_total_);
}

my_size_t a_star_search_node_t::get_c_g(void) const
{
  return(c_g_);
}

a_star_search_node_t* a_star_search_node_t::get_prev(void) const
{
  return(prev_);
}
