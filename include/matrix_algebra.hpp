// ------------------------------------------------------------------------------------------

#pragma once

// ------------------------------------------------------------------------------------------
// структура для обработки итераций,
// внутри - функция, которые принимают
// объекты матричных контейнеров и операций
// (см. struct default_operations),
// находят итераторы для контейнеров
// и производят итерации по всем контейнерам,
// поэлементно выполняя указанную операцию
  
struct matrix_algebra
{
  template<typename Sa, typename Sb, typename Sc, typename Op>
  void for_each3 (Sa& sa, Sb& sb, Sc& sc, Op op) const
  {
    using std::begin;
    using std::end;
    
    auto first_a1 = sa.begin1();
    auto first_b1 = sb.begin1();
    auto first_c1 = sc.begin1();
    auto first_a2 = first_a1.begin();
    auto first_b2 = first_b1.begin();
    auto first_c2 = first_c1.begin();
    
    for( ; first_a1 != sa.end1(); first_a1++, first_b1++, first_c1++)
    {
      for( ; first_a2 != first_a1.end(); first_a2++, first_b2++, first_c2++)
      {
        op(*first_a2, *first_b2, *first_c2);
      }
    }
  }
};

// ------------------------------------------------------------------------------------------
