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

struct Bar {};

SCENARIO( "same_as" ) {

  CHECK( std20::same_as< int, int > );
  CHECK( std20::same_as< double, double > );
  CHECK( std20::same_as< Foo, Foo > );

  CHECK( std20::same_as< std::common_type_t< int, int, int >, int > );
  CHECK( std20::same_as< std::common_type_t< int, float, double >, double > );

  CHECK( ! std20::same_as< double, int > );
  CHECK( ! std20::same_as< int, double > );
  CHECK( ! std20::same_as< Foo, Bar > );
} // SCENARIO
