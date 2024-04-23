// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "integral" ) {

  CHECK( std20::integral< bool > );
  CHECK( std20::integral< char > );
  CHECK( std20::integral< int > );
  CHECK( std20::integral< unsigned int > );
  CHECK( std20::integral< std::ptrdiff_t > );
  CHECK( std20::integral< std::size_t > );

  CHECK( ! std20::integral< void > );
  CHECK( ! std20::integral< float > );
  CHECK( ! std20::integral< int* > );
  CHECK( ! std20::integral< int& > );
  CHECK( ! std20::integral< int&& > );
  CHECK( ! std20::integral< const int& > );
  CHECK( ! std20::integral< int[] > );
  CHECK( ! std20::integral< int[2] > );
  CHECK( ! std20::integral< int() > );
  CHECK( ! std20::integral< int(*)() > );
  CHECK( ! std20::integral< int(&)() > );

  CHECK( ! std20::integral< double > );
  CHECK( ! std20::integral< decltype("") > );
  CHECK( ! std20::integral< void > );
} // SCENARIO
