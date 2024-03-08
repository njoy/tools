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

SCENARIO( "derived_from" ) {

  CHECK( std20::derived_from< Foo, Foo > );
  CHECK( std20::derived_from< Foo, const Foo > );
  CHECK( std20::derived_from< const Foo, const Foo > );
  CHECK( std20::derived_from< volatile Foo, const Foo > );

  CHECK( std20::derived_from< Bar, Foo > );
  CHECK( ! std20::derived_from< Foo, Bar > ); // Foo is not derived from Bar
  CHECK( std20::derived_from< Bar, Foo > );
  CHECK( std20::derived_from< const Bar, Foo > );
  CHECK( std20::derived_from< Bar, const Foo > );
  CHECK( std20::derived_from< volatile Bar, const Foo> );

  CHECK( ! std20::derived_from< AlsoBar, Foo > );
  CHECK( ! std20::derived_from< Foo, AlsoBar > );

  CHECK( ! std20::derived_from< int, int > );
  CHECK( ! std20::derived_from< int&, int > );
  CHECK( ! std20::derived_from< int, int& > );
  CHECK( ! std20::derived_from< int&&, int& > );
  CHECK( ! std20::derived_from< const int, int > );
  CHECK( ! std20::derived_from< const int, const int > );

  CHECK( ! std20::derived_from< int, double > );    // different primitive types
  CHECK( ! std20::derived_from< int, int > );       // same primitive types
  CHECK( ! std20::derived_from< double, double > ); // same primitive types
} // SCENARIO
