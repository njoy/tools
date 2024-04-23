// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/algorithm.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

// test code
struct Foo {

  int i;
};

SCENARIO( "min" ) {

  int a[] = { 1, 2, 3 };
  std::vector< int > v = { 1, 2, 3 };
  Foo list[] = { Foo{1}, Foo{2}, Foo{3} };

  CHECK( 1 == std20::ranges::min( a ) );
  CHECK( 3 == std20::ranges::min( a, std::greater{} ) );

  CHECK( 1 == std20::ranges::min( v ) );
  CHECK( 3 == std20::ranges::min( v, std::greater{} ) );

  CHECK( 1 == std20::ranges::min( { 1, 2, 3 } ) );
  CHECK( 3 == std20::ranges::min( { 1, 2, 3 }, std::greater{} ) );

  Foo result = std20::ranges::min( list, std::less< int >{}, &Foo::i );
  CHECK( 1 == result.i );
  result = std20::ranges::min( list, std::greater< int >{}, &Foo::i );
  CHECK( 3 == result.i );
} // SCENARIO
