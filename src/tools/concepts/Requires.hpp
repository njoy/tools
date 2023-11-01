#ifndef NJOY_TOOLS_CONCEPTS_REQUIRES
#define NJOY_TOOLS_CONCEPTS_REQUIRES

// system includes
#include <type_traits>

// other includes

namespace njoy {
namespace tools {
namespace concepts {

  template< bool TrueFalse, template< typename...> class Concept, typename... T >
  using Requires = std::enable_if_t< Concept< T... >::value == TrueFalse, bool >;

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
