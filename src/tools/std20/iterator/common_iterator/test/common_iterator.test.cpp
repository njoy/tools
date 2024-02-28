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
  std20::common_iterator< std::vector< Foo >::iterator,
                          std::vector< Foo >::const_iterator > begin = values.begin(),
                                                               end = values.cend();
  CHECK( *begin == 1 );
  CHECK( begin->n == 1 );
  ++begin;
  CHECK( *begin == 2 );
  CHECK( begin->n == 2 );
  ++begin;
  CHECK( begin == end );
} // SCENARIO
