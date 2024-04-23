#ifndef NJOY_TOOLS_RANGES_ANYVIEW
#define NJOY_TOOLS_RANGES_ANYVIEW

// system includes
#include <iterator>

// other includes
#include "tools/views/AnyIterator.hpp"
#include "tools/std20/views.hpp"

namespace njoy {
namespace tools {
namespace views {

/**
 *  @brief A type erased view class
 *
 *  It works on all types of iterators (input, forward, bidirectional and random).
 */
template < typename IteratorCategory, typename ReferenceType >
class AnyView :
  public njoy::tools::std20::ranges::view_interface< AnyView< IteratorCategory, ReferenceType > > {

  /* type aliases */
  using Iterator = AnyIterator< IteratorCategory, ReferenceType >;
  using Sentinel = AnyIterator< IteratorCategory, ReferenceType >;
  using Range = njoy::tools::std20::ranges::subrange< Iterator, Sentinel,
                                                      njoy::tools::std20::ranges::subrange_kind::sized >;

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
    range_( std::move( begin ), std::move( end ),
            std::distance( begin, end ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] container    the container or range to be type erased
   */
  template < typename Container >
  constexpr AnyView( Container&& container ) :
    AnyView( Iterator( container.begin() ), Iterator( container.end() ) ) {}

  /**
   *  @brief Return an iterator to the beginning of the view
   */
  Iterator begin() { return range_.begin(); }

  /**
   *  @brief Return an iterator to the beginning of the view
   */
  Iterator end() { return range_.end(); }
};

template < typename ReferenceType >
using AnyInputView = AnyView< std::input_iterator_tag, ReferenceType >;
template < typename ReferenceType >
using AnyForwardView = AnyView< std::forward_iterator_tag, ReferenceType >;
template < typename ReferenceType >
using AnyBidirectionalView = AnyView< std::bidirectional_iterator_tag, ReferenceType >;
template < typename ReferenceType >
using AnyRandomAccessView = AnyView< std::random_access_iterator_tag, ReferenceType >;

} // views namespace
} // tools namespace
} // njoy namespace

#endif
