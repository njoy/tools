// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes
#include <string>

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

// test code
struct Foo {

  ~Foo() noexcept {};
};

struct NonMovableFoo {

  NonMovableFoo( NonMovableFoo&& ) = delete;
};

struct CopyOnlyFoo {

	CopyOnlyFoo() = default;

	CopyOnlyFoo( const CopyOnlyFoo& ) = default;
	CopyOnlyFoo& operator=( const CopyOnlyFoo& ) = default;

	CopyOnlyFoo( CopyOnlyFoo&&) = delete;
	CopyOnlyFoo& operator=( CopyOnlyFoo&& ) = delete;
};

SCENARIO( "copy_constructible" ) {

  CHECK( std20::copy_constructible< Foo > );
  CHECK( ! std20::copy_constructible< NonMovableFoo > );
  CHECK( ! std20::copy_constructible< CopyOnlyFoo > );
  CHECK( std20::copy_constructible< NonMovableFoo& > );
  CHECK( std20::copy_constructible< CopyOnlyFoo& > );
  CHECK( ! std20::copy_constructible< NonMovableFoo&& > );
  CHECK( ! std20::copy_constructible< CopyOnlyFoo&& > );
  CHECK( std20::copy_constructible< const NonMovableFoo& > );
  CHECK( std20::copy_constructible< const CopyOnlyFoo& > );
  CHECK( ! std20::copy_constructible< const NonMovableFoo&& > );
  CHECK( ! std20::copy_constructible< const CopyOnlyFoo&& > );

  CHECK( ! std20::copy_constructible< void > );
  CHECK( std20::copy_constructible< void* > );
  CHECK( std20::copy_constructible< const void* > );
  CHECK( std20::copy_constructible< char > );
  CHECK( std20::copy_constructible< const float > );
  CHECK( std20::copy_constructible< int > );
  CHECK( std20::copy_constructible< int* > );
  CHECK( std20::copy_constructible< int& > );
  CHECK( ! std20::copy_constructible< int&& > );
  CHECK( std20::copy_constructible< const int > );
  CHECK( std20::copy_constructible< const int& > );
  CHECK( ! std20::copy_constructible< const int&& > );
  CHECK( ! std20::copy_constructible< int[] > );
  CHECK( ! std20::copy_constructible< int[2] > );
  CHECK( ! std20::copy_constructible< int() > );
  CHECK( std20::copy_constructible< int(*)() > );

  // fails on intel-classic compilers
  // CHECK( std20::copy_constructible< int(&)() > );
  // CHECK( std20::copy_constructible< int(&)() noexcept > );
} // SCENARIO
