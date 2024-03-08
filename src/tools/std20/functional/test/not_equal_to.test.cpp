// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/functional.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano::ranges;

// test code
struct Foo { };
int operator==( Foo, Foo ) noexcept { return 2; }
int operator!=( Foo, Foo ) { return 0; }
int operator<( Foo, Foo ) noexcept { return 0; }
int operator>( Foo, Foo ) { return 0; }
int operator<=( Foo, Foo ) { return 3; }
int operator>=( Foo, Foo ) { return 4; }

SCENARIO( "not_equal_to" ) {

  std20::not_equal_to f;

  CHECK( std::is_default_constructible_v< std20::not_equal_to > );
  CHECK( std::is_copy_constructible_v< std20::not_equal_to > );
  CHECK( std::is_move_constructible_v< std20::not_equal_to > );
  CHECK( std::is_copy_assignable_v< std20::not_equal_to > );
  CHECK( std::is_move_assignable_v< std20::not_equal_to > );

  CHECK( ! std20::not_equal_to{}( 99, 99.0 ) );
  CHECK( std20::not_equal_to{}( 99, 99.01 ) );
  CHECK( std20::not_equal_to{}( 99, 140 ) );

// operator== and std::equal_to do not give the same result on intel classic
// this part of the test is therefore excluded for intel classic
#if ! defined(__INTEL_COMPILER)
  int a[2]{};
  CHECK( ! f( &a, (void*)&a[0] ) );
  CHECK( f( &a, (void*)&a[1] ) );
  CHECK( ! f( &a + 1, (void*)(a + 2) ) );
#endif

  Foo x;
  CHECK( ! f( x, x ) );
} // SCENARIO
