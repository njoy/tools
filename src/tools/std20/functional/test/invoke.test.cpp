// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/functional.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano::ranges;

// test code
constexpr int f() noexcept { return 42; }
constexpr int g( int i ) { return i * i; }

struct Foo {

  int i = 42;

  constexpr int f() const { return i; }
};

constexpr struct {

  template < typename T >
  constexpr auto&& operator()( T&& arg ) const noexcept {

    return (decltype(arg)&&)arg;
  }
} bar{};


SCENARIO( "invoke" ) {

  CHECK( std20::invoke( f ) == 42 );
  CHECK( noexcept( std20::invoke( f ) == 42 ) );
  CHECK( std20::invoke( g, 2 ) == 4 );
  CHECK( std20::invoke( bar, 41 ) == 41 );
  CHECK( noexcept( std20::invoke( bar, 41 ) == 41 ) );

  int i = 40;
  CHECK( &std20::invoke( bar, i ) == &i );
  CHECK( noexcept( &std20::invoke( bar, i ) == &i ) );

  constexpr Foo x;
  CHECK( x.i == 42 );
  CHECK( x.f() == 42 );
  CHECK( std20::invoke( &Foo::i, x) == 42 );
  CHECK( std20::invoke( &Foo::i, &x) == 42 );
  CHECK( std20::invoke( &Foo::i, Foo{}) == 42 );
  CHECK( std20::invoke( &Foo::f, x) == 42 );
  CHECK( std20::invoke( &Foo::f, &x) == 42 );
  CHECK( std20::invoke( &Foo::f, Foo{}) == 42 );
} // SCENARIO
