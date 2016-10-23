#include "coche_autonomo_t.h"

coche_autonomo_t::coche_autonomo_t(const my_size_t x, const my_size_t y):
  x_(x),
  y_(y)
  {}

coche_autonomo_t::~coche_autonomo_t(void)
{}

my_size_t coche_autonomo_t::get_x(void) const
{
  return(x_);
}

my_size_t coche_autonomo_t::get_y(void) const
{
  return(y_);
}

void coche_autonomo_t::inc_x(void)
{
  ++x_;
}

void coche_autonomo_t::inc_y(void)
{
  ++y_;
}

void coche_autonomo_t::decr_x(void)
{
  --x_;
}

void coche_autonomo_t::decr_y(void)
{
  --y_;
}

void coche_autonomo_t::set_x(const my_size_t x)
{
  x_=x;
}

void coche_autonomo_t::set_y(const my_size_t y)
{
  y_=y;
}

void coche_autonomo_t::set(const my_size_t x, const my_size_t y)
{
  x_=x;
  y_=y;
}

my_size_t& coche_autonomo_t::get_set_x(void)
{
  return(x_);
}

my_size_t& coche_autonomo_t::get_set_y(void)
{
  return(y_);
}
