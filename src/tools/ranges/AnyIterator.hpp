#ifndef NJOY_TOOLS_RANGES_ANYITERATOR
#define NJOY_TOOLS_RANGES_ANYITERATOR

// system includes

// other includes
#include "tools/concepts/IsIterator.hpp"

namespace njoy {
namespace tools {
namespace ranges {

template< typename AnyIterator,  typename OtherAnyIterator, typename = void >
struct IsCompatibleAnyIterator : std::false_type {};

template< template < typename... > class AnyIteratorType,
          typename IteratorCategory, typename OtherIteratorCategory,
          typename ValueType, typename ReferenceType,
          typename PointerType, typename DifferenceType >
struct IsCompatibleAnyIterator<
         AnyIteratorType< IteratorCategory, ValueType, ReferenceType,
                          PointerType, DifferenceType >,
         AnyIteratorType< OtherIteratorCategory, ValueType, ReferenceType,
                          PointerType, DifferenceType >,
        std::enable_if< std::is_base_of< IteratorCategory,
                                         OtherIteratorCategory >::value > > : std::true_type {};

// AnyIterator concepts for different iterator categories (base classes)
#include "tools/ranges/AnyIterator/AnyIteratorConcept.hpp"

// AnyIterator models for different iterator categories (concept implementation)
#include "tools/ranges/AnyIterator/AnyIteratorModel.hpp"

/**
 *  @brief The AnyIterator class to type erase iterators
 */
template < typename IteratorCategory, typename ValueType,
           typename ReferenceType = ValueType&,
           typename PointerType = ValueType*,
           typename DifferenceType = std::ptrdiff_t >
class AnyIterator {

  AnyIteratorConcept* ptr_;

  template < typename Iterator >
  AnyIterator( const std::input_iterator_tag&, Iterator&& iter ) :
    ptr_( new AnyInputIteratorModel< typename std::decay< Iterator >::type,
                                     ValueType >( std::forward< Iterator >( iter ) ) ) {}

  template < typename Iterator >
  AnyIterator( const std::forward_iterator_tag&, Iterator&& iter ) :
    ptr_( new AnyForwardIteratorModel< typename std::decay< Iterator >::type,
                                       ValueType >( std::forward< Iterator >( iter ) ) ) {}

  template < typename Iterator >
  AnyIterator( const std::bidirectional_iterator_tag&, Iterator&& iter ) :
    ptr_( new AnyBidirectionalIteratorModel< typename std::decay< Iterator >::type,
                                             ValueType >( std::forward< Iterator >( iter ) ) ) {}

  template < typename Iterator >
  AnyIterator( const std::random_access_iterator_tag&, Iterator&& iter ) :
    ptr_( new AnyRandomAccessIteratorModel< typename std::decay< Iterator >::type,
                                            ValueType >( std::forward< Iterator >( iter ) ) ) {}

public:

  using value_type = ValueType;
  using reference = ReferenceType;
  using pointer = PointerType;
  using difference_type = DifferenceType;
  using iterator_category = IteratorCategory;

  /* constructor */

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

    using IteratorType = AnyInputIteratorConcept< ValueType, ReferenceType, PointerType >;
    return *static_cast< IteratorType& >( *this->ptr_ );
  }

  constexpr pointer operator->() const {

    using IteratorType = AnyInputIteratorConcept< ValueType, ReferenceType, PointerType >;
    return static_cast< IteratorType& >( *this->ptr_ );
  }

  constexpr bool operator==( const AnyIterator& right ) const {

    using IteratorType = AnyInputIteratorConcept< ValueType, ReferenceType, PointerType >;
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

  constexpr AnyIterator& operator--( void ) {

    static_assert(
      concepts::IsBidirectionalIterator< AnyIterator >::value == true,
      "the operator-- method can only be made available for bidirectional iterators" );

    using IteratorType = AnyBidirectionalIteratorConcept< ValueType, ReferenceType, PointerType >;
    --( static_cast< IteratorType& >( *this->ptr_ ) );
    return *this;
  }

  constexpr AnyIterator operator--( int ) {

    static_assert(
      concepts::IsBidirectionalIterator< AnyIterator >::value == true,
      "the operator-- method can only be made available for bidirectional iterators" );

    AnyIterator iter = *this;
    --( *this );
    return iter;
  }

  constexpr AnyIterator& operator+=( difference_type i ) {

    static_assert(
      concepts::IsRandomAccessIterator< AnyIterator >::value == true,
      "the operator+= method can only be made available for random access iterators" );

    using IteratorType = AnyRandomAccessIteratorConcept< ValueType, ReferenceType, PointerType, DifferenceType >;
    static_cast< IteratorType& >( *this->ptr_ ) += i;
    return *this;
  }

  constexpr AnyIterator& operator-=( difference_type i ) {

    static_assert(
      concepts::IsRandomAccessIterator< AnyIterator >::value == true,
      "the operator-= method can only be made available for random access iterators" );

    using IteratorType = AnyRandomAccessIteratorConcept< ValueType, ReferenceType, PointerType, DifferenceType >;
    static_cast< IteratorType& >( *this->ptr_ ) -= i;
    return *this;
  }

  constexpr difference_type operator-( const AnyIterator& right ) const {

    static_assert(
      concepts::IsRandomAccessIterator< AnyIterator >::value == true,
      "the operator-= method can only be made available for random access iterators" );

    using IteratorType = AnyRandomAccessIteratorConcept< ValueType, ReferenceType, PointerType, DifferenceType >;
    return static_cast< IteratorType& >( *this->ptr_ ) - static_cast< IteratorType& >( *right.ptr_ );
  }

  friend constexpr bool operator<( const AnyIterator& left,
                                   const AnyIterator& right) {

    static_assert(
      concepts::IsRandomAccessIterator< AnyIterator >::value == true,
      "the operator< method can only be made available for random access iterators" );

    using IteratorType = AnyRandomAccessIteratorConcept< ValueType, ReferenceType, PointerType >;
    return static_cast< IteratorType& >( *left.ptr_ ) < static_cast< IteratorType& >( *right.ptr_ );
  }

  friend constexpr bool operator>( const AnyIterator& left,
                                   const AnyIterator& right ) {

    static_assert(
      concepts::IsRandomAccessIterator< AnyIterator >::value == true,
      "the operator> method can only be made available for random access iterators" );

    return right < left;
  }

  friend constexpr bool operator<=( const AnyIterator& left,
                                    const AnyIterator& right ) {

    static_assert(
      concepts::IsRandomAccessIterator< AnyIterator >::value == true,
      "the operator<= method can only be made available for random access iterators" );

    return !( left > right );
  }

  friend constexpr bool operator>=( const AnyIterator& left,
                                    const AnyIterator& right ) {

    static_assert(
      concepts::IsRandomAccessIterator< AnyIterator >::value == true,
      "the operator>= method can only be made available for random access iterators" );

    return !( left < right );
  }

  ~AnyIterator() {

    delete this->ptr_;
  }
};

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
