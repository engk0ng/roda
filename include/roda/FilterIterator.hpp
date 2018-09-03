#ifndef RODA_FILTER_ITERATOR_HPP
#define RODA_FILTER_ITERATOR_HPP

#include "type_traits.hpp"

namespace roda {

template<typename Iterator, typename Predicate>
class FilterIterator {
public:
  using IteratorCategory = iterator_category_t<Iterator>;
  using ValueType = iterator_value_type_t<Iterator>;
  using DifferenceType = iterator_difference_type_t<Iterator>;
  using Pointer = iterator_pointer_t<Iterator>;
  using Reference = iterator_reference_t<Iterator>;

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

  Reference operator*() const
  {
    return *m_iter;
  }

private:
  Iterator m_iter;
  Predicate m_pred;
};

} // namespace roda

#endif
