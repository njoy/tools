#ifndef NJOY_TOOLS_RANGES_MAKE_TRANSFORM_VIEW
#define NJOY_TOOLS_RANGES_MAKE_TRANSFORM_VIEW

// system includes

// other includes
#include "tools/ranges/IteratorView.hpp"
#include "tools/ranges/TransformView.hpp"

namespace njoy {
namespace tools {
namespace ranges {

/**
 *  @brief Make an TransformView based on iterators and a transformation
 *
 *  @param[in] begin             the iterator to the beginning of the view
 *  @param[in] end               the iterator to the end of the view
 *  @param[in] transformation    the transformation to be applied
 */
template < typename Iterator, typename Transformation >
constexpr auto make_transform_view( Iterator begin, Iterator end,
                                    Transformation transformation ) {

  return TransformView( std::move( begin ), std::move( end ),
                        std::move( transformation ) );
}

/**
 *  @brief Make an TransformView based on a container and a transformation
 *
 *  @param[in] container         the container
 *  @param[in] transformation    the transformation to be applied
 */
template < typename Container, typename Transformation >
constexpr auto make_transform_view( Container&& container,
                                    Transformation transformation ) {

  return TransformView( container.begin(), container.end(),
                        std::move( transformation ) );
}

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
