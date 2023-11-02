#ifndef NJOY_TOOLS_RANGES_VIEWBASE
#define NJOY_TOOLS_RANGES_VIEWBASE

// system includes
#include <stdexcept>

// other includes
#include "tools/concepts/Requires.hpp"
#include "tools/concepts/IsRange.hpp"
#include "tools/concepts/IsIterator.hpp"

namespace njoy {
namespace tools {
namespace ranges {

/**
 *
 *  @brief A base class for views
 *
 *  This CRTP base class assumes the Derived range has a begin() and end()
 *  method that define the begin and end iterator to the Derived range.
 */
template < typename Derived >
class ViewBase {

  constexpr Derived& derived() noexcept {

    return static_cast< Derived& >( *this );
  }

  constexpr const Derived& derived() const noexcept {

    return static_cast< const Derived& >( *this );
  }

public:

  /* methods */

  /**
   *  @brief Return whether or not the view is empty
   */
  template < typename Range = Derived,
             concepts::Requires< true, concepts::IsForwardIterator,
                                 typename Range::iterator > = true >
  constexpr bool empty() const noexcept {

    return this->derived().begin() == this->derived().end();
  }

  /**
   *  @brief Return whether or not the view is empty
   */
  template < typename Range = Derived,
             concepts::Requires< true, concepts::IsForwardIterator,
                                 typename Range::iterator > = true >
  constexpr explicit operator bool() const noexcept {

    return this->empty();
  }

  /**
   *  @brief Return the size of the iterator view
   */
  template < typename Range = Derived,
             concepts::Requires< true, concepts::IsForwardIterator,
                                 typename Range::iterator > = true >
  constexpr std::size_t size() const noexcept {

    return std::distance( this->derived().begin(), this->derived().end() );
  }

  /**
   *  @brief Return the reference to the front element of the view
   */
  template < typename Range = Derived,
             concepts::Requires< true, concepts::IsForwardIterator,
                                 typename Range::iterator > = true >
  constexpr decltype(auto) front() const noexcept {

    return *( this->derived().begin() );
  }

  /**
   *  @brief Return the reference to the back element of the view
   */
  template < typename Range = Derived,
             concepts::Requires< true, concepts::IsBidirectionalIterator,
                                 typename Range::iterator > = true >
  constexpr decltype(auto) back() const noexcept {

    return *( std::prev( this->derived().end() ) );
  }

  /**
   *  @brief Return an element at a given index
   *
   *  No range checking is performed.
   *
   *  @param[in] i    the index
   */
  template < typename Range = Derived,
             concepts::Requires< true, concepts::IsRandomAccessIterator,
                                 typename Range::iterator > = true >
  constexpr decltype(auto) operator[]( std::size_t i ) const noexcept {

    return *( std::next( this->derived().begin(), i ) );
  }

  /**
   *  @brief Return an element at a given index with range checking
   *
   *  @param[in] i    the index
   */
  template < typename Range = Derived,
             concepts::Requires< true, concepts::IsRandomAccessIterator,
                                 typename Range::iterator > = true >
  constexpr decltype(auto) at( std::size_t i ) const {

    if ( i >= this->size() ) {

      throw std::out_of_range( "Index out of range: " +
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
  template < typename Container,
             typename Range = Derived,
             concepts::Requires< true, concepts::IsInputIterator,
                                 typename Range::iterator > = true >
  constexpr bool operator==( const Container& other ) const {

    return std::equal( this->derived().begin(), this->derived().end(),
                       other.begin(), other.end() );
  }

  /**
   *  @brief Verify if the IteratorView is equal to another container
   *
   *  @param[in] other    the other container to compare with
   */
  template < typename Container,
             typename Range = Derived,
             concepts::Requires< true, concepts::IsInputIterator,
                                 typename Range::iterator > = true >
  constexpr bool operator!=( const Container& other ) const {

    return !this->operator==( other );
  }

  // the following code is added to make compiler errors more comprehensible

  template < typename Range = Derived,
             concepts::Requires< false, concepts::IsForwardIterator,
                                 typename Range::iterator > = true >
  constexpr bool empty() const noexcept {

    static_assert(
      concepts::IsForwardIterator< typename Range::iterator >::value == true,
      "the empty() method can only be made available for forward iterators" );
    return true;
  }

  template < typename Range = Derived,
             concepts::Requires< false, concepts::IsForwardIterator,
                                 typename Range::iterator > = true >
  constexpr explicit operator bool() const noexcept {

    static_assert(
      concepts::IsForwardIterator< typename Range::iterator >::value == true,
      "the operator bool() method can only be made available for forward iterators" );
    return true;
  }

  template < typename Range = Derived,
             concepts::Requires< false, concepts::IsForwardIterator,
                                 typename Range::iterator > = true >
  constexpr std::size_t size() const noexcept {

    static_assert(
      concepts::IsForwardIterator< typename Range::iterator >::value == true,
      "the size() method can only be made available for forward iterators" );
    return std::size_t{};
  }

  template < typename Range = Derived,
             concepts::Requires< false, concepts::IsForwardIterator,
                                 typename Range::iterator > = true >
  constexpr decltype(auto) front() const noexcept {

    static_assert(
      concepts::IsBidirectionalIterator< typename Range::iterator >::value == true,
      "the front() method can only be made available for bidirectional iterators" );
    return typename Derived::value_type{};
  }

  template < typename Range = Derived,
             concepts::Requires< false, concepts::IsBidirectionalIterator,
                                 typename Range::iterator > = true >
  constexpr decltype(auto) back() const noexcept {

    static_assert(
      concepts::IsBidirectionalIterator< typename Range::iterator >::value == true,
      "the back() method can only be made available for bidirectional iterators" );
    return typename Derived::value_type{};
  }

  template < typename Range = Derived,
             concepts::Requires< false, concepts::IsRandomAccessIterator,
                                 typename Range::iterator > = true >
  constexpr decltype(auto) operator[]( std::size_t i ) const {

    static_assert(
      concepts::IsRandomAccessIterator< typename Range::iterator >::value == true,
      "the operator[] method can only be made available for random access iterators" );
    return typename Derived::value_type{};
  }

  template < typename Range = Derived,
             concepts::Requires< false, concepts::IsRandomAccessIterator,
                                 typename Range::iterator > = true >
  constexpr decltype(auto) at( std::size_t i ) const {

    static_assert(
      concepts::IsRandomAccessIterator< typename Range::iterator >::value == true,
      "the at() method can only be made available for random access iterators" );
    return typename Derived::value_type{};
  }
};

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
