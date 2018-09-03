#ifndef RODA_TYPE_TRAITS_HPP
#define RODA_TYPE_TRAITS_HPP

#include <iterator>
#include <type_traits>

namespace roda {

/**
 * iterator_category
 */
template<typename Iterator, class = void>
struct iterator_category {
  using type = typename Iterator::IteratorCategory;
};

template<typename Iterator>
struct iterator_category<
 Iterator,
 std::void_t<typename std::iterator_traits<Iterator>::iterator_category>> {
  using type = typename std::iterator_traits<Iterator>::iterator_category;
};

template<typename Iterator>
using iterator_category_t = typename iterator_category<Iterator>::type;

/**
 * iterator_value_type
 */
template<typename Iterator, class = void>
struct iterator_value_type {
  using type = typename Iterator::ValueType;
};

template<typename Iterator>
struct iterator_value_type<
 Iterator,
 std::void_t<typename std::iterator_traits<Iterator>::value_type>> {
  using type = typename std::iterator_traits<Iterator>::value_type;
};

template<typename Iterator>
using iterator_value_type_t = typename iterator_value_type<Iterator>::type;

/**
 * iterator_difference_type
 */
template<typename Iterator, class = void>
struct iterator_difference_type {
  using type = typename Iterator::DifferenceType;
};

template<typename Iterator>
struct iterator_difference_type<
 Iterator,
 std::void_t<typename std::iterator_traits<Iterator>::difference_type>> {
  using type = typename std::iterator_traits<Iterator>::difference_type;
};

template<typename Iterator>
using iterator_difference_type_t =
 typename iterator_difference_type<Iterator>::type;

/**
 * iterator_pointer
 */
template<typename Iterator, class = void>
struct iterator_pointer {
  using type = typename Iterator::Pointer;
};

template<typename Iterator>
struct iterator_pointer<
 Iterator,
 std::void_t<typename std::iterator_traits<Iterator>::pointer>> {
  using type = typename std::iterator_traits<Iterator>::pointer;
};

template<typename Iterator>
using iterator_pointer_t = typename iterator_pointer<Iterator>::type;

/**
 * iterator_reference
 */
template<typename Iterator, class = void>
struct iterator_reference {
  using type = typename Iterator::Reference;
};

template<typename Iterator>
struct iterator_reference<
 Iterator,
 std::void_t<typename std::iterator_traits<Iterator>::reference>> {
  using type = typename std::iterator_traits<Iterator>::reference;
};

template<typename Iterator>
using iterator_reference_t = typename iterator_reference<Iterator>::type;

} // namespace roda

#endif