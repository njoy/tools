#ifndef NJOY_TOOLS_RANGES_ITERATORVIEW
#define NJOY_TOOLS_RANGES_ITERATORVIEW

// system includes
#include <iterator>
#include <stdexcept>

// other includes

namespace njoy {
namespace tools {
namespace ranges {

/**
 *
 *  @brief A simple iterator based view class
 *
 *  Currently only defined for random access iterators.
 */
template < class Iterator,
           std::enable_if_t<
               std::is_same< typename std::iterator_traits< Iterator >::iterator_category,
                             std::random_access_iterator_tag >::value, bool > = true >
class IteratorView {

public:

  using value_type = typename std::iterator_traits< Iterator >::value_type;
  using difference_type = typename std::iterator_traits< Iterator >::difference_type;
  using size_type = std::size_t;
  using pointer = typename std::iterator_traits< Iterator >::pointer;
  using reference = typename std::iterator_traits< Iterator >::reference;
  using const_reference = const reference;
  using iterator = Iterator;

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
   *  @brief IteratorView constructor
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
   *  @brief Return the reference to the front element of the view
   */
  constexpr decltype(auto) front() const noexcept {

    return *( this->begin() );
  }

  /**
   *  @brief Return the reference to the back element of the view
   */
  constexpr decltype(auto) back() const noexcept {

    return *( std::prev( this->end() ) );
  }

  /**
   *  @brief Return whether or not the view is empty
   */
  constexpr bool empty() const noexcept { return this->begin() == this->end(); }

  /**
   *  @brief Return the size of the iterator view
   */
  constexpr size_type size() const noexcept {

    return std::distance( this->begin(), this->end() );
  }

  /**
   *  @brief Return an element at a given index
   *
   *  No range checking is performed.
   *
   *  @param[in] i    the index
   */
  constexpr decltype(auto) operator[]( size_type i ) const noexcept {

    return *( std::next( this->begin(), i ) );
  }

  /**
   *  @brief Return an element at a given index with range checking
   *
   *  @param[in] i    the index
   */
  constexpr decltype(auto) at( size_type i ) const {

    if ( i >= this->size() ) {

      throw std::out_of_range( "Index out of range in IteratorView: " +
                               std::to_string( i ) + " >= size (" +
                               std::to_string( this->size() ) + ")" );
    }
    return this->operator[]( i );
  }

  /**
   *  @brief Verify if the IteratorView is equal to another container
   *
   *  @param[in] other    the other container to compare with
   */
  template < typename Container >
  constexpr bool operator==( const Container& other ) const {

    return std::equal( this->begin(), this->end(), other.begin(), other.end() );
  }

  /**
   *  @brief Verify if the IteratorView is equal to another container
   *
   *  @param[in] other    the other container to compare with
   */
  template < typename Container >
  constexpr bool operator!=( const Container& other ) const {

    return !this->operator==( other );
  }
};

/**
 *  @brief Make an IteratorView based on two iterators
 *
 *  @param[in] begin    the iterator to the beginning of the view
 *  @param[in] end      the iterator to the end of the view
 */
template < typename Iterator >
constexpr auto make_view( Iterator&& begin, Iterator&& end ) {

  return IteratorView< Iterator >{ std::forward< Iterator >( begin ),
                                   std::forward< Iterator >( end ) };
}

/**
 *  @brief Make an IteratorView based on a container
 *
 *  @param[in] container    the container
 */
template < typename Container >
constexpr auto make_view( Container& container ) {

  return IteratorView< typename Container::iterator >{ container.begin(),
                                                       container.end() };
}

/**
 *  @brief Make an IteratorView based on a container
 *
 *  @param[in] container    the container
 */
template < typename Container >
constexpr auto make_view( const Container& container ) {

  return IteratorView< typename Container::const_iterator >{ container.cbegin(),
                                                             container.cend() };
}

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
