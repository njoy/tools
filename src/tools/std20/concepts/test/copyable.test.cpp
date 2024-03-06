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

SCENARIO( "copyable" ) {

  CHECK( std20::copyable< Foo > );
  CHECK( ! std20::copyable< MoveOnlyFoo > );
  CHECK( ! std20::copyable< NonMovableFoo > );
  CHECK( ! std20::copyable< CopyOnlyFoo > );
  CHECK( ! std20::copyable< Foo& > );
  CHECK( ! std20::copyable< MoveOnlyFoo& > );
  CHECK( ! std20::copyable< NonMovableFoo& > );
  CHECK( ! std20::copyable< CopyOnlyFoo& > );
  CHECK( ! std20::copyable< Foo&& > );
  CHECK( ! std20::copyable< MoveOnlyFoo&& > );
  CHECK( ! std20::copyable< NonMovableFoo&& > );
  CHECK( ! std20::copyable< CopyOnlyFoo&& > );
  CHECK( ! std20::copyable< const Foo& > );
  CHECK( ! std20::copyable< const MoveOnlyFoo& > );
  CHECK( ! std20::copyable< const NonMovableFoo& > );
  CHECK( ! std20::copyable< const CopyOnlyFoo& > );
  CHECK( ! std20::copyable< const Foo&& > );
  CHECK( ! std20::copyable< const MoveOnlyFoo&& > );
  CHECK( ! std20::copyable< const NonMovableFoo&& > );
  CHECK( ! std20::copyable< const CopyOnlyFoo&& > );

  CHECK( std20::copyable< int > );
  CHECK( std20::copyable< int* > );
  CHECK( ! std20::copyable< const int > );
  CHECK( ! std20::copyable< int& > );
  CHECK( ! std20::copyable< const int& > );
  CHECK( ! std20::copyable< int&& > );
  CHECK( ! std20::copyable< const int&& > );
  CHECK( std20::copyable< double > );
  CHECK( ! std20::copyable< void > );
  CHECK( ! std20::copyable< void() > );
  CHECK( ! std20::copyable< int[2] > );
} // SCENARIO
