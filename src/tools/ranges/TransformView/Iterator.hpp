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

    static_assert(
      concepts::IsRandomAccessIterator< Iterator >::value == true,
      "the operator[] method can only be made available for random access iterators" );

    return this->transform_( this->iter_[i] );
  }

  constexpr Iterator& operator+=( difference_type i ) {

    static_assert(
      concepts::IsRandomAccessIterator< Iterator >::value == true,
      "the operator+= method can only be made available for random access iterators" );

    this->iter_ += i;
    return *this;
  }

  constexpr Iterator& operator-=( difference_type i ) {

    static_assert(
      concepts::IsRandomAccessIterator< Iterator >::value == true,
      "the operator-= method can only be made available for random access iterators" );

    this->iter_ -= i;
    return *this;
  }

  constexpr Iterator& operator++() {

    ++this->iter_;
    return *this;
  }

  constexpr Iterator operator++( int ) {

    return Iterator( this->iter_++, transform_ );
  }

  constexpr Iterator& operator--( void ) {

    static_assert(
      concepts::IsBidirectionalIterator< Iterator >::value == true,
      "the operator-- method can only be made available for bidirectional iterators" );

    --this->iter_;
    return *this;
  }

  constexpr Iterator operator--( int ) {

    static_assert(
      concepts::IsBidirectionalIterator< Iterator >::value == true,
      "the operator-- method can only be made available for bidirectional iterators" );

    return Iterator( this->iter_--, this->transform_ );
  }

  friend constexpr Iterator operator+( difference_type i, Iterator iter ) {

    static_assert(
      concepts::IsRandomAccessIterator< Iterator >::value == true,
      "the operator+ method can only be made available for random access iterators" );

    return Iterator( iter.iter_ + i, iter.transform_ );
  }

  friend constexpr Iterator operator+( Iterator iter, difference_type i ) {

    static_assert(
      concepts::IsRandomAccessIterator< Iterator >::value == true,
      "the operator+ method can only be made available for random access iterators" );

    return Iterator( iter.iter_ + i, iter.transform_ );
  }

  friend constexpr Iterator operator-( Iterator iter, difference_type i ) {

    static_assert(
      concepts::IsRandomAccessIterator< Iterator >::value == true,
      "the operator- method can only be made available for random access iterators" );

    return Iterator( iter.iter_ - i, iter.transform_ );
  }

  friend constexpr difference_type operator-( const Iterator& left,
                                              const Iterator& right ) {

    static_assert(
      concepts::IsRandomAccessIterator< Iterator >::value == true,
      "the operator- method can only be made available for random access iterators" );

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

    static_assert(
      concepts::IsRandomAccessIterator< Iterator >::value == true,
      "the operator< method can only be made available for random access iterators" );

    return left.iter_ < right.iter_;
  }

  friend constexpr bool operator>( const Iterator& left,
                                   const Iterator& right ) {

    static_assert(
      concepts::IsRandomAccessIterator< Iterator >::value == true,
      "the operator> method can only be made available for random access iterators" );

    return right < left;
  }

  friend constexpr bool operator<=( const Iterator& left,
                                    const Iterator& right ) {

    static_assert(
      concepts::IsRandomAccessIterator< Iterator >::value == true,
      "the at() method can only be made available for random access iterators" );

    return !( left > right );
  }

  friend constexpr bool operator>=( const Iterator& left,
                                    const Iterator& right ) {

    static_assert(
      concepts::IsRandomAccessIterator< Iterator >::value == true,
      "the operator>= method can only be made available for random access iterators" );

    return !( left < right );
  }
};
