#ifndef RODA_ALGORITHM_HPP
#define RODA_ALGORITHM_HPP

#include "type_traits.hpp"

namespace roda {

template<class InputIt, class UnaryFunction>
constexpr UnaryFunction
for_each(InputIt iter, UnaryFunction f)
{
  for(; iter; ++iter) {
    f(*iter);
  }
  return f;
}

/**
 * count and count_if
 */
template<class InputIt, class T>
constexpr iterator_difference_type_t<InputIt>
count(InputIt first, const T& value)
{
  auto ret = iterator_difference_type_t<InputIt>{0};
  for(; first; ++first) {
    if(*first == value) {
      ret++;
    }
  }
  return ret;
}

template<class InputIt, class UnaryPredicate>
constexpr iterator_difference_type_t<InputIt>
count_if(InputIt first, UnaryPredicate p)
{
  auto ret = iterator_difference_type_t<InputIt>{0};
  for(; first; ++first) {
    if(p(*first)) {
      ret++;
    }
  }
  return ret;
}

} // namespace roda

#endif