// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "unsigned_integral" ) {

  CHECK( std20::unsigned_integral< bool > );
  CHECK( std20::unsigned_integral< unsigned int > );
  CHECK( std20::unsigned_integral< std::size_t > );

  CHECK( ! std20::unsigned_integral< void > );
  CHECK( ! std20::unsigned_integral< float > );
  CHECK( ! std20::unsigned_integral< int* > );
  CHECK( ! std20::unsigned_integral< int& > );
  CHECK( ! std20::unsigned_integral< int&& > );
  CHECK( ! std20::unsigned_integral< const int& > );
  CHECK( ! std20::unsigned_integral< int[] > );
  CHECK( ! std20::unsigned_integral< int[2] > );
  CHECK( ! std20::unsigned_integral< int() > );
  CHECK( ! std20::unsigned_integral< int(*)() > );
  CHECK( ! std20::unsigned_integral< int(&)() > );

  CHECK( ! std20::unsigned_integral< std::ptrdiff_t > );
  CHECK( ! std20::unsigned_integral< char > );
  CHECK( ! std20::unsigned_integral< int > );
  CHECK( ! std20::unsigned_integral< double > );
  CHECK( ! std20::unsigned_integral< decltype("") > );
  CHECK( ! std20::unsigned_integral< void > );
} // SCENARIO
