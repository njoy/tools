/**
 *  @brief The AnyInputIteratorModel class
 *
 *  Implementation of the AnyIterator model for input iterators.
 */
template < typename InputIterator, typename ValueType,
           typename ReferenceType = ValueType&,
           typename PointerType = ValueType* >
class AnyInputIteratorModel final :
  public AnyInputIteratorConcept< ValueType, ReferenceType, PointerType >
{

  /* fields */
  InputIterator iter_;

public:

  using value_type = ValueType;
  using reference = ReferenceType;
  using pointer = PointerType;

  /* constructors */
  AnyInputIteratorModel( InputIterator iter ) noexcept : iter_( iter ) {}

  /* methods */

  bool operator==( const AnyIteratorConcept& right ) const override {

    const AnyInputIteratorModel* p_right = static_cast< const AnyInputIteratorModel* >( &right );
    return this->iter_ == p_right->iter_;
  }

  bool operator!=( const AnyIteratorConcept& right ) const override {

    return !( this->operator==( right ) );
  }

  reference operator*() const override {

    return *this->iter_;
  }

  pointer operator->() const override {

    return std::addressof( *this->iter_ );
  }

  AnyInputIteratorModel& operator++() override {

    ++this->iter_;
    return *this;
  }

  AnyIteratorConcept* copy() const override {

    return new AnyInputIteratorModel( this->iter_ );
  }
};

/**
 *  @brief The AnyForwardIteratorModel class
 *
 *  Implementation of the AnyIterator model for forward iterators.
 */
template < typename ForwardIterator, typename ValueType,
           typename ReferenceType = ValueType&,
           typename PointerType = ValueType* >
class AnyForwardIteratorModel final :
  public AnyForwardIteratorConcept< ValueType, ReferenceType, PointerType >
{

  /* fields */
  ForwardIterator iter_;

public:

  using value_type = ValueType;
  using reference = ReferenceType;
  using pointer = PointerType;

  /* constructors */
  AnyForwardIteratorModel( ForwardIterator iter ) noexcept : iter_( iter ) {}

  /* methods */

  bool operator==( const AnyIteratorConcept& right ) const override {

    const AnyForwardIteratorModel* p_right = static_cast< const AnyForwardIteratorModel* >( &right );
    return this->iter_ == p_right->iter_;
  }

  bool operator!=( const AnyIteratorConcept& right ) const override {

    return !( this->operator==( right ) );
  }

  reference operator*() const override {

    return *this->iter_;
  }

  pointer operator->() const override {

    return std::addressof( *this->iter_ );
  }

  AnyForwardIteratorModel& operator++() override {

    ++this->iter_;
    return *this;
  }

  AnyIteratorConcept* copy() const override {

    return new AnyForwardIteratorModel( this->iter_ );
  }
};

/**
 *  @brief The AnyBidirectionalIteratorModel class
 *
 *  Implementation of the AnyIterator model for bidirectional iterators.
 */
template < typename BidirectionalIterator, typename ValueType,
           typename ReferenceType = ValueType&,
           typename PointerType = ValueType* >
class AnyBidirectionalIteratorModel final :
  public AnyBidirectionalIteratorConcept< ValueType, ReferenceType, PointerType >
{

  /* fields */
  BidirectionalIterator iter_;

public:

  using value_type = ValueType;
  using reference = ReferenceType;
  using pointer = PointerType;

  /* constructors */
  AnyBidirectionalIteratorModel( BidirectionalIterator iter ) noexcept : iter_( iter ) {}

  /* methods */

  bool operator==( const AnyIteratorConcept& right ) const override {

    const AnyBidirectionalIteratorModel* p_right = static_cast< const AnyBidirectionalIteratorModel* >( &right );
    return this->iter_ == p_right->iter_;
  }

  bool operator!=( const AnyIteratorConcept& right ) const override {

    return !( this->operator==( right ) );
  }

  reference operator*() const override {

    return *this->iter_;
  }

  pointer operator->() const override {

    return std::addressof( *this->iter_ );
  }

  AnyBidirectionalIteratorModel& operator++() override {

    ++this->iter_;
    return *this;
  }

  AnyBidirectionalIteratorModel& operator--() override {

    --this->iter_;
    return *this;
  }

  AnyIteratorConcept* copy() const override {

    return new AnyBidirectionalIteratorModel( this->iter_ );
  }
};

/**
 *  @brief The AnyRandomAccessIteratorModel class
 *
 *  Implementation of the AnyIterator model for random access iterators.
 */
template < typename RandomAccessIterator, typename ValueType,
           typename ReferenceType = ValueType&,
           typename PointerType = ValueType*,
           typename DifferenceType = std::ptrdiff_t >
class AnyRandomAccessIteratorModel final :
  public AnyRandomAccessIteratorConcept< ValueType, ReferenceType, PointerType, DifferenceType >
{

  /* type aliases */
  using Base = AnyRandomAccessIteratorConcept< ValueType, ReferenceType, PointerType, DifferenceType >;

  /* fields */
  RandomAccessIterator iter_;

public:

  using value_type = ValueType;
  using reference = ReferenceType;
  using pointer = PointerType;
  using difference_type = DifferenceType;

  /* constructors */
  AnyRandomAccessIteratorModel( RandomAccessIterator iter ) noexcept : iter_( iter ) {}

  /* methods */

  bool operator==( const AnyIteratorConcept& right ) const override {

    const AnyRandomAccessIteratorModel* p_right = static_cast< const AnyRandomAccessIteratorModel* >( &right );
    return this->iter_ == p_right->iter_;
  }

  bool operator!=( const AnyIteratorConcept& right ) const override {

    return !( this->operator==( right ) );
  }

  bool operator<( const Base& right ) const override {

    const AnyRandomAccessIteratorModel* p_right = static_cast< const AnyRandomAccessIteratorModel* >( &right );
    return this->iter_ < p_right->iter_;
  }

  bool operator<=( const Base& right ) const override {

    const AnyRandomAccessIteratorModel* p_right = static_cast< const AnyRandomAccessIteratorModel* >( &right );
    return this->iter_ <= p_right->iter_;
  }

  bool operator>( const Base& right ) const override {

    const AnyRandomAccessIteratorModel* p_right = static_cast< const AnyRandomAccessIteratorModel* >( &right );
    return this->iter_ > p_right->iter_;
  }

  bool operator>=( const Base& right ) const override {

    const AnyRandomAccessIteratorModel* p_right = static_cast< const AnyRandomAccessIteratorModel* >( &right );
    return this->iter_ >= p_right->iter_;
  }

  reference operator*() const override {

    return *this->iter_;
  }

  pointer operator->() const override {

    return std::addressof( *this->iter_ );
  }

  AnyRandomAccessIteratorModel& operator++() override {

    ++this->iter_;
    return *this;
  }

  AnyRandomAccessIteratorModel& operator--() override {

    --this->iter_;
    return *this;
  }

  reference operator[]( difference_type i ) const override {

    return this->iter_[i];
  }

  AnyRandomAccessIteratorModel& operator+=( difference_type i ) override {

    this->iter_ += i;
    return *this;
  }

  AnyRandomAccessIteratorModel& operator-=( difference_type i ) override {

    this->iter_ -= i;
    return *this;
  }

  difference_type operator-( const Base& right ) const override {

    const AnyRandomAccessIteratorModel* p_right = static_cast< const AnyRandomAccessIteratorModel* >( &right );
    return this->iter_ - p_right->iter_;
  }

  AnyIteratorConcept* copy() const override {

    return new AnyRandomAccessIteratorModel( this->iter_ );
  }
};
