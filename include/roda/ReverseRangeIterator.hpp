#ifndef RODA_REVERSE_RANGE_ITERATOR_HPP
#define RODA_REVERSE_RANGE_ITERATOR_HPP

#include "type_traits.hpp"

namespace roda {

template<typename Iterator>
class ReverseRangeIterator {
public:
  using IteratorCategory = iterator_category_t<Iterator>;
  using ValueType = iterator_value_type_t<Iterator>;
  using DifferenceType = iterator_difference_type_t<Iterator>;
  using Pointer = iterator_pointer_t<Iterator>;
  using Reference = iterator_reference_t<Iterator>;

  ReverseRangeIterator(Iterator begin, Iterator end)
  : m_iter{begin}
  , m_end{end}
  {
  }

  template<typename Range,
           typename = decltype(std::rbegin(std::declval<Range>()),
                               std::rend(std::declval<Range>()),
                               (void)0)>
  explicit ReverseRangeIterator(Range& range)
  : ReverseRangeIterator{std::rbegin(range), std::rend(range)}
  {
  }

  ReverseRangeIterator&
  operator++()
  {
    ++m_iter;
    return *this;
  }

  ReverseRangeIterator
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
ReverseRangeIterator(Range& range)
 ->ReverseRangeIterator<std::conditional_t<std::is_const_v<Range>,
                                    typename Range::const_reverse_iterator,
                                    typename Range::reverse_iterator>>;

} // namespace roda

#endif