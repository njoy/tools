// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

// test code
struct Foo {};

struct Bar : public Foo {};

struct AlsoBar : private Foo {};

SCENARIO( "common_with" ) {

  CHECK( std20::common_with< Foo, Foo > );
  CHECK( std20::common_with< Bar, Foo > );
  CHECK( std20::common_with< Foo, Bar > );
  CHECK( std20::common_with< Bar, Bar > );
  CHECK( std20::common_with< int, double > );
  CHECK( std20::common_with< double, int > );
  CHECK( std20::common_with< void, void > );
  CHECK( ! std20::common_with< int, void > );
  CHECK( ! std20::common_with< int, int* > );
  CHECK( ! std20::common_with< int, int() > );

  CHECK( std20::common_with< int, int > );
  CHECK( std20::common_with< int, const int > );
  CHECK( std20::common_with< int&, int& > );
  CHECK( std20::common_with< const int&, int& > );
  CHECK( std20::common_with< int&, const int& > );
  CHECK( std20::common_with< int&&, int& > );
  CHECK( std20::common_with< int&&, const int& > );
  CHECK( std20::common_with< int&, int&& > );
  CHECK( std20::common_with< const int&, int&& > );
  CHECK( std20::common_with< int&&, int&& > );
  CHECK( std20::common_with< const int&&, int&& > );
  CHECK( std20::common_with< int&&, const int&& > );

  CHECK( std20::common_with< int, short > );
  CHECK( std20::common_with< short, int > );
  CHECK( std20::common_with< void*, const int* > );

  CHECK( std20::common_with< volatile int&, int& > );
  CHECK( std20::common_with< volatile int&, const int& > );
  CHECK( std20::common_with< const volatile int&, int& > );
  CHECK( std20::common_with< int&, volatile int& > );
  CHECK( std20::common_with< const int&, volatile int& > );
  CHECK( std20::common_with< int&, const volatile int& > );

  CHECK( std20::common_with< Foo&, Bar& > );
  CHECK( std20::common_with< Foo&&, Bar&& > );
  CHECK( std20::common_with< Foo&, Bar&& > );
  CHECK( std20::common_with< Foo&&, Bar& > );
  CHECK( std20::common_with< Foo&&, Bar&& > );

  CHECK( ! std20::common_with< AlsoBar, Foo > );   // private inheritance from Foo
  CHECK( ! std20::common_with< Foo, AlsoBar > );   // private inheritance from Foo
} // SCENARIO
