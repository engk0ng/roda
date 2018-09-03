#ifndef RODA_RANGE_ITERATOR_HPP
#define RODA_RANGE_ITERATOR_HPP

#include "type_traits.hpp"

namespace roda {

template<typename Iterator>
class RangeIterator {
public:
  using IteratorCategory = iterator_category_t<Iterator>;
  using ValueType = iterator_value_type_t<Iterator>;
  using DifferenceType = iterator_difference_type_t<Iterator>;
  using Pointer = iterator_pointer_t<Iterator>;
  using Reference = iterator_reference_t<Iterator>;

  RangeIterator(Iterator begin, Iterator end)
  : m_iter{begin}
  , m_end{end}
  {
  }

  template<typename Range,
           typename = decltype(std::begin(std::declval<Range>()),
                               std::end(std::declval<Range>()),
                               (void)0)>
  explicit RangeIterator(Range& range)
  : RangeIterator{std::begin(range), std::end(range)}
  {
  }

  RangeIterator&
  operator++()
  {
    ++m_iter;
    return *this;
  }

  RangeIterator
  operator++(int)
  {
    auto retval = *this;
    ++(*this);
    return retval;
  }

  explicit operator bool() const
  {
    return m_iter != m_end;
  }

  Reference operator*() const
  {
    return *m_iter;
  }

private:
  Iterator m_iter;
  Iterator m_end;
};

template<typename Range, typename = void>
RangeIterator(Range& range)
 ->RangeIterator<std::conditional_t<std::is_const_v<Range>,
                                    typename Range::const_iterator,
                                    typename Range::iterator>>;

} // namespace roda

#endif