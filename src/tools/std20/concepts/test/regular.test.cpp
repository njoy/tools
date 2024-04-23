// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes
#include <string>

// convenience typedefs
using namespace njoy::tools;

// test code
struct Foo {};

struct RegularFoo {

  friend bool operator==( const RegularFoo&, const RegularFoo& );
	friend bool operator!=( const RegularFoo&, const RegularFoo& );
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

SCENARIO( "regular" ) {

  CHECK( ! std20::regular< Foo > );
  CHECK( std20::regular< RegularFoo > );
  CHECK( ! std20::regular< MoveOnlyFoo > );
  CHECK( ! std20::regular< NonMovableFoo > );
  CHECK( ! std20::regular< CopyOnlyFoo > );
  CHECK( ! std20::regular< Foo& > );
  CHECK( ! std20::regular< MoveOnlyFoo& > );
  CHECK( ! std20::regular< NonMovableFoo& > );
  CHECK( ! std20::regular< CopyOnlyFoo& > );
  CHECK( ! std20::regular< Foo&& > );
  CHECK( ! std20::regular< MoveOnlyFoo&& > );
  CHECK( ! std20::regular< NonMovableFoo&& > );
  CHECK( ! std20::regular< CopyOnlyFoo&& > );
  CHECK( ! std20::regular< const Foo& > );
  CHECK( ! std20::regular< const MoveOnlyFoo& > );
  CHECK( ! std20::regular< const NonMovableFoo& > );
  CHECK( ! std20::regular< const CopyOnlyFoo& > );
  CHECK( ! std20::regular< const Foo&& > );
  CHECK( ! std20::regular< const MoveOnlyFoo&& > );
  CHECK( ! std20::regular< const NonMovableFoo&& > );
  CHECK( ! std20::regular< const CopyOnlyFoo&& > );

  CHECK( std20::regular< int > );
  CHECK( std20::regular< int* > );
  CHECK( ! std20::regular< const int > );
  CHECK( ! std20::regular< int& > );
  CHECK( ! std20::regular< const int& > );
  CHECK( ! std20::regular< int&& > );
  CHECK( ! std20::regular< const int&& > );
  CHECK( std20::regular< double > );
  CHECK( ! std20::regular< void > );
  CHECK( ! std20::regular< void() > );
  CHECK( ! std20::regular< int[2] > );
} // SCENARIO
