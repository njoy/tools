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
 *  @brief A simple iterator based view class
 *
 *  Currently only defined for random access iterators.
 */
template < typename Range, typename Transform >
class TransformView : public ViewBase< TransformView< Range, Transform > > {

  /* type aliases */
  using BaseIterator = typename Range::const_iterator;

  /* fields */
  IteratorView< BaseIterator > base_;
  Transform transform_;

public:

  class Iterator {

    BaseIterator iter_;
    std::reference_wrapper< const Transform > transform_;

  public:

    using iterator_category = typename BaseIterator::iterator_category;
    using difference_type = typename BaseIterator::difference_type;
    using value_type = decltype( std::declval< Transform >()( std::declval< typename BaseIterator::value_type >() ) );
    using pointer = value_type*;
    using reference = value_type;

    /* constructor */

    constexpr Iterator() = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] iter         the iterator
     *  @param[in] transform    the transformation to be applied
     */
    constexpr Iterator( BaseIterator iter, 
                        const Transform& transform ) :
      iter_( std::move( iter ) ), transform_( std::cref( transform ) ) {}

    /* methods */

    constexpr reference operator*() const {

      return this->transform_( *this->iter_ );
    }

    constexpr reference operator[]( difference_type i ) const {

      return this->transform_( this->iter_[i] );
    }

    constexpr Iterator& operator+=( difference_type i ) {

      this->iter_ += i;
      return *this;
    }

    constexpr Iterator& operator-=( difference_type i ) {

      this->iter_ -= i;
      return *this;
    }

    constexpr Iterator& operator++( void ) {

      ++this->iter_;
      return *this;
    }

    constexpr Iterator operator++( int ) {

      return Iterator( this->iter_++, transform_ );
    }

    constexpr Iterator& operator--( void ) {

      --this->iter_;
      return *this;
    }

    constexpr Iterator operator--( int ) {

      return Iterator( this->iter_--, this->transform_ );
    }

    friend constexpr Iterator operator+( difference_type i, Iterator iter ) {

      return Iterator( iter.iter_ + i, iter.transform_ );
    }

    friend constexpr Iterator operator+( Iterator iter, difference_type i ) {

      return Iterator( iter.iter_ + i, iter.transform_ );
    }

    friend constexpr Iterator operator-( Iterator iter, difference_type i ) {

      return Iterator( iter.iter_ - i, iter.transform_ );
    }

    friend constexpr difference_type operator-( const Iterator& left,
                                                const Iterator& right ) {

      return left.iter_ - right.iter_;
    }

    friend constexpr bool operator==( const Iterator& left,
                                      const Iterator& right ) {

      return left.iter_ == right.iter_;
    };

    friend constexpr bool operator!=( const Iterator& left,
                                      const Iterator& right ) {

      return !( left == right );
    };

    friend constexpr bool operator<( const Iterator& left,
                                     const Iterator& right) {

      return left.iter_ < right.iter_;
    }

    friend constexpr bool operator>( const Iterator& left,
                                     const Iterator& right ) {

      return right < left;
    }

    friend constexpr bool operator<=( const Iterator& left,
                                      const Iterator& right ) {

      return !( right < left );
    }

    friend constexpr bool operator>=( const Iterator& left,
                                      const Iterator& right ) {

      return !( left < right );
    }
  };

  using value_type = typename std::iterator_traits< Iterator >::value_type;
  using difference_type = typename std::iterator_traits< Iterator >::difference_type;
  using size_type = std::size_t;
  using pointer = typename std::iterator_traits< Iterator >::pointer;
  using reference = typename std::iterator_traits< Iterator >::reference;
  using const_reference = const reference;
  using iterator = Iterator;

  /* constructor */

  /**
   *  @brief Default constructor
   */
  constexpr TransformView() = delete;

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the iterator to the beginning of the view
   *  @param[in] end      the iterator to the end of the view
   */
  constexpr TransformView( const Range& range, Transform transform ) :
    base_( make_view( range ) ),
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
