// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/Scientific.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Scientific" ) {

  THEN( "values can be written" ) {

    constexpr double infinity = std::numeric_limits<double>::infinity();

    auto write = [] ( double value ) {

      std::string buffer( "" );
      auto iter = std::back_inserter( buffer );
      Scientific< 12, 5 >::write( value, iter );
      return buffer;
    };

    CHECK( " 0.00000E+00" == write( 0 ) );
    CHECK( " 2.00000E+00" == write( 2 ) );
    CHECK( " 1.00000E+01" == write( 10 ) );
    CHECK( " 3.14159E+00" == write( 3.14159265359 ) );
    CHECK( " 6.93147E-01" == write( 0.69314718056 ) );
    CHECK( "1.00000E-100" == write( 1e-100 ) );
    CHECK( "1.00000E+100" == write( 1e+100 ) );
    CHECK( "-2.00000E+00" == write( -2 ) );
    CHECK( "-1.00000E+01" == write( -10 ) );
    CHECK( "-3.14159E+00" == write( -3.14159265359 ) );
    CHECK( "-6.93147E-01" == write( -0.69314718056 ) );
    CHECK( "-1.0000E-100" == write( -1e-100 ) );
    CHECK( "-1.0000E+100" == write( -1e+100 ) );
    CHECK( "         Inf" == write( infinity ) );
    CHECK( "        -Inf" == write( -infinity ) );
    CHECK( "-1.0000E+100" == write( -1e+100 ) );
  } // THEN
} // SCENARIO
