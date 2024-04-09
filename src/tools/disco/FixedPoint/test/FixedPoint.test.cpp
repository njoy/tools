// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/FixedPoint.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "FixedPoint" ) {

  THEN( "values can be written" ) {

    double value;
    std::string buffer;
    auto iter = std::back_inserter( buffer );

    value = 0;
    buffer = "";
    iter = std::back_inserter( buffer );
    FixedPoint< 12, 5 >::write( value, iter );
    CHECK( "     0.00000" == buffer );
    CHECK( 12 == buffer.size() );

    value = 2;
    buffer = "";
    iter = std::back_inserter( buffer );
    FixedPoint< 12, 5 >::write( value, iter );
    CHECK( "     2.00000" == buffer );
    CHECK( 12 == buffer.size() );

    value = 10;
    buffer = "";
    iter = std::back_inserter( buffer );
    FixedPoint< 12, 5 >::write( value, iter );
    CHECK( "    10.00000" == buffer );
    CHECK( 12 == buffer.size() );

    value = 3.14159265359;
    buffer = "";
    iter = std::back_inserter( buffer );
    FixedPoint< 12, 5 >::write( value, iter );
    CHECK( "     3.14159" == buffer );
    CHECK( 12 == buffer.size() );

    value = 0.69314718056;
    buffer = "";
    iter = std::back_inserter( buffer );
    FixedPoint< 12, 5 >::write( value, iter );
    CHECK( "     0.69315" == buffer );
    CHECK( 12 == buffer.size() );

//    value = 1e-100;
//    buffer = "";
//    iter = std::back_inserter( buffer );
//    FixedPoint< 12, 5 >::write( value, iter );
//    CHECK( "1.00000E-100" == buffer );
//    CHECK( 12 == buffer.size() );
//
//    value = 1e+100;
//    buffer = "";
//    iter = std::back_inserter( buffer );
//    FixedPoint< 12, 5 >::write( value, iter );
//    CHECK( "1.00000E+100" == buffer );
//    CHECK( 12 == buffer.size() );

    value = -2;
    buffer = "";
    iter = std::back_inserter( buffer );
    FixedPoint< 12, 5 >::write( value, iter );
    CHECK( "    -2.00000" == buffer );
    CHECK( 12 == buffer.size() );

    value = -10;
    buffer = "";
    iter = std::back_inserter( buffer );
    FixedPoint< 12, 5 >::write( value, iter );
    CHECK( "   -10.00000" == buffer );
    CHECK( 12 == buffer.size() );

    value = -3.14159265359;
    buffer = "";
    iter = std::back_inserter( buffer );
    FixedPoint< 12, 5 >::write( value, iter );
    CHECK( "    -3.14159" == buffer );
    CHECK( 12 == buffer.size() );

    value = -0.69314718056;
    buffer = "";
    iter = std::back_inserter( buffer );
    FixedPoint< 12, 5 >::write( value, iter );
    CHECK( "    -0.69315" == buffer );
    CHECK( 12 == buffer.size() );

    value = std::numeric_limits< double >::max();
    buffer = "";
    iter = std::back_inserter( buffer );
    FixedPoint< 12, 5 >::write( value, iter );
    CHECK( "         Inf" == buffer );
    CHECK( 12 == buffer.size() );

    value = -std::numeric_limits< double >::max();
    buffer = "";
    iter = std::back_inserter( buffer );
    FixedPoint< 12, 5 >::write( value, iter );
    CHECK( "        -Inf" == buffer );
    CHECK( 12 == buffer.size() );
  } // THEN
} // SCENARIO
