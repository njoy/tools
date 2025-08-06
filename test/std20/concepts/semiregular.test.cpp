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

SCENARIO( "semiregular" ) {

  CHECK( std20::semiregular< Foo > );
  CHECK( std20::semiregular< RegularFoo > );
  CHECK( ! std20::semiregular< MoveOnlyFoo > );
  CHECK( ! std20::semiregular< NonMovableFoo > );
  CHECK( ! std20::semiregular< CopyOnlyFoo > );
  CHECK( ! std20::semiregular< Foo& > );
  CHECK( ! std20::semiregular< MoveOnlyFoo& > );
  CHECK( ! std20::semiregular< NonMovableFoo& > );
  CHECK( ! std20::semiregular< CopyOnlyFoo& > );
  CHECK( ! std20::semiregular< Foo&& > );
  CHECK( ! std20::semiregular< MoveOnlyFoo&& > );
  CHECK( ! std20::semiregular< NonMovableFoo&& > );
  CHECK( ! std20::semiregular< CopyOnlyFoo&& > );
  CHECK( ! std20::semiregular< const Foo& > );
  CHECK( ! std20::semiregular< const MoveOnlyFoo& > );
  CHECK( ! std20::semiregular< const NonMovableFoo& > );
  CHECK( ! std20::semiregular< const CopyOnlyFoo& > );
  CHECK( ! std20::semiregular< const Foo&& > );
  CHECK( ! std20::semiregular< const MoveOnlyFoo&& > );
  CHECK( ! std20::semiregular< const NonMovableFoo&& > );
  CHECK( ! std20::semiregular< const CopyOnlyFoo&& > );

  CHECK( std20::semiregular< int > );
  CHECK( std20::semiregular< int* > );
  CHECK( ! std20::semiregular< const int > );
  CHECK( ! std20::semiregular< int& > );
  CHECK( ! std20::semiregular< const int& > );
  CHECK( ! std20::semiregular< int&& > );
  CHECK( ! std20::semiregular< const int&& > );
  CHECK( std20::semiregular< double > );
  CHECK( ! std20::semiregular< void > );
  CHECK( ! std20::semiregular< void() > );
  CHECK( ! std20::semiregular< int[2] > );
} // SCENARIO
