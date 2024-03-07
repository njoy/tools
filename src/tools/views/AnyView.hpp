#ifndef NJOY_TOOLS_RANGES_ANYVIEW
#define NJOY_TOOLS_RANGES_ANYVIEW

// system includes
#include <iterator>

// other includes
#include "tools/views/AnyIterator.hpp"
#include "tools/std20/views.hpp"

namespace njoy {
namespace tools {
namespace ranges {

/**
 *  @brief A type erased view class
 *
 *  It works on all types of iterators (input, forward, bidirectional and random).
 */
template < typename IteratorCategory, typename ValueType >
class AnyView : public nano::view_interface< AnyView< IteratorCategory, ValueType > > {

  /* type aliases */
  using Iterator = AnyIterator< IteratorCategory, ValueType >;
  using Sentinel = AnyIterator< IteratorCategory, ValueType >;
  using Range = nano::subrange< Iterator, Sentinel, nano::ranges::subrange_kind::sized >;

  Range range_;

public:

  /* constructor */

  constexpr AnyView() = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the iterator to the beginning of the view
   *  @param[in] end      the iterator to the end of the view
   */
  constexpr AnyView( Iterator begin, Iterator end ) :
    range_( std::move( begin ), std::move( end ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] container    the container or range to be type erased
   */
  template < typename Container >
  constexpr AnyView( Container&& container ) :
    AnyView( Iterator( container.begin() ), Iterator( container.end() ) ) {}

  Iterator begin() { return range_.begin(); }
  Iterator end() { return range_.end(); }
};

template < typename ValueType >
using AnyInputView = AnyView< std::input_iterator_tag, ValueType >;
template < typename ValueType >
using AnyForwardView = AnyView< std::forward_iterator_tag, ValueType >;
template < typename ValueType >
using AnyBidirectionalView = AnyView< std::bidirectional_iterator_tag, ValueType >;
template < typename ValueType >
using AnyRandomAccessView = AnyView< std::random_access_iterator_tag, ValueType >;

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
