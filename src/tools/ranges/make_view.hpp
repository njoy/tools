#ifndef NJOY_TOOLS_RANGES_MAKE_VIEW
#define NJOY_TOOLS_RANGES_MAKE_VIEW

// system includes

// other includes
#include "tools/ranges/IteratorView.hpp"

namespace njoy {
namespace tools {
namespace ranges {

/**
 *  @brief Make an IteratorView based on two iterators
 *
 *  @param[in] begin    the iterator to the beginning of the view
 *  @param[in] end      the iterator to the end of the view
 */
template < typename Iterator >
constexpr auto make_view( Iterator&& begin, Iterator&& end ) {

  return IteratorView< Iterator >{ std::move( begin ), std::move( end ) };
}

/**
 *  @brief Make an IteratorView based on a container
 *
 *  @param[in] container    the container
 */
template < typename Container >
constexpr auto make_view( Container&& container ) {

  return make_view( container.begin(), container.end() );
}

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
