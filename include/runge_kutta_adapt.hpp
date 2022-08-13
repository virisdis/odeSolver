// ------------------------------------------------------------------------------------------

#pragma once

#include <numeric>

#include "standard_algebra.hpp"
#include "default_operations.hpp"

#include "resize.hpp"

// ------------------------------------------------------------------------------------------
// класс-степпер
// для метода Кутты - Мерсона
// (из семейства методов Рунге - Кутты)

template <typename state_type,
          typename value_type = double,
          typename time_type = value_type,
          typename algebra = standard_algebra,
          typename operations = default_operations>
class runge_kutta_adapt
{
  public:
  
    template <typename system_type>
    void do_step(system_type& system,
                 state_type& x,
                 time_type& t,
                 time_type& dt,
           const value_type& error,
                 char& flag)
    {
    
      adjust_size(x);
  
      typedef typename operations::template scale_sum2<value_type, time_type>
                                            scale_sum2;
      typedef typename operations::template scale_sum3<value_type, time_type, time_type>
                                            scale_sum3;
      typedef typename operations::template scale_sum4<value_type, time_type, time_type, time_type>
                                            scale_sum4;
      
      dt12 = dt/static_cast<time_type>(2); dt13 = dt/static_cast<time_type>(3); dt16 = dt/static_cast<time_type>(6); dt18 = dt/static_cast<time_type>(8),
      dt21 = static_cast<time_type>(2)*dt; dt23 = (static_cast<time_type>(2)/static_cast<time_type>(3))*dt;
      dt32 = (static_cast<time_type>(3)/static_cast<time_type>(2))*dt; dt38 = (static_cast<time_type>(3)/static_cast<time_type>(8))*dt;
      
      const value_type error164 = error/static_cast<value_type>(64);
      
      system(x, k1, t); // установка k1
      
      s_algebra.for_each3(x_tmp, x, k1, scale_sum2(one, dt13)); // подготовка x_tmp для k2
      system(x_tmp, k2, t+dt13); // установка k2
      
      s_algebra.for_each4(x_tmp, x, k1, k2, scale_sum3(one, dt16, dt16)); // подготовка x_tmp для k3
      system(x_tmp, k3, t+dt13); // установка k3

      s_algebra.for_each4(x_tmp, x, k1, k2, scale_sum3(one, dt18, dt38)); // подготовка x_tmp для k4
      system(x_tmp, k4, t+dt12); // установка k4
      
      s_algebra.for_each5(x_tmp, x, k1, k3, k4, scale_sum4(one, dt12, -dt32, dt21)); // подготовка x_tmp для k5
      system(x_tmp, k5, t+dt); // установка k5
      
      // x_tmp, полученный ранее для k5, далее сравним с x
      s_algebra.for_each5(x, x, k1, k4, k5, scale_sum4(one, dt16, dt23, dt16)); // потенциальное искомое
      
      s_algebra.for_each3(x_tmp, x, x_tmp, scale_sum2(one, -one)); // далее подадим рассчитанный здесь x_tmp на вход функции расчета нормы
      
      R = 0.2 * eu_norm(x_tmp);
      
      if (R > error) { flag = 1; }
      else
      if (R <= error164) { flag = 2; };

    }
    
    /*
    void set_dt_fracts(time_type& dt)
    {
      this->dt12 = dt/2.; this->dt13 = dt/3.; this->dt16 = dt/6.; this->dt18 = dt/8.;
      this->dt21 = 2.*dt; this->dt23 = (2./3.)*dt;
      this->dt32 = -(3./2.)*dt; this->dt38 = (3./8.)*dt;
    }
    */

  private:
      
    algebra s_algebra;

    state_type x_tmp, k1, k2, k3, k4, k5;
    
    value_type R;
    
    const value_type one = 1;
    
    time_type dt12, dt13, dt16, dt18,
              dt21, dt23,
              dt32, dt38;
    
    
    void adjust_size(const state_type& x)
    {
      resize(x, x_tmp);
      resize(x, k1);
      resize(x, k2);
      resize(x, k3);
      resize(x, k4);
      resize(x, k5);
    }
    
    value_type eu_norm(state_type &in) // евклидова норма
    {
      std::transform(in.begin(), in.end(), in.begin(), [](value_type& c){ return std::pow(c, 2); });
      value_type result = std::accumulate(in.begin(), in.end(), static_cast<value_type>(0));
      result = std::sqrt(result);
      return result;
    }
};

// ------------------------------------------------------------------------------------------
