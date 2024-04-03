// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/Scientific.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Scientific" ) {

  double value;
  std::string buffer;
  auto iter = std::back_inserter( buffer );

  value = 3.14159265359;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( " 3.14159E+00" == buffer );

  value = 2;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( " 2.00000E+00" == buffer );

  value = std::numeric_limits< double >::max();
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( "         Inf" == buffer );
} // SCENARIO
