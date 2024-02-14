#ifndef NJOY_TOOLS_STD20_TYPE_TRAITS
#define NJOY_TOOLS_STD20_TYPE_TRAITS

// system includes
#include <type_traits>

// other includes

namespace njoy {
namespace tools {
namespace std20 {

template < typename T >
struct remove_cvref {
  using type = std::remove_cv_t< std::remove_reference_t< T > >;
};

template < typename T >
using remove_cvref_t = typename remove_cvref< T >::type;

template < typename T >
struct type_identity {
  using type = T;
};

template < typename T >
using type_identity_t = typename type_identity< T >::type;

} // std20 namespace
} // tools namespace
} // njoy namespace

#endif
