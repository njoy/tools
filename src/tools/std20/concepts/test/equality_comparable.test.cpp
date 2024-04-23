// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

// test code
struct Foo {

	friend bool operator==( const Foo&, const Foo& );
	friend bool operator!=( const Foo&, const Foo& );
};

struct Bar {};

SCENARIO( "equality_comparable and equality_comparable_with" ) {

  CHECK( std20::equality_comparable< int > );
  CHECK( std20::equality_comparable< int& > );
  CHECK( std20::equality_comparable< const int& > );
  CHECK( std20::equality_comparable< int&& > );
  CHECK( std20::equality_comparable< Foo > );
  CHECK( std20::equality_comparable< Foo& > );
  CHECK( std20::equality_comparable< const Foo& > );
  CHECK( std20::equality_comparable< Foo&& > );
  CHECK( std20::equality_comparable< std::nullptr_t > );
  CHECK( ! std20::equality_comparable< void > );
  CHECK( ! std20::equality_comparable< Bar > );

  CHECK( std20::equality_comparable_with< int, int > );
  CHECK( std20::equality_comparable_with< int, int& > );
  CHECK( std20::equality_comparable_with< int&, const int& > );
  CHECK( std20::equality_comparable_with< Foo, Foo > );
  CHECK( std20::equality_comparable_with< Foo, Foo& > );
  CHECK( std20::equality_comparable_with< Foo&, const Foo& > );
  CHECK( ! std20::equality_comparable_with< Foo, Bar > );
} // SCENARIO
