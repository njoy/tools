// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

// test code
struct Foo {

	friend bool operator==( const Foo&, const Foo& );
	friend bool operator!=( const Foo&, const Foo& );
	friend bool operator<( const Foo&, const Foo& );
	friend bool operator>( const Foo&, const Foo& );
	friend bool operator<=( const Foo&, const Foo& );
	friend bool operator>=( const Foo&, const Foo& );
};

struct Bar {};

SCENARIO( "totally_ordered and totally_ordered_with" ) {

  CHECK( std20::totally_ordered< int > );
  CHECK( std20::totally_ordered< int& > );
  CHECK( std20::totally_ordered< const int& > );
  CHECK( std20::totally_ordered< int&& > );
  CHECK( std20::totally_ordered< Foo > );
  CHECK( std20::totally_ordered< Foo& > );
  CHECK( std20::totally_ordered< const Foo& > );
  CHECK( std20::totally_ordered< Foo&& > );
  CHECK( ! std20::totally_ordered< void > );
  CHECK( ! std20::totally_ordered< Bar > );

  CHECK( std20::totally_ordered_with< int, int > );
  CHECK( std20::totally_ordered_with< int, double > );
  CHECK( std20::totally_ordered_with< int, int& > );
  CHECK( std20::totally_ordered_with< int&, const int& > );
  CHECK( std20::totally_ordered_with< Foo, Foo > );
  CHECK( std20::totally_ordered_with< Foo, Foo& > );
  CHECK( std20::totally_ordered_with< Foo&, const Foo& > );
  CHECK( ! std20::totally_ordered_with< Foo, Bar > );
} // SCENARIO
