#ifndef NJOY_TOOLS_RANGES_ITERATORVIEW
#define NJOY_TOOLS_RANGES_ITERATORVIEW

// system includes
#include <iterator>

// other includes
#include "tools/ranges/ViewBase.hpp"

namespace njoy {
namespace tools {
namespace ranges {

/**
 *
 *  @brief A simple iterator based view class
 *
 *  It works on all types of iterators (input, forward, bidirectional and random).
 */
template < typename Iterator >
class IteratorView : public ViewBase< IteratorView< Iterator > > {

public:

  using value_type = typename std::iterator_traits< Iterator >::value_type;
  using difference_type = typename std::iterator_traits< Iterator >::difference_type;
  using size_type = std::size_t;
  using pointer = typename std::iterator_traits< Iterator >::pointer;
  using reference = typename std::iterator_traits< Iterator >::reference;
  using const_reference = const reference;
  using iterator = Iterator;
  using const_iterator = const Iterator;

private:

  /* fields */
  Iterator begin_;
  Iterator end_;

public:

  /* constructor */

  /**
   *  @brief Default constructor
   */
  constexpr IteratorView() : IteratorView( Iterator{}, Iterator{} ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the iterator to the beginning of the view
   *  @param[in] end      the iterator to the end of the view
   */
  constexpr IteratorView( Iterator begin, Iterator end ) :
    begin_( std::move( begin ) ), end_( std::move( end ) ) {}

  /* methods */

  /**
   *  @brief Return the begin iterator to the view
   */
  constexpr iterator begin() const noexcept { return begin_; }

  /**
   *  @brief Return the end iterator to the view
   */
  constexpr iterator end() const noexcept { return end_; }

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
 *  @brief Verify if the IteratorView is equal to another container
 *
 *  @param[in] other    the other container to compare with
 */
template < typename Container, typename Iterator >
constexpr bool operator==( const Container& left,
                           IteratorView< Iterator > right ) {

  return right == left;
}

/**
 *  @brief Verify if the IteratorView is equal to another container
 *
 *  @param[in] other    the other container to compare with
 */
template < typename Container, typename Iterator >
constexpr bool operator!=( const Container& left,
                           IteratorView< Iterator > right ) {

  return right != left;
}

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
