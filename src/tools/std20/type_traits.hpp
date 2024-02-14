#ifndef NJOY_TOOLS_STD20_TYPE_TRAITS
#define NJOY_TOOLS_STD20_TYPE_TRAITS

// system includes
#include <type_traits>

// other includes

namespace njoy {
namespace tools {
namespace std20 {

// remove_cvref

template < typename T >
struct remove_cvref {
  using type = std::remove_cv_t< std::remove_reference_t< T > >;
};

template < typename T >
using remove_cvref_t = typename remove_cvref< T >::type;

// type_identity

template < typename T >
struct type_identity {
  using type = T;
};

template < typename T >
using type_identity_t = typename type_identity< T >::type;

// basic_common_reference

template < typename T, typename U, template < typename > typename TQual,
           template < typename > typename UQual>
struct basic_common_reference {};

// common_reference

template < typename... >
struct common_reference;

template < typename... Ts >
using common_reference_t = typename common_reference< Ts... >::type;

#include "tools/std20/type_traits/details/common_reference.hpp"

template <>
struct common_reference<> {};

template < typename T >
struct common_reference< T > {

    using type = T;
};

template < typename T1, typename T2 >
struct common_reference< T1, T2 > : detail::binary_common_ref<T1, T2> {};

template < typename T1, typename T2, typename... Rest >
struct common_reference< T1, T2, Rest... >
  : detail::multiple_common_reference< void, T1, T2, Rest... > {};

// is_bounded_array
// is_unbounded_array
// is_nothrow_convertible
// is_layout_compatible
// is_pointer_interconvertible_base_of
// is_pointer_interconvertible_with_class
// is_corresponding_member
// is_constant_evaluated

} // std20 namespace
} // tools namespace
} // njoy namespace

#endif
