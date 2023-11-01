#ifndef NJOY_TOOLS_CONCEPTS_REQUIRES
#define NJOY_TOOLS_CONCEPTS_REQUIRES

// system includes
#include <type_traits>

// other includes

namespace njoy {
namespace tools {
namespace concepts {

  template< bool TrueFalse, template< typename...> class Concept, typename... T >
  using Requires = typename std::enable_if< Concept< T... >::value == TrueFalse, bool >::type;

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
