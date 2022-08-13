// ------------------------------------------------------------------------------------------

#pragma once

// ------------------------------------------------------------------------------------------
// функция-драйвер,
// в которой вызывается
// отвечающий за совершение шага
// метод объекта-степпера
// (шаг - переменного размера,
// с учетом заданной ошибки).

template <typename system_type,
          typename state_type,
          typename stepper_type,
          typename time_type = double,
          typename value_type = time_type>
void driver_adapt(
                  system_type& system,
                  state_type x,
                  stepper_type& stepper,
            const time_type& t_start,
            const time_type& t_end,
                  time_type dt,
            const value_type& error,
                  std::ofstream& resultfile
                 )
{
  state_type x_old; // будем сохранять входной x на случай, если для выходного x норма превысит ошибку (тогда итерируем заново с шагом dt/2)
  char flag; // флаг: 0 - продолжить, 1 - повторить со вдвое уменьшенным шагом, 2 - продолжить со вдвое увеличенным шагом
  
  for (time_type t = t_start; t < t_end; )
  {
  
    x_old = x;
    
    stepper.do_step(system, x, t, dt, error, flag = 0); // меняются x и (возможно) flag
    // кажется, определение дробей от dt в do_step (внутри настоящего цикла) не повлекло заметного увеличения времени выполнения (с векторами того размера, который задан в main(), системами и т. п., с моим компилятором)
    if (flag == 1)
    {
      x = x_old;
      dt = dt/2;
      continue;
    };
    
    resultfile << t << " ";
    resultfile << x[0] << " " << x[1] << " " << x[2] << std::endl;
    
    if (flag == 2)
    {
      dt = dt*2;
    }
    
    t += dt;
    
  }
}

// ------------------------------------------------------------------------------------------
