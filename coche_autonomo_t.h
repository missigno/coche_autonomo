#ifndef COCHE_AUTONOMO_T_H
#define COCHE_AUTONOMO_T_H

#include "common.hpp"

class coche_autonomo_t
{
  private:
    my_size_t x_;
    my_size_t y_;
  public:
    coche_autonomo_t(const my_size_t x=1, const my_size_t y=1);
    ~coche_autonomo_t(void);
    my_size_t get_x(void) const;
    my_size_t get_y(void) const;
    void inc_x(void);
    void inc_y(void);
    void decr_x(void);
    void decr_y(void);
    void set_x(const my_size_t x);
    void set_y(const my_size_t y);
    void set(const my_size_t x, const my_size_t y);
    my_size_t& get_set_x(void);
    my_size_t& get_set_y(void);
};

#endif // COCHE_AUTONOMO_T_H
