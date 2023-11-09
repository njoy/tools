/**
 *  @brief The AnyIteratorConcept base class
 *
 *  This base class represents the minimal interface that must be provided by
 *  all AnyIterator implementations.
 */
class AnyIteratorConcept {

public:

    /* methods */

    virtual AnyIteratorConcept* copy() const = 0;

    virtual AnyIteratorConcept& operator++() = 0;

    virtual ~AnyIteratorConcept() = default;
};

/**
 *  @brief The AnyInputIteratorConcept base class
 *
 *  This base class represents the minimal interface that must be provided by
 *  an AnyIterator that models an input iterator.
 */
template < typename ValueType,
           typename ReferenceType = ValueType&,
           typename PointerType = ValueType* >
class AnyInputIteratorConcept : public AnyIteratorConcept {

public:

    virtual bool operator==( const AnyIteratorConcept& ) const = 0;
    virtual bool operator!=( const AnyIteratorConcept& ) const = 0;
    virtual ReferenceType operator*() const = 0;
    virtual PointerType operator->() const = 0;
};

/**
 *  @brief The AnyForwardIteratorConcept base class
 *
 *  This base class represents the minimal interface that must be provided by
 *  an AnyIterator that models a forward iterator.
 */
template < typename ValueType,
           typename ReferenceType = ValueType&,
           typename PointerType = ValueType* >
class AnyForwardIteratorConcept :
  public AnyInputIteratorConcept< ValueType, ReferenceType, PointerType > {};

/**
 *  @brief The AnyBidirectionalIteratorConcept base class
 *
 *  This base class represents the minimal interface that must be provided by
 *  an AnyIterator that models a bidirectional iterator.
 */
template < typename ValueType,
           typename ReferenceType = ValueType&,
           typename PointerType = ValueType* >
class AnyBidirectionalIteratorConcept :
  public AnyForwardIteratorConcept< ValueType, ReferenceType, PointerType > {

public:

  virtual AnyBidirectionalIteratorConcept& operator--() = 0;
};

/**
 *  @brief The AnyRandomAccessIteratorConcept base class
 *
 *  This base class represents the minimal interface that must be provided by
 *  an AnyIterator that models a random access iterator.
 */
template < typename ValueType,
           typename ReferenceType = ValueType&,
           typename PointerType = ValueType*,
           typename DifferenceType = std::ptrdiff_t >
class AnyRandomAccessIteratorConcept :
  public AnyBidirectionalIteratorConcept< ValueType, ReferenceType, PointerType > {

public:

  virtual ReferenceType operator[]( DifferenceType ) const = 0;

  virtual DifferenceType operator-( const AnyRandomAccessIteratorConcept& ) const = 0;

  virtual bool operator<(const AnyRandomAccessIteratorConcept& ) const = 0;
  virtual bool operator>(const AnyRandomAccessIteratorConcept& ) const = 0;

  virtual bool operator<=(const AnyRandomAccessIteratorConcept& ) const = 0;
  virtual bool operator>=(const AnyRandomAccessIteratorConcept& ) const = 0;

  virtual AnyRandomAccessIteratorConcept& operator+=( DifferenceType ) = 0;
  virtual AnyRandomAccessIteratorConcept& operator-=( DifferenceType ) = 0;
};
