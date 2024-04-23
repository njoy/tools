// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

// test code
struct Foo {};

struct Bar {

  Bar(int) { }
  Bar& operator=( const Bar& ) { return *this; }
  Bar& operator=( int ) { return *this; }
  void operator=( void* ) {}
};

SCENARIO( "assignable_from" ) {

  CHECK( ! std20::assignable_from< void, void > );
  CHECK( ! std20::assignable_from< void*, int* > );
  CHECK( std20::assignable_from< void*&, int* > );
  CHECK( ! std20::assignable_from< void*&, const int* > );
  CHECK( std20::assignable_from< const void*&, const int* > );
  CHECK( ! std20::assignable_from< char, char > );
  CHECK( std20::assignable_from< char&, char > );
  CHECK( ! std20::assignable_from< float, float > );
  CHECK( std20::assignable_from< float&, double > );
  CHECK( std20::assignable_from< int*&, int* > );
  CHECK( std20::assignable_from< int&, int& > );
  CHECK( std20::assignable_from< int&, int&& > );
  CHECK( ! std20::assignable_from< int&&, int > );
  CHECK( ! std20::assignable_from< const int&, int > );
  CHECK( ! std20::assignable_from< const int&, int& > );
  CHECK( ! std20::assignable_from< const int&, const int > );
  CHECK( ! std20::assignable_from< const int&, const int& > );
  CHECK( ! std20::assignable_from< int(&)[], int(&)[] > );
  CHECK( ! std20::assignable_from< int(&)[], int > );
  CHECK( ! std20::assignable_from< int(&)[2], int(&)[2] > );
  CHECK( ! std20::assignable_from< int(), int() > );
  CHECK( ! std20::assignable_from< int(*)(), int(*)() > );
  CHECK( std20::assignable_from< int(*&)(), int(*)() > );
  CHECK( std20::assignable_from< int(*&)(), std::nullptr_t > );
  CHECK( std20::assignable_from< int(*&)(), int(*)() noexcept > );
  CHECK( std20::assignable_from< int(*&)(), int(&)() noexcept > );
  CHECK( ! std20::assignable_from< int(&)(), std::nullptr_t > );
  CHECK( ! std20::assignable_from< int(&)(), int(&)() noexcept > );

  CHECK( ! std20::assignable_from< Foo, Foo > );
  CHECK( std20::assignable_from< Foo&, Foo > );
  CHECK( ! std20::assignable_from< Foo, Foo& > );
  CHECK( std20::assignable_from< Foo&, const Foo& > );

  CHECK( std20::assignable_from< Bar&, Bar > );
  CHECK( std20::assignable_from< Bar&, const Bar& > );
  CHECK( std20::assignable_from< Bar&, int > );
  CHECK( ! std20::assignable_from< Bar&, void* > );
  CHECK( ! std20::assignable_from< Bar&, std::nullptr_t > );
} // SCENARIO
