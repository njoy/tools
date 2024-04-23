// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/iterator.hpp"

// other includes
#include "tools/std20/ranges.hpp"

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "reverse_iterator" ) {

  using Iter = std20::reverse_iterator< int* >;
  CHECK( std::is_default_constructible_v< Iter > );
  CHECK( std::is_copy_constructible_v< Iter > );
  CHECK( std::is_move_constructible_v< Iter > );
  CHECK( std::is_copy_assignable_v< Iter > );
  CHECK( std::is_move_assignable_v< Iter > );
  CHECK( std::is_constructible_v< Iter, int* > );

  int array[2] = { 1, 2 };
  std20::reverse_iterator< int* > i = std20::rbegin( array );
  std20::reverse_iterator< int* > arrayend = std20::rend( array );

  CHECK( i != arrayend );
  CHECK( (arrayend - i) == 2 );
  CHECK( (i - arrayend) == -2 );
  auto j = i;
  CHECK( j == i );
  CHECK( (j - i) == 0 );
  j = arrayend;
  CHECK( j != i );
  CHECK( j == arrayend );
  j = std::next(i);
  CHECK( j != i );
  CHECK( j != arrayend );
  CHECK( (arrayend - j) == 1 );
  CHECK( (j - i) == 1 );
  CHECK( (i - j) == -1 );
  ++j;
  CHECK( j == arrayend );
  CHECK( (arrayend - j) == 0 );
  j = i;
  CHECK( j == i );
  CHECK( (j - arrayend) == -2 );
  CHECK( (j - i) == 0 );

  std::vector< int > vector = { 0, 1, 2, 3, 4 };
	auto begin = std20::make_reverse_iterator( std::end( vector ) );
	auto second = std20::make_reverse_iterator( --std::end( vector ) );
	auto end = std20::make_reverse_iterator( std::begin( vector ) );

  unsigned int counter = 0;
  for ( auto iter = begin; iter != end; ++iter ) {

    ++counter;
  }
  CHECK( 5 == counter );

  for ( auto iter = end; iter != begin; --iter ) {

    --counter;
  }
  CHECK( 0 == counter );

  CHECK( 5 == std::distance( begin, end ) );
  CHECK( begin != end );

  CHECK( 4 == *begin );
  CHECK( 3 == *second );

  CHECK( 4 == begin[0] );
  CHECK( 3 == begin[1] );
  CHECK( 2 == begin[2] );
  CHECK( 1 == begin[3] );
  CHECK( 0 == begin[4] );

  auto iter = begin;
  iter += 1;
  CHECK( second == iter );
  iter -= 1;
  CHECK( begin == iter );

  CHECK( second == ++begin );
  CHECK( begin == --begin );

  iter = begin;
  CHECK( begin == iter++ );
  CHECK( second == iter );
  CHECK( second == iter-- );
  CHECK( begin == iter );

  iter = begin + 1;
  CHECK( second == iter );
  iter = second - 1;
  CHECK( begin == iter );
  iter = 1 + begin;
  CHECK( second == iter );

  CHECK( second >= begin );
  CHECK( second > begin );
  CHECK( begin <= second );
  CHECK( begin < second );
} // SCENARIO
