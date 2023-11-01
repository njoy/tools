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

  template< typename Iterator, typename = void >
  struct IsIterator : std::false_type {};

  template< typename Iterator >
  struct IsIterator< Iterator,
                     std::void_t< iterator_category< Iterator > > > : std::true_type {};

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
