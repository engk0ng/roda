#ifndef RODA_FILTER_ITERATOR_HPP
#define RODA_FILTER_ITERATOR_HPP

#include <iterator>
#include <type_traits>

namespace roda {

template<typename Iterator, typename Predicate>
class FilterIterator {
public:
  using iterator_category =
   typename std::iterator_traits<Iterator>::iterator_category;
  using value_type = typename std::iterator_traits<Iterator>::value_type;
  using difference_type =
   typename std::iterator_traits<Iterator>::difference_type;
  using pointer = typename std::iterator_traits<Iterator>::pointer;
  using reference = typename std::iterator_traits<Iterator>::reference;

  FilterIterator(Iterator it, Predicate p)
  : m_iter{it}
  , m_pred{p}
  {
    if(static_cast<bool>(m_iter) && !m_pred(*m_iter)) {
      ++(*this);
    }
  }

  template<class OtherIterator,
           std::enable_if_t<std::is_convertible_v<OtherIterator, Iterator>>>
  FilterIterator(const FilterIterator<OtherIterator, Predicate>& it)
  : FilterIterator{it.base(), it.predicate()}
  {
  }

  FilterIterator&
  operator++()
  {
    do {
      ++m_iter;
    } while(static_cast<bool>(m_iter) && !m_pred(*m_iter));

    return *this;
  }

  FilterIterator
  operator++(int)
  {
    auto retval = *this;
    ++(*this);
    return retval;
  }

  explicit operator bool()
  {
    return static_cast<bool>(m_iter);
  }

  Predicate
  predicate() const
  {
    return m_pred;
  }

  const Iterator&
  base() const
  {
    return m_iter;
  }

  reference operator*() const
  {
    return *m_iter;
  }

private:
  Iterator m_iter;
  Predicate m_pred;
};

} // namespace roda

#endif
