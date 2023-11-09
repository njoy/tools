#ifndef NJOY_TOOLS_RANGES_TRANSFORMVIEW
#define NJOY_TOOLS_RANGES_TRANSFORMVIEW

// system includes
#include <functional>
#include <iterator>

// other includes
#include "tools/ranges/ViewBase.hpp"
#include "tools/ranges/IteratorView.hpp"
#include "tools/ranges/make_view.hpp"

namespace njoy {
namespace tools {
namespace ranges {

/**
 *
 *  @brief A view that applies a transformation on every element of a range
 *
 *  To avoid copying containers like vectors, maps, etc. into the TransportView,
 *  an IteratorView using constant iterators into the container is created
 *  and stored inside the TransformView.
 */
template < typename BaseIterator, typename Transform >
class TransformView : public ViewBase< TransformView< BaseIterator, Transform > > {

  /* fields */
  IteratorView< BaseIterator > base_;
  Transform transform_;

public:

  #include "tools/ranges/TransformView/Iterator.hpp"

  using value_type = typename std::iterator_traits< Iterator >::value_type;
  using difference_type = typename std::iterator_traits< Iterator >::difference_type;
  using size_type = std::size_t;
  using pointer = typename std::iterator_traits< Iterator >::pointer;
  using reference = typename std::iterator_traits< Iterator >::reference;
  using const_reference = const reference;
  using iterator = Iterator;
  using const_iterator = const Iterator;

  /* constructor */

  /**
   *  @brief Default constructor
   */
  constexpr TransformView() = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] range        the range to be transformed
   *  @param[in] transform    the transformation to be applied to the range
   */
  constexpr TransformView( BaseIterator begin, BaseIterator end, Transform transform ) :
    base_( std::move( begin ), std::move( end ) ),
    transform_( std::move( transform ) ) {}

  /* methods */

  /**
   *  @brief Return the begin iterator to the view
   */
  constexpr iterator begin() const noexcept {

    return Iterator{ this->base_.begin(), this->transform_ };
  }

  /**
   *  @brief Return the end iterator to the view
   */
  constexpr iterator end() const noexcept {

    return Iterator{ this->base_.end(), this->transform_ };
  }

  /**
   *  @brief Return the begin iterator to the view
   */
  constexpr const_iterator cbegin() const noexcept { return this->begin(); }

  /**
   *  @brief Return the end iterator to the view
   */
  constexpr const_iterator cend() const noexcept { return this->end(); }
};


/**
 *  @brief Verify if the TransformView is equal to another container
 *
 *  @param[in] other    the other container to compare with
 */
template < typename Container, typename Range, typename Transform >
constexpr bool operator==( const Container& left,
                           TransformView< Range, Transform > right ) {

  return right == left;
}

/**
 *  @brief Verify if the TransformView is equal to another container
 *
 *  @param[in] other    the other container to compare with
 */
template < typename Container, typename Range, typename Transform >
constexpr bool operator!=( const Container& left,
                           TransformView< Range, Transform > right ) {

  return right != left;
}

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
