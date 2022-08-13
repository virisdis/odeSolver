// ------------------------------------------------------------------------------------------

#pragma once

// ------------------------------------------------------------------------------------------
// структура, описывающая операции,
// которые должны быть применены
// к содержимому контейнеров

struct default_operations
{

  // возможно, переписать более кратко? н-р, через variadic templates

  // -------------------------

  template <typename F1 = double, typename F2 = F1>
  struct scale_sum2
  {
    const F1 alpha1;
    const F2 alpha2;
    
//    scale_sum2(F1 a1, F2 a2): alpha1(a1), alpha2(a2)
//    { } // конструктор
    
    template <typename T0, typename T1, typename T2>
    void operator() (T0& t0, const T1& t1, const T2& t2) const
    {
      t0 = alpha1*t1 + alpha2*t2;
    }
  };
  
  // -------------------------
  
  template <typename F1 = double, typename F2 = F1, typename F3 = F1>
  struct scale_sum3
  {
    const F1 alpha1;
    const F2 alpha2;
    const F3 alpha3;
    
//    scale_sum3(F1 a1, F2 a2, F3 a3): alpha1(a1), alpha2(a2), alpha3(a3)
//    { } // конструктор
    
    template <typename T0, typename T1, typename T2, typename T3>
    void operator() (T0& t0, const T1& t1, const T2& t2, const T3& t3) const
    {
      t0 = alpha1*t1 + alpha2*t2 + alpha3*t3;
    }
  };
  
  // -------------------------
  
  template <typename F1 = double, typename F2 = F1, typename F3 = F1, typename F4 = F1>
  struct scale_sum4
  {
    const F1 alpha1;
    const F2 alpha2;
    const F3 alpha3;
    const F4 alpha4;
    
//    scale_sum4(F1 a1, F2 a2, F3 a3, F4 a4): alpha1(a1), alpha2(a2), alpha3(a3), alpha4(a4)
//    { } // конструктор
    
    template <typename T0, typename T1, typename T2, typename T3, typename T4>
    void operator() (T0& t0, const T1& t1, const T2& t2, const T3& t3, const T4& t4) const
    {
      t0 = alpha1*t1 + alpha2*t2 + alpha3*t3 + alpha4*t4;
    }
  };
  
  // -------------------------

  template <typename F1 = double, typename F2 = F1, typename F3 = F1, typename F4 = F1, typename F5 = F1>
  struct scale_sum5
  {
    const F1 alpha1;
    const F2 alpha2;
    const F3 alpha3;
    const F4 alpha4;
    const F5 alpha5;
    
//    scale_sum5(F1 a1, F2 a2, F3 a3, F4 a4, F5 a5): alpha1(a1), alpha2(a2), alpha3(a3), alpha4(a4), alpha5(a5)
//    { } // конструктор
    
    template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    void operator() (T0& t0, const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5) const
    {
      t0 = alpha1*t1 + alpha2*t2 + alpha3*t3 + alpha4*t4 + alpha5*t5;
    }
  };

  // -------------------------

};

// ------------------------------------------------------------------------------------------
