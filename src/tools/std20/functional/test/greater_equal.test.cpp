// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/functional.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

// test code
struct Foo { };
int operator==( Foo, Foo ) noexcept { return 2; }
int operator!=( Foo, Foo ) { return 0; }
int operator<( Foo, Foo ) noexcept { return 0; }
int operator>( Foo, Foo ) { return 0; }
int operator<=( Foo, Foo ) { return 3; }
int operator>=( Foo, Foo ) { return 4; }

SCENARIO( "greater_equal" ) {

  std20::greater_equal f;

  CHECK( std::is_default_constructible_v< std20::greater_equal > );
  CHECK( std::is_copy_constructible_v< std20::greater_equal > );
  CHECK( std::is_move_constructible_v< std20::greater_equal > );
  CHECK( std::is_copy_assignable_v< std20::greater_equal > );
  CHECK( std::is_move_assignable_v< std20::greater_equal > );

  CHECK( std20::greater_equal{}( 99, 99.0 ) );
  CHECK( std20::greater_equal{}( 99.01, 99 ) );
  CHECK( ! std20::greater_equal{}( 99, 140 ) );

  int a[2]{};
  CHECK( f(&a, (void*)&a[0]) );
  CHECK( f((void*)&a[1], &a) );
  CHECK( f(&a + 1, (void*)(a + 1)) );
  CHECK( ! f(&a, (void*)(a + 1)) );

  Foo x;
  CHECK( f( x, x ) );
} // SCENARIO
