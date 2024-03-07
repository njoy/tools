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
           typename ReferenceType >
class AnyInputIteratorConcept : public AnyIteratorConcept {

public:

    virtual bool operator==( const AnyIteratorConcept& ) const = 0;
    virtual bool operator!=( const AnyIteratorConcept& ) const = 0;
    virtual ReferenceType operator*() const = 0;
};

/**
 *  @brief The AnyForwardIteratorConcept base class
 *
 *  This base class represents the minimal interface that must be provided by
 *  an AnyIterator that models a forward iterator.
 */
template < typename ValueType,
           typename ReferenceType >
class AnyForwardIteratorConcept :
  public AnyInputIteratorConcept< ValueType, ReferenceType > {};

/**
 *  @brief The AnyBidirectionalIteratorConcept base class
 *
 *  This base class represents the minimal interface that must be provided by
 *  an AnyIterator that models a bidirectional iterator.
 */
template < typename ValueType,
           typename ReferenceType >
class AnyBidirectionalIteratorConcept :
  public AnyForwardIteratorConcept< ValueType, ReferenceType > {

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
           typename ReferenceType >
class AnyRandomAccessIteratorConcept :
  public AnyBidirectionalIteratorConcept< ValueType, ReferenceType > {

public:

  virtual ReferenceType operator[]( std::ptrdiff_t ) const = 0;

  virtual std::ptrdiff_t operator-( const AnyRandomAccessIteratorConcept& ) const = 0;

  virtual bool operator<(const AnyRandomAccessIteratorConcept& ) const = 0;
  virtual bool operator>(const AnyRandomAccessIteratorConcept& ) const = 0;

  virtual bool operator<=(const AnyRandomAccessIteratorConcept& ) const = 0;
  virtual bool operator>=(const AnyRandomAccessIteratorConcept& ) const = 0;

  virtual AnyRandomAccessIteratorConcept& operator+=( std::ptrdiff_t ) = 0;
  virtual AnyRandomAccessIteratorConcept& operator-=( std::ptrdiff_t ) = 0;
};
