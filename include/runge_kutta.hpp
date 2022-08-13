// ------------------------------------------------------------------------------------------

#pragma once

#include "standard_algebra.hpp"
#include "default_operations.hpp"

#include "resize.hpp"

// ------------------------------------------------------------------------------------------
// класс-степпер
// для явного метода Рунге - Кутты IV порядка с постоянным шагом

template <typename state_type,
          typename value_type = double,
          typename time_type = value_type,
          typename algebra = standard_algebra,
          typename operations = default_operations>
class runge_kutta
{
  public:
  
    void set(state_type& x, time_type& dt)
    {
      dt2 = dt/static_cast<time_type>(2); dt3 = dt/static_cast<time_type>(3); dt6 = dt/static_cast<time_type>(6);
    }
  
    template <typename system_type>
    void do_step(system_type& system,
                 state_type& x,
                 time_type& t,
                 time_type& dt)
    {
    
      adjust_size(x);
  
      typedef typename operations::template scale_sum2<value_type, time_type>
                                            scale_sum2;
      typedef typename operations::template scale_sum5<value_type, time_type, time_type, time_type, time_type>
                                            scale_sum5;
      
      system(x, k1, t); // установка k1
      
      s_algebra.for_each3(x_tmp, x, k1, scale_sum2(one, dt2)); // подготовка x_tmp для k2
      system(x_tmp, k2, t+dt2); // установка k2
      
      s_algebra.for_each3(x_tmp, x, k2, scale_sum2(one, dt2)); // подготовка x_tmp для k3
      system(x_tmp, k3, t+dt2); // установка k3
      
      s_algebra.for_each3(x_tmp, x, k3, scale_sum2(one, dt)); // подготовка x_tmp для k4
      system(x_tmp, k4, t+dt); // установка k4
      
      s_algebra.for_each6(x, x, k1, k2, k3, k4, scale_sum5(one, dt6, dt3, dt3, dt6)); // подготовка x для искомого
  
    }


  private:

    algebra s_algebra;

    state_type x_tmp, k1, k2, k3, k4;
    
    const value_type one = 1;
    
    time_type dt2, dt3, dt6;
  
    void adjust_size(const state_type& x)
    {
      resize(x, x_tmp);
      resize(x, k1);
      resize(x, k2);
      resize(x, k3);
      resize(x, k4);
    }
};

// ------------------------------------------------------------------------------------------
