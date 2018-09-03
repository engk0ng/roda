#ifndef RODA_ALGORITHM_FIND_HPP
#define RODA_ALGORITHM_FIND_HPP

#include "../type_traits.hpp"

namespace roda {

template<class InputIt,
         class T,
         typename = decltype(std::declval<iterator_value_type_t<InputIt>>() ==
                              std::declval<T>(),
                             (void)0)>
constexpr InputIt
find(InputIt first, const T& value)
{
  for(; first; ++first) {
    if(*first == value) {
      return first;
    }
  }
  return first;
}

template<class InputIt, class UnaryPredicate>
constexpr InputIt
find_if(InputIt first, UnaryPredicate p)
{
  for(; first; ++first) {
    if(p(*first)) {
      return first;
    }
  }
  return first;
}

template<class InputIt, class UnaryPredicate>
constexpr InputIt
find_if_not(InputIt first, UnaryPredicate q)
{
  for(; first; ++first) {
    if(!q(*first)) {
      return first;
    }
  }
  return first;
}

} // namespace roda

#endif