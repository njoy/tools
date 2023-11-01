#ifndef NJOY_TOOLS_CONCEPTS_ISITERATOR
#define NJOY_TOOLS_CONCEPTS_ISITERATOR

// system includes
#include <type_traits>

// other includes

namespace njoy {
namespace tools {
namespace concepts {

  template< typename Iterator >
  using iterator_category =
    typename std::iterator_traits< Iterator >::iterator_category;

  // sfinae structures for iterator objects

  template< typename Iterator, typename = void >
  struct IsIterator : std::false_type {};

  template< typename Iterator >
  struct IsIterator<
           Iterator,
           std::void_t< iterator_category< Iterator > > > : std::true_type {};

  // the following template aliases only work on iterators

  // sfinae structures for input iterator objects

  template< typename Iterator >
  using IsInputIterator =
    typename std::is_base_of< std::input_iterator_tag,
                              iterator_category< Iterator > >;

  // sfinae structures for output iterator objects

  template< typename Iterator >
  using IsOutputIterator =
    typename std::is_base_of< std::output_iterator_tag,
                              iterator_category< Iterator > >;

  // sfinae structures for forward iterator objects

  template< typename Iterator >
  using IsForwardIterator =
    typename std::is_base_of< std::forward_iterator_tag,
                              iterator_category< Iterator > >;

  // sfinae structures for bidirectional iterator objects

  template< typename Iterator >
  using IsBidirectionalIterator =
    typename std::is_base_of< std::bidirectional_iterator_tag,
                              iterator_category< Iterator > >;

  // sfinae structures for random access iterator objects

  template< typename Iterator >
  using IsRandomAccessIterator =
    typename std::is_base_of< std::random_access_iterator_tag,
                              iterator_category< Iterator > >;

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
