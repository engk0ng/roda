#ifndef RODA_ALGORITHM_HPP
#define RODA_ALGORITHM_HPP

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

} // namespace roda

#endif