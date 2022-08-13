// ------------------------------------------------------------------------------------------

#pragma once

#include "standard_algebra.hpp"
#include "default_operations.hpp"

#include "resize.hpp"

// ------------------------------------------------------------------------------------------
// класс-степпер
// для явного метода Эйлера с постоянным шагом

template <typename state_type,
          typename value_type = double,
          typename time_type = value_type,
          typename stand_algebra = standard_algebra,
          typename operations = default_operations>
class euler
{

  public:
  
    template <typename system_type>
    void do_step(system_type& system,
                 state_type& x,
                 time_type& t,
                 time_type& dt)
    {
    
      adjust_size(x);
  
      typedef typename operations::template scale_sum2<value_type, time_type>
                                            scale_sum2;

      system(x, k, t); // установка k
      s_algebra.for_each3(x, x, k, scale_sum2(one, dt)); // подготовка x для искомого
      
    }


  private:
  
    stand_algebra s_algebra;
  
    state_type k;
    
    const value_type one = 1;
  
    void adjust_size(const state_type& x)
    {
      resize(x, k);
    }
    
};

// ------------------------------------------------------------------------------------------
