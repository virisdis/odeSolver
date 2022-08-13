// ------------------------------------------------------------------------------------------

#pragma once

// ------------------------------------------------------------------------------------------

// функции-драйверы,
// в которой вызывается
// отвечающий за совершение шага
// метод объекта-степпера
// (шаг - постоянного размера).

// ------------------------------------------------------------------------------------------
// вызов явного метода

template <typename system_type,
          typename state_type,
          typename stepper_type,
          typename time_type = double>
void driver_const(
                  system_type& system,
                  state_type x,
                  stepper_type& stepper,
            const time_type& t_start,
            const time_type& t_end,
                  time_type dt,
                  std::ofstream& resultfile
                 )
{

  for (time_type t = t_start; t < t_end; )
  {
    stepper.do_step(system, x, t, dt); // меняется x
    resultfile << t << " ";
    resultfile << x[0] << " " << x[1] << " " << x[2] << std::endl;
    t += dt;
  }
}

// ------------------------------------------------------------------------------------------
// вызов неявного метода

template <typename system_type,
          typename system_j_type,
          typename state_type,
          typename stepper_type,
          typename time_type = double>
void driver_const(
                  system_type& system,
                  system_j_type& system_j,
                  state_type x,
                  stepper_type& stepper,
            const time_type& t_start,
            const time_type& t_end,
                  time_type dt,
                  std::ofstream& resultfile
                 )
{
  for (time_type t = t_start; t < t_end; )
  {
    stepper.do_step(system, system_j, x, t, dt); // меняется x
    resultfile << t << " ";
    resultfile << x[0] << " " << x[1] << " " << x[2] << std::endl;
    t += dt;
  }
}

// ------------------------------------------------------------------------------------------
