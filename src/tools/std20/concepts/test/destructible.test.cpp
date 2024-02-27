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
struct Foo {

  ~Foo() noexcept {};
};

struct IndestructibleFoo {

  ~IndestructibleFoo() = delete;
};

struct ThrowingDestructorFoo {

  ~ThrowingDestructorFoo() noexcept(false);
};

struct Bar {

  ~Bar() = default;
};

SCENARIO( "destructible" ) {

  CHECK( std20::destructible< Foo > );
  CHECK( std20::destructible< Bar > );
  CHECK( std20::destructible< std::string > );

  CHECK( ! std20::destructible< IndestructibleFoo > );
  CHECK( ! std20::destructible< ThrowingDestructorFoo > );

  CHECK( ! std20::destructible<void> );
  CHECK( std20::destructible<char> );
  CHECK( std20::destructible<float> );
  CHECK( std20::destructible<int*> );
  CHECK( std20::destructible<int&> );
  CHECK( std20::destructible<int&&> );
  CHECK( std20::destructible<const int&> );
  CHECK( ! std20::destructible<int[]> );
  CHECK( std20::destructible<int[2]> );
  CHECK( std20::destructible<int[2][3]> );
  CHECK( ! std20::destructible<int()> );
  CHECK( std20::destructible<int(*)()> );
  CHECK( std20::destructible<int(&)()> );
} // SCENARIO
