// ------------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>

// далее - шаблоны
#include "driver_const.hpp"
#include "driver_adapt.hpp"

#include "euler.hpp"
#include "euler_im.hpp"
#include "runge_kutta.hpp"
#include "runge_kutta_adapt.hpp"

#include <Python.h>

// для определения векторов и матриц
// позволим себе применить boost.uBLAS
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

// ------------------------------------------------------------------------------------------

typedef boost::numeric::ublas::vector<double> state_type;
typedef boost::numeric::ublas::matrix<double> matrix_type;

typedef euler<state_type> eu_ex_type;
typedef euler_im<state_type, matrix_type> eu_im_type;
typedef runge_kutta<state_type> rk_co_type;
typedef runge_kutta_adapt<state_type> rk_ad_type;

// ------------------------------------------------------------------------------------------
// функторы, описывающие предлагаемые к решению
// системы ОДУ в стандартной (Коши) форме
// (заранее рассчитанный якобиан - для неявного метода)

// -------------------------
// гармонический осциллятор:
// в идеале - окружность, с погрешностями - спираль

struct h_osc
{
  const double omega0;
  h_osc(const double omega0): omega0(omega0)
  { } // конструктор, задаем параметры системы
  
  template <typename state_type>
  void operator()(const state_type& x, state_type& dxdt, const double t)
  {
    dxdt[0] = x[1];
    dxdt[1] = - omega0*omega0*x[0];
  }
};

struct h_osc_j
{
  const double omega0;
  h_osc_j(h_osc& system): omega0(system.omega0)
  { } // конструктор, копирующий параметры системы
  
  template <typename state_type, typename matrix_type>
  void operator()(const state_type& x, matrix_type& J, const double t)
  {
    J(0,0) = 0.;              J(0,1) = 1.;
    J(1,0) = - omega0*omega0; J(1,1) = 0.;
  }
};

// -------------------------
// аттрактор Лоренца

struct lorenz
{
  const double sigma, R, b;
  lorenz(const double sigma, const double R, const double b): sigma(sigma), R(R), b(b)
  { } // конструктор, задаем параметры системы
  
  template <typename state_type>
  void operator()(const state_type& x, state_type& dxdt, const double t)
  {
    dxdt[0] = sigma*(x[1] - x[0]);
    dxdt[1] = R*x[0] - x[1] - x[0]*x[2];
    dxdt[2] = -b*x[2] + x[0]*x[1];
  }
};

struct lorenz_j
{
  const double sigma, R, b;
  lorenz_j(lorenz& system): sigma(system.sigma), R(system.R), b(system.b)
  { } // конструктор, копирующий параметры системы
  
  template <typename state_type, typename matrix_type>
  void operator()(const state_type& x, matrix_type& J, const double t)
  {
    J(0,0) = -sigma;    J(0,1) =  sigma; J(0,2) =  0.;
    J(1,0) =  R - x[2]; J(1,1) = -1.;    J(1,2) = -x[0];
    J(2,0) =  x[1];     J(2,1) =  x[0];  J(2,2) = -b;
  }
};

// -------------------------
// жесткая система
// (пояснение: http://old.exponenta.ru/EDUCAT/CLASS/courses/ode/theme15/theory.asp)

struct stiff
{
  template <typename state_type>
  void operator()(const state_type& x, state_type& dxdt, const double t)
  {
    dxdt[0] = -2.*x[0] - 998.*x[1];
    dxdt[1] = -1000.*x[1];
  }
};

struct stiff_j
{
  template <typename state_type, typename matrix_type>
  void operator()(const state_type& x, matrix_type& J, const double t)
  {
    J(0,0) = -2; J(0,1) = -998.;
    J(1,0) = 0;  J(1,1) = -1000.;
  }
};

// ------------------------------------------------------------------------------------------

int main ()
{
  // -------------------------
  
  // пределы интегрирования и начальный размер шага
  const double t_start = 0.;
  const double t_end = 5.;
  const double dt = 0.001;
  
  // для метода с переменным шагом
  const double error = 0.001;
 
  // -------------------------
  // система ОДУ и
  // якобиан
  
  h_osc system(10.);
  h_osc_j system_j(system);
  
//  lorenz system(10.0, 28.0, 8.0/3.0);
//  lorenz_j system_j(system);

//  stiff system;
//  stiff_j system_j;
  
  // -------------------------
  
  // начальное условие
  state_type x(3, 1.0); // вектор (1.0, 1.0, 1.0)
  x[0] = 10.0;
  
  // файлы со значениями x (запись - в каждую итерацию)
  std::ofstream resultfile1, resultfile2, resultfile3, resultfile4;
  
  // степперы (вызываются драйверами - в каждую итерацию)
  eu_ex_type stepper1; eu_im_type stepper2; rk_co_type stepper3; rk_ad_type stepper4;
  
  // открытие-закрытие файлов,
  // драйверы (вызывают степперы, обрабатывают полученные из степпера данные)
  resultfile1.open("result_eu_ex.txt");
  driver_const(system, x, stepper1, t_start, t_end, dt, resultfile1);
  resultfile1.close();
  
  resultfile2.open("result_eu_im.txt");
  driver_const(system, system_j, x, stepper2, t_start, t_end, dt, resultfile2);
  resultfile2.close();
  
  resultfile3.open("result_rk4_co.txt");
  driver_const(system, x, stepper3, t_start, t_end, dt, resultfile3);
  resultfile3.close();
  
  resultfile4.open("result_rk4_ad.txt");
  driver_adapt(system, x, stepper4, t_start, t_end, dt, error, resultfile4);  
  resultfile4.close();
  
  // -------------------------
  // запустим Python-скрипт для визуализации
  
  char pythonfile[] = "../plot.py";
  FILE* fp;
  Py_Initialize();
  fp = fopen(pythonfile, "r");
  PyRun_SimpleFile(fp, pythonfile);
  Py_Finalize();
  
  // -------------------------
}

// ------------------------------------------------------------------------------------------
