#ifndef NJOY_TOOLS_RANGES_ANYITERATOR
#define NJOY_TOOLS_RANGES_ANYITERATOR

// system includes

// other includes
#include "tools/std20/iterator.hpp"

namespace njoy {
namespace tools {
namespace views {

// AnyIterator concepts for different iterator categories (base classes)
#include "tools/views/AnyIterator/AnyIteratorConcept.hpp"

// AnyIterator models for different iterator categories (concept implementation)
#include "tools/views/AnyIterator/AnyIteratorModel.hpp"

/**
 *  @brief The AnyIterator class to type erase iterators
 */
template < typename IteratorCategory, typename ReferenceType >
class AnyIterator {

  /* fields */
  AnyIteratorConcept* ptr_;

  /* private constructors */
  template < typename Iterator >
  AnyIterator( const std::input_iterator_tag&, Iterator&& iter ) :
    ptr_( new AnyInputIteratorModel< typename std::decay< Iterator >::type,
                                     ReferenceType >( std::forward< Iterator >( iter ) ) ) {}

  template < typename Iterator >
  AnyIterator( const std::forward_iterator_tag&, Iterator&& iter ) :
    ptr_( new AnyForwardIteratorModel< typename std::decay< Iterator >::type,
                                       ReferenceType >( std::forward< Iterator >( iter ) ) ) {}

  template < typename Iterator >
  AnyIterator( const std::bidirectional_iterator_tag&, Iterator&& iter ) :
    ptr_( new AnyBidirectionalIteratorModel< typename std::decay< Iterator >::type,
                                             ReferenceType >( std::forward< Iterator >( iter ) ) ) {}

  template < typename Iterator >
  AnyIterator( const std::random_access_iterator_tag&, Iterator&& iter ) :
    ptr_( new AnyRandomAccessIteratorModel< typename std::decay< Iterator >::type,
                                            ReferenceType >( std::forward< Iterator >( iter ) ) ) {}

public:

  using value_type = std::decay_t< ReferenceType >;
  using reference = ReferenceType;
  using pointer = void;
  using difference_type = std::ptrdiff_t;
  using iterator_category = IteratorCategory;

  /* constructor */

  AnyIterator() : ptr_( nullptr ) {}
  AnyIterator( const AnyIterator& iter ) : ptr_( iter.ptr_->copy() ) {}
  AnyIterator( AnyIterator&& iter ) : ptr_( iter.ptr_->copy() ) {}

  AnyIterator& operator=( const AnyIterator& right ) {

    delete this->ptr_;
    this->ptr_ = right.ptr_->copy();
    return *this;
  }

  AnyIterator& operator=( AnyIterator&& right ) {

    delete this->ptr_;
    this->ptr_ = right.ptr_->copy();
    return *this;
  }

  template < typename Iterator >
  AnyIterator( Iterator iter ) :
    AnyIterator( IteratorCategory{}, std::move( iter ) ) {}

  /* methods */

  constexpr reference operator*() const {

    using IteratorType = AnyInputIteratorConcept< ReferenceType >;
    return *static_cast< IteratorType& >( *this->ptr_ );
  }

  constexpr bool operator==( const AnyIterator& right ) const {

    using IteratorType = AnyInputIteratorConcept< ReferenceType >;
    return static_cast< IteratorType& >( *this->ptr_ ) == static_cast< IteratorType& >( *right.ptr_ );
  }

  constexpr bool operator!=( const AnyIterator& right ) const {

    return !( this->operator==( right ) );
  }

  constexpr AnyIterator& operator++() {

    ++( *this->ptr_ );
    return *this;
  }

  constexpr AnyIterator operator++( int ) const {

    AnyIterator iter = *this;
    ++( *this->ptr_ );
    return iter;
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::bidirectional_iterator_tag> > >
  constexpr AnyIterator& operator--( void ) {

    using IteratorType = AnyBidirectionalIteratorConcept< ReferenceType >;
    --( static_cast< IteratorType& >( *this->ptr_ ) );
    return *this;
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::bidirectional_iterator_tag> > >
  constexpr AnyIterator operator--( int ) {

    AnyIterator iter = *this;
    --( *this );
    return iter;
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::random_access_iterator_tag> > >
  constexpr AnyIterator& operator+=( difference_type i ) {

    using IteratorType = AnyRandomAccessIteratorConcept< ReferenceType >;
    static_cast< IteratorType& >( *this->ptr_ ) += i;
    return *this;
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::random_access_iterator_tag> > >
  constexpr AnyIterator& operator-=( difference_type i ) {

    using IteratorType = AnyRandomAccessIteratorConcept< ReferenceType >;
    static_cast< IteratorType& >( *this->ptr_ ) -= i;
    return *this;
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::random_access_iterator_tag> > >
  constexpr difference_type operator-( const AnyIterator& right ) const {

    using IteratorType = AnyRandomAccessIteratorConcept< ReferenceType >;
    return static_cast< IteratorType& >( *this->ptr_ ) - static_cast< IteratorType& >( *right.ptr_ );
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::random_access_iterator_tag> > >
  friend constexpr AnyIterator operator+( difference_type i, const AnyIterator& iter ) {

    AnyIterator result = iter;
    result += i;
    return result;
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::random_access_iterator_tag> > >
  friend constexpr AnyIterator operator+( AnyIterator iter, difference_type i ) {

    AnyIterator result = iter;
    result += i;
    return result;
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::random_access_iterator_tag> > >
  friend constexpr AnyIterator operator-( AnyIterator iter, difference_type i ) {

    AnyIterator result = iter;
    result -= i;
    return result;
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::random_access_iterator_tag> > >
  constexpr reference operator[]( difference_type i ) const {

    using IteratorType = AnyRandomAccessIteratorConcept< ReferenceType >;
    return static_cast< IteratorType& >( *this->ptr_ )[i];
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::random_access_iterator_tag> > >
  friend constexpr bool operator<( const AnyIterator& left,
                                   const AnyIterator& right) {

    using IteratorType = AnyRandomAccessIteratorConcept< ReferenceType >;
    return static_cast< IteratorType& >( *left.ptr_ ) < static_cast< IteratorType& >( *right.ptr_ );
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::random_access_iterator_tag> > >
  friend constexpr bool operator>( const AnyIterator& left,
                                   const AnyIterator& right ) {

    return right < left;
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::random_access_iterator_tag> > >
  friend constexpr bool operator<=( const AnyIterator& left,
                                    const AnyIterator& right ) {

    return !( left > right );
  }

  template < typename Category = IteratorCategory,
             typename = std::enable_if_t< nano::derived_from< Category,
                                                              nano::random_access_iterator_tag> > >
  friend constexpr bool operator>=( const AnyIterator& left,
                                    const AnyIterator& right ) {

    return !( left < right );
  }

  ~AnyIterator() {

    delete this->ptr_;
  }
};

template < typename ReferenceType >
using AnyInputIterator = AnyIterator< std::input_iterator_tag, ReferenceType >;
template < typename ReferenceType >
using AnyForwardIterator = AnyIterator< std::forward_iterator_tag, ReferenceType >;
template < typename ReferenceType >
using AnyBidirectionalIterator = AnyIterator< std::bidirectional_iterator_tag, ReferenceType >;
template < typename ReferenceType >
using AnyRandomAccessIterator = AnyIterator< std::random_access_iterator_tag, ReferenceType >;

} // views namespace
} // tools namespace
} // njoy namespace

#endif
