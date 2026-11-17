#ifndef NJOY_TOOLS_APPLYPERMUTATION
#define NJOY_TOOLS_APPLYPERMUTATION

// system includes

// other includes

namespace njoy {
namespace tools {

  /**
   *  @brief Apply a permutation on a given range
   *
   *  This code was adopted from the boost algorithm library.
   *
   *  This function applies a permutation to a given range using permutation
   *  indices from another range. The size of both ranges is assumed to be the
   *  same (no check is performed to this effect) and the value type of the
   *  permutation range should be the difference type of the range to be
   *  permuted (there is no check to this effect either).
   *
   *  The permutation indices also need to follow a few rules: they need to be
   *  within 0 and the size of the range to be permutated, and each value can
   *  only appear once. For example, to generate a permutation range based on
   *  the order of another vector, we can use this code snippet:
   *
   *     std::vector< std::size_t > order( vector.size() );
   *     std::iota( order.begin(), order.end(), 0 );
   *     std::sort( order.begin(), order.end(),
   *                [&] ( auto&& i, auto&& j )
   *                    { return vector[i] < vector[j]; } );
   *
   *  The resulting permutation order follows all the rules given above.
   *
   *  The permutation range is modified by this function so this range cannot
   *  be reused.
   *
   *  @param[in] begin    the iterator to the start of the range
   *  @param[in] end      the iterator to the end of the range
   *  @param[in] pbegin   the iterator to the permutation range
   */
  template< typename Iterator, typename PIterator >
  void apply_permutation( Iterator begin, const Iterator end, PIterator pbegin ) {

    using difference_type = typename std::iterator_traits< PIterator >::value_type;

    difference_type size = std::distance( begin, end );

    for ( difference_type i = 0; i < size; ++i ) {

      difference_type current = i;
      while ( i != pbegin[ current ] ) {

        difference_type next = pbegin[ current ];
        std::swap( begin[ current ], begin[ next ] );
        pbegin[ current ] = current;
        current = next;
      }
      pbegin[ current ] = current;
    }
  }

  /**
   *  @brief Apply a permutation on a given range
   *
   *  This code was adopted from the boost algorithm library.
   *
   *  This function applies a permutation to a given range using permutation
   *  indices from another range. The size of both ranges is assumed to be the
   *  same (no check is performed to this effect) and the value type of the
   *  permutation range should be the difference type of the range to be
   *  permuted (there is no check to this effect either).
   *
   *  The permutation indices also need to follow a few rules: they need to be
   *  within 0 and the size of the range to be permutated, and each value can
   *  only appear once. For example, to generate a permutation range based on
   *  the order of another vector, we can use this code snippet:
   *
   *     std::vector< std::size_t > order( vector.size() );
   *     std::iota( order.begin(), order.end(), 0 );
   *     std::sort( order.begin(), order.end(),
   *                [&] ( auto&& i, auto&& j )
   *                    { return vector[i] < vector[j]; } );
   *
   *  The resulting permutation order follows all the rules given above.
   *
   *  The permutation range is modified by this function so this range cannot
   *  be reused.
   *
   *  @param[in] values    the range of values
   *  @param[in] indices   the permutation range
   */
  template< typename Range, typename PRange >
  void apply_permutation( Range& values, PRange& indices ) {

    apply_permutation( std::begin( values ), std::end( values ), std::begin( indices ) );
  }

} // tools namespace
} // njoy namespace

#endif
