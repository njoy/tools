// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/iterator.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano::ranges;

// test code
struct Foo {

  int n;

  bool operator==( int value ) const { return value == n; }
};

SCENARIO( "common_iterator" ) {

  using Iter = std20::common_iterator< int*, const int* >;
  CHECK( std::is_default_constructible_v< Iter > );
  CHECK( std::is_copy_constructible_v< Iter > );
  CHECK( std::is_move_constructible_v< Iter > );
  CHECK( std::is_copy_assignable_v< Iter > );
  CHECK( std::is_move_assignable_v< Iter > );
  CHECK( std::is_constructible_v< Iter, int* > );
  CHECK( std::is_constructible_v< Iter, const int* > );

  std::vector< Foo > values = { {1}, {2} };
  using CommonVector = std20::common_iterator< std::vector< Foo >::iterator,
                                               std::vector< Foo >::const_iterator >;
  CommonVector begin = values.begin();
  CommonVector end = values.cend();

  CHECK( *begin == 1 );
  CHECK( begin->n == 1 );
  ++begin;
  CHECK( *begin == 2 );
  CHECK( begin->n == 2 );
  ++begin;
  CHECK( begin == end );

  int array[2] = { 1, 2 };
  std20::common_iterator< int*, const int* > i = std::begin( array );
  std20::common_iterator< int*, const int* > arrayend = std::cend( array );

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

  std::vector< int > vector = { 1, 2, 3, 4 };
  using Iterator = std20::common_iterator< std::vector< int >::iterator,
                                           std::vector< int >::const_iterator >;
  Iterator bvector = std::begin( vector );
  Iterator evector = std::end( vector );

  CHECK( bvector != evector );
  CHECK( evector - bvector > 0 );
} // SCENARIO
