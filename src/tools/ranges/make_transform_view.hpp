#ifndef NJOY_TOOLS_RANGES_MAKE_TRANSFORM_VIEW
#define NJOY_TOOLS_RANGES_MAKE_TRANSFORM_VIEW

// system includes

// other includes
#include "tools/ranges/TransformView.hpp"

namespace njoy {
namespace tools {
namespace ranges {

/**
 *  @brief Make an TransformView based on a container and a transformation
 *
 *  @param[in] container         the container
 *  @param[in] transformation    the transformation to be applied
 */
template < typename Container, typename Transformation >
constexpr auto make_transform_view( Container&& container,
                                    Transformation transformation ) {

  return TransformView( container, std::move( transformation ) );
}

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
