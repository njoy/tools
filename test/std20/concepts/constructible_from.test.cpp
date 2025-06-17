// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes
#include <string>

// convenience typedefs
using namespace njoy::tools;

// test code
struct Foo {

  ~Foo() noexcept {};
};

struct NonDefaultConstructableFoo {

  NonDefaultConstructableFoo() = delete;
  ~NonDefaultConstructableFoo() noexcept {};
};

struct Bar {

  Bar() = default;
  explicit Bar( int );
  ~Bar() = default;
};

SCENARIO( "constructible_from" ) {

  CHECK( std20::constructible_from< Foo > );
  CHECK( std20::constructible_from< Bar > );
  CHECK( std20::constructible_from< std::string > );
  CHECK( std20::constructible_from< Bar, int > );

  CHECK( ! std20::constructible_from< NonDefaultConstructableFoo > );

  CHECK( ! std20::constructible_from< void > );
  CHECK( ! std20::constructible_from< void, void > );
  CHECK( std20::constructible_from< void*, int* > );
  CHECK( ! std20::constructible_from< void*, const int* > );
  CHECK( std20::constructible_from< const void*, const int* > );
  CHECK( std20::constructible_from< int* > );
  CHECK( std20::constructible_from< int*, int* > );

  CHECK( std20::constructible_from< int > );
  CHECK( std20::constructible_from< const int > );
  CHECK( ! std20::constructible_from< const int& > );
  CHECK( ! std20::constructible_from< int() > );
  CHECK( ! std20::constructible_from< int (&)() > );
  CHECK( ! std20::constructible_from< int[] > );
  CHECK( std20::constructible_from< int[2] > );
  CHECK( std20::constructible_from< int const (&)[2], int (&)[2] > );
  CHECK( ! std20::constructible_from< int, int (&)[2] >);

  CHECK( std20::constructible_from< int, int > );
  CHECK( std20::constructible_from< int, int& > );
  CHECK( std20::constructible_from< int, int&& > );
  CHECK( std20::constructible_from< int, const int > );
  CHECK( std20::constructible_from< int, const int& > );
  CHECK( std20::constructible_from< int, const int&& > );

  CHECK( std20::constructible_from< Foo, Foo > );
  CHECK( std20::constructible_from< Foo, Foo& > );
  CHECK( std20::constructible_from< Foo, Foo&& > );
  CHECK( std20::constructible_from< Foo, const Foo > );
  CHECK( std20::constructible_from< Foo, const Foo& > );
  CHECK( std20::constructible_from< Foo, const Foo&&> );

  CHECK( ! std20::constructible_from< int&, int > );
  CHECK( std20::constructible_from< int&, int& > );
  CHECK( ! std20::constructible_from< int&, int&& > );
  CHECK( ! std20::constructible_from< int&, const int > );
  CHECK( ! std20::constructible_from< int&, const int& > );
  CHECK( ! std20::constructible_from< int&, const int&& > );

  CHECK( std20::constructible_from< const int&, int > );
  CHECK( std20::constructible_from< const int&, int& > );
  CHECK( std20::constructible_from< const int&, int&& > );
  CHECK( std20::constructible_from< const int&, const int > );
  CHECK( std20::constructible_from< const int&, const int& > );
  CHECK( std20::constructible_from< const int&, const int&& > );

  CHECK( std20::constructible_from< int&&, int > );
  CHECK( ! std20::constructible_from< int&&, int& > );
  CHECK( std20::constructible_from< int&&, int&& > );
  CHECK( ! std20::constructible_from< int&&, const int > );
  CHECK( ! std20::constructible_from< int&&, const int& > );
  CHECK( ! std20::constructible_from< int&&, const int&& > );

  CHECK( std20::constructible_from< const int&&, int > );
  CHECK(! std20::constructible_from< const int&&, int& > );
  CHECK( std20::constructible_from< const int&&, int&& > );
  CHECK( std20::constructible_from< const int&&, const int > );
  CHECK(! std20::constructible_from< const int&&, const int& > );
  CHECK( std20::constructible_from< const int&&, const int&& > );
} // SCENARIO
