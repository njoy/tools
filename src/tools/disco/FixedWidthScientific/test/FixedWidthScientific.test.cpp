// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/FixedWidthScientific.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "FixedWidthScientific" ) {

  double value;
  std::string buffer;
  auto iter = std::back_inserter( buffer );

  value = 3.141529;
  buffer = "";
  iter = std::back_inserter( buffer );
  FixedWidthScientific< 12, 5 >::write( value, iter );
  CHECK( " 3.14153E+00" == buffer );

  value = 2;
  buffer = "";
  iter = std::back_inserter( buffer );
  FixedWidthScientific< 12, 5 >::write( value, iter );
  CHECK( " 2.00000E+00" == buffer );
} // SCENARIO
