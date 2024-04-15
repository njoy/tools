// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/FixedPoint.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "FixedPoint" ) {

  THEN( "values can be written" ) {

    constexpr double infinity = std::numeric_limits<double>::infinity();

    auto write = [] ( double value ) {

      std::string buffer( "" );
      auto iter = std::back_inserter( buffer );
      FixedPoint< 12, 5 >::write( value, iter );
      return buffer;
    };

    CHECK( "     0.00000" == write( 0 ) );
    CHECK( "     2.00000" == write( 2 ) );
    CHECK( "    10.00000" == write( 10 ) );
    CHECK( "     3.14159" == write( 3.14159265359 ) );
    CHECK( "     0.69315" == write( 0.69314718056 ) );
    CHECK( "    -2.00000" == write( -2 ) );
    CHECK( "   -10.00000" == write( -10 ) );
    CHECK( "    -3.14159" == write( -3.14159265359 ) );
    CHECK( "    -0.69315" == write( -0.69314718056 ) );
    CHECK( "         Inf" == write( infinity ) );
    CHECK( "        -Inf" == write( -infinity ) );
  } // THEN
} // SCENARIO
