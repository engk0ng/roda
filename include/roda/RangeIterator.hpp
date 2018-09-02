#ifndef RODA_RANGE_ITERATOR_HPP
#define RODA_RANGE_ITERATOR_HPP

#include <iterator>
#include <type_traits>

namespace roda {

template<typename Iterator>
class RangeIterator {
public:
  using iterator_category =
   typename std::iterator_traits<Iterator>::iterator_category;
  using value_type = typename std::iterator_traits<Iterator>::value_type;
  using difference_type =
   typename std::iterator_traits<Iterator>::difference_type;
  using pointer = typename std::iterator_traits<Iterator>::pointer;
  using reference = typename std::iterator_traits<Iterator>::reference;

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

  reference operator*() const
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