#ifndef NJOY_UTILITY_TRANSFORMITERATOR
#define NJOY_UTILITY_TRANSFORMITERATOR

// system includes
#include <iterator>

// other includes

namespace njoy {
namespace tools {
namespace ranges {

/**
 *
 *  @brief An iterator class that applies a transformation when dereferencing
 *         the iterator
 */
template < typename Iterator, typename Transformation >
class TransformIterator {

  /* fields */
  Iterator iter_;
  Transformation transform_;

public:

  using iterator_category = typename Iterator::iterator_category;
  using difference_type = typename Iterator::difference_type;
  using value_type = decltype( std::declval< Transformation >()( std::declval< typename Iterator::value_type >() ) );
  using pointer = value_type*;
  using reference = value_type;

  /* constructor */

  constexpr TransformIterator() = delete;

  /**
   *  @brief TransformIterator constructor
   *
   *  @param[in] iter              the iterator
   *  @param[in] transformation    the transformation to be applied
   */
  constexpr TransformIterator( Iterator iter, Transformation transformation ) :
    iter_( std::move( iter ) ), transform_( std::move( transformation ) ) {}

  /* methods */

  constexpr reference operator*() const {

    return this->transform_( *this->iter_ );
  }

  constexpr reference operator[]( difference_type i ) const {

    return this->transform_( this->iter_[i] );
  }

  constexpr TransformIterator& operator+=( difference_type i ) {

    this->iter_ += i;
    return *this;
  }

  constexpr TransformIterator& operator-=( difference_type i ) {

    this->iter_ -= i;
    return *this;
  }

  constexpr TransformIterator& operator++( void ) {

    ++this->iter_;
    return *this;
  }

  constexpr TransformIterator operator++( int ) {

    return TransformIterator( this->iter_++, transform_ );
  }

  constexpr TransformIterator& operator--( void ) {

    --this->iter_;
    return *this;
  }

  constexpr TransformIterator operator--( int ) {

    return TransformIterator( this->iter_--, this->transform_ );
  }

  friend constexpr TransformIterator operator+( difference_type i,
                                                TransformIterator iter ) {

    return TransformIterator( iter.iter_ + i, iter.transform_ );
  }

  friend constexpr TransformIterator operator+( TransformIterator iter,
                                                difference_type i ) {

    return TransformIterator( iter.iter_ + i, iter.transform_ );
  }

  friend constexpr TransformIterator operator-( TransformIterator iter,
                                                difference_type i ) {

    return TransformIterator( iter.iter_ - i, iter.transform_ );
  }

  friend constexpr difference_type operator-( const TransformIterator& left,
                                              const TransformIterator& right ) {

    return left.iter_ - right.iter_;
  }

  friend constexpr bool operator==( const TransformIterator& left,
                                    const TransformIterator& right ) {

    return left.iter_ == right.iter_;
  };

  friend constexpr bool operator!=( const TransformIterator& left,
                                    const TransformIterator& right ) {

    return !( left == right );
  };

  friend constexpr bool operator<( const TransformIterator& left,
                                   const TransformIterator& right) {

      return left.iter_ < right.iter_;
  }

  friend constexpr bool operator>( const TransformIterator& left,
                                   const TransformIterator& right ) {

      return right < left;
  }

  friend constexpr bool operator<=( const TransformIterator& left,
                                    const TransformIterator& right ) {

      return !( right < left );
  }

  friend constexpr bool operator>=( const TransformIterator& left,
                                    const TransformIterator& right ) {

      return !( left < right );
  }
};

} // ranges namespace
} // tools namespace
} // njoy namespace

#endif
