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
  CHECK( std20::convertible_to< Bar, Foo > );
  CHECK( std20::convertible_to< int, double > );
  CHECK( std20::convertible_to< double, int > );
  CHECK( std20::convertible_to< void, void > );

  CHECK( ! std20::convertible_to< Foo, Bar > );       // Foo is not derived from Bar
  CHECK( ! std20::convertible_to< AlsoBar, Foo > );   // private inheritance from Foo
} // SCENARIO
