// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

// test code
struct Foo {};
struct Bar { int i; };

struct NonMovableFoo {

  NonMovableFoo( NonMovableFoo&& ) = delete;
};

struct SwappableFoo {

  SwappableFoo( SwappableFoo&& ) = delete;
  friend void swap( SwappableFoo&, SwappableFoo& ) {}
};

struct ProxyFoo {

  ProxyFoo( Foo& ) {}
  friend void swap( ProxyFoo, ProxyFoo ) {}
};

SCENARIO( "swappable and swappable_with" ) {

  CHECK( std20::swappable< int > );
  CHECK( std20::swappable< int& > );

  CHECK( std20::swappable< Foo > );
  CHECK( std20::swappable< Bar > );
  CHECK( ! std20::swappable< NonMovableFoo > );
  CHECK( std20::swappable< SwappableFoo > );
  CHECK( std20::swappable< ProxyFoo > );
  CHECK( ! std20::swappable< const Foo > );
  CHECK( ! std20::swappable< const Bar > );
  CHECK( ! std20::swappable< const NonMovableFoo > );
  CHECK( ! std20::swappable< const SwappableFoo > );

  CHECK( ! std20::swappable_with< int, int > );
  CHECK( std20::swappable_with< int&, int& > );
  CHECK( ! std20::swappable_with< int*, int* > );
  CHECK( ! std20::swappable_with< int&, const int& > );
  CHECK( ! std20::swappable_with< const int&, const int& > );
  CHECK( ! std20::swappable_with< int&, long& > );

  CHECK( ! std20::swappable_with< NonMovableFoo&, NonMovableFoo& > );
  CHECK( std20::swappable_with< SwappableFoo&, SwappableFoo& > );
  CHECK( std20::swappable_with< Foo&, Foo& > );
//  CHECK( std20::swappable_with< ProxyFoo&, Foo& > );
//  CHECK( std20::swappable_with< Foo&, ProxyFoo& > );
  CHECK( std20::swappable_with< ProxyFoo&, ProxyFoo& > );
} // SCENARIO
