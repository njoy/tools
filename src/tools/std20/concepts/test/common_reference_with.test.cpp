// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

// test code
struct Foo {};

struct Bar : public Foo {};

struct AlsoBar : private Foo {};

SCENARIO( "common_reference_with" ) {

  CHECK( std20::common_reference_with< Foo, Foo > );
  CHECK( std20::common_reference_with< Bar, Foo > );
  CHECK( std20::common_reference_with< Foo, Bar > );
  CHECK( std20::common_reference_with< Bar, Bar > );
  CHECK( std20::common_reference_with< int, double > );
  CHECK( std20::common_reference_with< double, int > );
  CHECK( std20::common_reference_with< void, void > );
  CHECK( ! std20::common_reference_with< int, void > );
  CHECK( ! std20::common_reference_with< int, int* > );
  CHECK( ! std20::common_reference_with< int, int() > );

  CHECK( std20::common_reference_with< int, int > );
  CHECK( std20::common_reference_with< int&, int& > );
  CHECK( std20::common_reference_with< const int&, int& > );
  CHECK( std20::common_reference_with< int&, const int& > );
  CHECK( std20::common_reference_with< int&&, int& > );
  CHECK( std20::common_reference_with< int&&, const int& > );
  CHECK( std20::common_reference_with< int&, int&& > );
  CHECK( std20::common_reference_with< const int&, int&& > );
  CHECK( std20::common_reference_with< int&&, int&& > );
  CHECK( std20::common_reference_with< const int&&, int&& > );
  CHECK( std20::common_reference_with< int&&, const int&& > );

  CHECK( std20::common_reference_with< volatile int&, int& > );
  CHECK( std20::common_reference_with< volatile int&, const int& > );
  CHECK( std20::common_reference_with< const volatile int&, int& > );
  CHECK( std20::common_reference_with< int&, volatile int& > );
  CHECK( std20::common_reference_with< const int&, volatile int& > );
  CHECK( std20::common_reference_with< int&, const volatile int& > );

  CHECK( std20::common_reference_with< Foo&, Bar& > );
  CHECK( std20::common_reference_with< Foo&&, Bar&& > );
  CHECK( std20::common_reference_with< Foo&, Bar&& > );
  CHECK( std20::common_reference_with< Foo&&, Bar& > );
  CHECK( std20::common_reference_with< Foo&&, Bar&& > );

  CHECK( ! std20::common_reference_with< AlsoBar, Foo > );   // private inheritance from Foo
  CHECK( ! std20::common_reference_with< Foo, AlsoBar > );   // private inheritance from Foo
} // SCENARIO
