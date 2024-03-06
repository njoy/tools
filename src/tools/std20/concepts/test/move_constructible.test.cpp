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

struct MoveOnlyFoo {

	MoveOnlyFoo() = default;

	MoveOnlyFoo( const MoveOnlyFoo& ) = delete;
	MoveOnlyFoo& operator=( const MoveOnlyFoo& ) = delete;

	MoveOnlyFoo( MoveOnlyFoo&&) = default;
	MoveOnlyFoo& operator=( MoveOnlyFoo&& ) = default;
};

struct CopyOnlyFoo {

	CopyOnlyFoo() = default;

	CopyOnlyFoo( const CopyOnlyFoo& ) = default;
	CopyOnlyFoo& operator=( const CopyOnlyFoo& ) = default;

	CopyOnlyFoo( CopyOnlyFoo&&) = delete;
	CopyOnlyFoo& operator=( CopyOnlyFoo&& ) = delete;
};

SCENARIO( "move_constructible" ) {

  CHECK( std20::move_constructible< Foo > );
  CHECK( std20::move_constructible< MoveOnlyFoo > );
  CHECK( ! std20::move_constructible< NonMovableFoo > );
  CHECK( ! std20::move_constructible< CopyOnlyFoo > );
  CHECK( std20::move_constructible< Foo& > );
  CHECK( std20::move_constructible< MoveOnlyFoo& > );
  CHECK( std20::move_constructible< NonMovableFoo& > );
  CHECK( std20::move_constructible< CopyOnlyFoo& > );
  CHECK( std20::move_constructible< Foo&& > );
  CHECK( std20::move_constructible< MoveOnlyFoo&& > );
  CHECK( std20::move_constructible< NonMovableFoo&& > );
  CHECK( std20::move_constructible< CopyOnlyFoo&& > );
  CHECK( std20::move_constructible< const NonMovableFoo& > );
  CHECK( std20::move_constructible< const CopyOnlyFoo& > );
  CHECK( std20::move_constructible< const NonMovableFoo&& > );
  CHECK( std20::move_constructible< const CopyOnlyFoo&& > );

  CHECK( std20::move_constructible< int > );
  CHECK( std20::move_constructible< const int > );
  CHECK( std20::move_constructible< int& > );
  CHECK( std20::move_constructible< const int& > );
  CHECK( std20::move_constructible< int&& > );
  CHECK( std20::move_constructible< const int&& > );
  CHECK( std20::move_constructible< double > );
  CHECK( ! std20::move_constructible< void > );
  CHECK( std20::move_constructible< void* > );
  CHECK( std20::move_constructible< const void* > );
  CHECK( ! std20::move_constructible< void() > );
  CHECK( ! std20::move_constructible< int[2] > );
} // SCENARIO
