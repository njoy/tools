// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano::ranges;

// test code
struct Foo {};

struct Bar : public Foo {};

struct AlsoBar : private Foo {};

SCENARIO( "convertible_to" ) {

  CHECK( std20::convertible_to< Foo, Foo > );
  CHECK( std20::convertible_to< Foo, const Foo > );
  CHECK( std20::convertible_to< Foo const, const Foo > );
  CHECK( ! std20::convertible_to< volatile Foo, const Foo > );
  CHECK( ! std20::convertible_to< volatile Foo, const volatile Foo& > );
  CHECK( std20::convertible_to< volatile Foo&, const volatile Foo& > );

  CHECK( std20::convertible_to< Bar, Bar > );
  CHECK( std20::convertible_to< Bar, Foo > );
  CHECK( ! std20::convertible_to< Foo, Bar > );
  CHECK( std20::convertible_to< Bar, Foo > );
  CHECK( std20::convertible_to< const Bar, Foo > );
  CHECK( std20::convertible_to< Bar, const Foo > );
  CHECK( std20::convertible_to< Bar, const Foo& > );
  CHECK( ! std20::convertible_to< volatile Bar, const Foo > );
  CHECK( ! std20::convertible_to< volatile Bar, const Foo& > );

  CHECK( ! std20::convertible_to< AlsoBar, Foo > );
  CHECK( ! std20::convertible_to< Foo, AlsoBar > );

  CHECK( std20::convertible_to< int, int > );
  CHECK( std20::convertible_to< int&, int > );
  CHECK( ! std20::convertible_to< int, int& > );
  CHECK( std20::convertible_to< int, const int& > );
  CHECK( ! std20::convertible_to< int&&, int& > );
  CHECK( std20::convertible_to< int&&, const int& > );
  CHECK( std20::convertible_to< const int, int > );
  CHECK( ! std20::convertible_to< const int, int& > );
  CHECK( std20::convertible_to< const int, const int > );
  CHECK( std20::convertible_to< const int, const int& > );

  CHECK( std20::convertible_to< int, float > );
  CHECK( ! std20::convertible_to< int, float& > );
  CHECK( ! std20::convertible_to< int, int* > );
  CHECK( std20::convertible_to< int*, void* > );
  CHECK( std20::convertible_to< int*, const void* > );
  CHECK( ! std20::convertible_to< const int*, void* > );
  CHECK( ! std20::convertible_to< int, void > );
} // SCENARIO
