// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes
#include <string>

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano::ranges;

// test code
struct Foo {};

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

SCENARIO( "movable" ) {

  CHECK( std20::movable< Foo > );
  CHECK( std20::movable< MoveOnlyFoo > );
  CHECK( ! std20::movable< NonMovableFoo > );
  CHECK( ! std20::movable< CopyOnlyFoo > );
  CHECK( ! std20::movable< Foo& > );
  CHECK( ! std20::movable< MoveOnlyFoo& > );
  CHECK( ! std20::movable< NonMovableFoo& > );
  CHECK( ! std20::movable< CopyOnlyFoo& > );
  CHECK( ! std20::movable< Foo&& > );
  CHECK( ! std20::movable< MoveOnlyFoo&& > );
  CHECK( ! std20::movable< NonMovableFoo&& > );
  CHECK( ! std20::movable< CopyOnlyFoo&& > );
  CHECK( ! std20::movable< const Foo& > );
  CHECK( ! std20::movable< const MoveOnlyFoo& > );
  CHECK( ! std20::movable< const NonMovableFoo& > );
  CHECK( ! std20::movable< const CopyOnlyFoo& > );
  CHECK( ! std20::movable< const Foo&& > );
  CHECK( ! std20::movable< const MoveOnlyFoo&& > );
  CHECK( ! std20::movable< const NonMovableFoo&& > );
  CHECK( ! std20::movable< const CopyOnlyFoo&& > );

  CHECK( std20::movable< int > );
  CHECK( ! std20::movable< const int > );
  CHECK( ! std20::movable< int& > );
  CHECK( ! std20::movable< const int& > );
  CHECK( ! std20::movable< int&& > );
  CHECK( ! std20::movable< const int&& > );
  CHECK( std20::movable< double > );
  CHECK( ! std20::movable< void > );
  CHECK( ! std20::movable< void() > );
  CHECK( ! std20::movable< int[2] > );
} // SCENARIO
