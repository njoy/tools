#ifndef NJOY_TOOLS_CONCEPTS_ISRANGE
#define NJOY_TOOLS_CONCEPTS_ISRANGE

// system includes
#include <type_traits>

// other includes

namespace njoy {
namespace tools {
namespace concepts {

  template< typename Range, typename = void >
  struct IsRange : std::false_type {};

  template< typename Range >
  struct IsRange< Range,
                  std::void_t< decltype( std::begin( std::declval< Range >() ) ),
                               decltype( std::end( std::declval< Range >() ) )
                             > > : std::true_type {};

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
