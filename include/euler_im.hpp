// ------------------------------------------------------------------------------------------

#pragma once

#include "standard_algebra.hpp"
#include "matrix_algebra.hpp"
#include "default_operations.hpp"

#include "resize.hpp"

#include <boost/numeric/ublas/lu.hpp>

// ------------------------------------------------------------------------------------------
// класс-степпер
// для неявного (вернее, полуявного - т. к. одна итерация метода Ньютона)
// метода Эйлера с постоянным шагом

template <typename state_type,
          typename matrix_type,
          typename value_type = double,
          typename time_type = value_type,
          typename algebra1 = standard_algebra,
          typename algebra2 = matrix_algebra,
          typename operations = default_operations>
class euler_im
{
  public:
  
    template <typename system_type, typename system_j_type>
    void do_step(system_type& system,
                 system_j_type& system_j,
                 state_type& x,
                 time_type& t,
                 time_type& dt)
    {

      adjust_size(x);
  
      typedef typename operations::template scale_sum2<value_type, time_type>
                                            scale_sum2;

      system(x, dxdt, t); // установка dxdt
      system_j(x, J, t); // установка J
      set_identity_m(I); // установка I
      m_algebra.for_each3(A, I, J, scale_sum2(one, -dt)); // установка A
      
      std::transform(dxdt.begin(), dxdt.end(), dxdt.begin(), [&dt](value_type& c){ return c*dt; });
      
      // чтобы воспользоваться методом Ньютона (одна итерация),
      // решим линейное уравнение
      dx = solve(A, dxdt);
      s_algebra.for_each3(x, x, dx, scale_sum2(one, one)); // искомое
      
    }


  private:
    
    standard_algebra s_algebra;
    matrix_algebra m_algebra;
  
    state_type dx, dxdt;
    matrix_type J, // якобиан
                I,
                A; // матрица I-dt*J

    const value_type zero = 0;
    const value_type one = 1;
  
    void adjust_size(const state_type& x)
    {
      resize(x, dx);
      resize(x, dxdt);
      
      // resize для матриц всегда возвращает квадратную матрицу
      resize(x, J);
      resize(x, I);
      resize(x, A);
      
    }
    
    void set_identity_m(matrix_type& M)
    {
      for(unsigned int i = 0; i < M.size1(); i++)
      {
        for(unsigned int j = 0; j < M.size2(); j++)
        {
          (i == j) ?  M(i,j) = one : M(i,j) = zero;
        }
      }
    }

    state_type solve(matrix_type& A, state_type& b) // A*x = b
    {
      // возможно, для большей модульности стоило не ограничивать возможность представления входных данных одними лишь векторами и матрицами из boost.uBLAS
    
      namespace ublas = boost::numeric::ublas;
      
      ublas::permutation_matrix<std::size_t> pm(A.size1());
      lu_factorize(A, pm);
      state_type result(b);
      lu_substitute(A, pm, result);
      return result;
    }
};

// ------------------------------------------------------------------------------------------
