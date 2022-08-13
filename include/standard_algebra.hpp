// ------------------------------------------------------------------------------------------

#pragma once

// ------------------------------------------------------------------------------------------
// структура для обработки итераций,
// внутри - функции, которые принимают
// объекты контейнеров и операций
// (см. struct default_operations),
// находят итераторы для контейнеров
// и производят итерации по всем контейнерам,
// поэлементно выполняя указанную операцию

struct standard_algebra
{

  // возможно, переписать более кратко? н-р, через variadic templates

  // -------------------------

  template<typename S1, typename S2, typename S3, typename Op>
  void for_each3 (S1& s1, S2& s2, S3& s3, Op op) const
  {
    using std::begin;
    using std::end;
    
    auto first1 = begin(s1);
    auto first2 = begin(s2);
    auto first3 = begin(s3);
    
    auto last1 = end(s1); // нужен для остановки цикла for
    
    for ( ; first1 != last1; )
      op(*first1++, *first2++, *first3++);
  }
  
  // -------------------------
  
  template<typename S1, typename S2, typename S3, typename S4, typename Op>
  void for_each4 (S1& s1, S2& s2, S3& s3, S4& s4, Op op) const
  {
    using std::begin;
    using std::end;
    
    auto first1 = begin(s1);
    auto first2 = begin(s2);
    auto first3 = begin(s3);
    auto first4 = begin(s4);
    
    auto last1 = end(s1);
    
    for ( ; first1 != last1; )
      op(*first1++, *first2++, *first3++, *first4++);
  }
  
  // -------------------------
  
  template<typename S1, typename S2, typename S3, typename S4, typename S5, typename Op>
  void for_each5 (S1& s1, S2& s2, S3& s3, S4& s4, S5& s5, Op op) const
  {
    using std::begin;
    using std::end;
    
    auto first1 = begin(s1);
    auto first2 = begin(s2);
    auto first3 = begin(s3);
    auto first4 = begin(s4);
    auto first5 = begin(s5);
    
    auto last1 = end(s1);
    
    for ( ; first1 != last1; )
      op(*first1++, *first2++, *first3++, *first4++, *first5++);
  }
  
  // -------------------------
  
  template<typename S1, typename S2, typename S3, typename S4, typename S5, typename S6, typename Op>
  void for_each6 (S1& s1, S2& s2, S3& s3, S4& s4, S5& s5, S6& s6, Op op) const
  {
    using std::begin;
    using std::end;
    
    auto first1 = begin(s1);
    auto first2 = begin(s2);
    auto first3 = begin(s3);
    auto first4 = begin(s4);
    auto first5 = begin(s5);
    auto first6 = begin(s6);
    
    auto last1 = end(s1);
    
    for ( ; first1 != last1; )
      op(*first1++, *first2++, *first3++, *first4++, *first5++, *first6++);
  }

  // -------------------------

};

// ------------------------------------------------------------------------------------------
