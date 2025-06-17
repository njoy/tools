// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/ENDF.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Scientific" ) {

  THEN( "values can be written" ) {

    constexpr double infinity = std::numeric_limits<double>::infinity();

    auto write = [] ( double value ) {

      std::string buffer( "" );
      auto iter = std::back_inserter( buffer );
      ENDF::write( value, iter );
      return buffer;
    };

    CHECK( " 0.000000+0" == write( 0.0 ) );
    CHECK( " 1.000000+1" == write( 10.0 ) );
    CHECK( " 3.141590+0" == write( 3.14159 ) );
    CHECK( "        Inf" == write( infinity ) );
    CHECK( " 0.69314718" == write( 0.69314718056 ) );
    CHECK( " 1.0000-100" == write( 1E-100 ) );
    CHECK( " 1.00000+10" == write( 1E10 ) );
    CHECK( " 1.00000-10" == write( 1E-10 ) );
    CHECK( "-1.00000+10" == write( -1E10 ) );
    CHECK( "-1.00000-10" == write( -1E-10 ) );
    CHECK( "-1.000000+1" == write( -10.0 ) );
    CHECK( "-3.141590+0" == write( -3.14159 ) );
    CHECK( "       -Inf" == write( -infinity ) );
    CHECK( "-0.69314718" == write( -0.69314718056 ) );

    // Test scientific notation
    CHECK( " 1.00000+10" == write(  +1.e+10 ) );
    CHECK( " 1.000000+9" == write(  +1.0e+9 ) );
    CHECK( " 1.000000+8" == write(  +1.0e+8 ) );
    CHECK( " 1.000000+7" == write(  +1.0e+7 ) );
    CHECK( " 1.000000+6" == write(  +1.0e+6 ) );
    CHECK( " 1.000000+5" == write(  +1.0e+5 ) );
    CHECK( " 1.000000+4" == write(  +1.0e+4 ) );
    CHECK( " 1.000000+3" == write(  +1.0e+3 ) );
    CHECK( " 1.000000+2" == write(  +1.0e+2 ) );
    CHECK( " 1.000000+1" == write(  +1.0e+1 ) );
    CHECK( " 1.000000+2" == write(    100.0 ) );
    CHECK( " 1.000000+0" == write(  +1.0000 ) );
    CHECK( " 1.000000-1" == write(  +0.1000 ) );
    CHECK( " 1.000000-2" == write(  +0.0100 ) );
    CHECK( " 1.000000-3" == write(  +0.0010 ) );
    CHECK( " 1.000000-4" == write(  +0.0001 ) );
    CHECK( " 0.000000+0" == write(  0.00000 ) );
    CHECK( "-1.000000-4" == write(  -0.0001 ) );
    CHECK( "-1.000000-3" == write(  -0.0010 ) );
    CHECK( "-1.000000-2" == write(  -0.0100 ) );
    CHECK( "-1.000000-1" == write(  -0.1000 ) );
    CHECK( "-1.000000+0" == write(  -1.0000 ) );
    CHECK( "-1.000000+1" == write(  -1.0e+1 ) );
    CHECK( "-1.000000+2" == write(  -1.0e+2 ) );
    CHECK( "-1.000000+3" == write(  -1.0e+3 ) );
    CHECK( "-1.000000+4" == write(  -1.0e+4 ) );
    CHECK( "-1.000000+5" == write(  -1.0e+5 ) );
    CHECK( "-1.000000+6" == write(  -1.0e+6 ) );
    CHECK( "-1.000000+7" == write(  -1.0e+7 ) );
    CHECK( "-1.000000+8" == write(  -1.0e+8 ) );
    CHECK( "-1.000000+9" == write(  -1.0e+9 ) );
    CHECK( "-1.00000+10" == write( -1.0e+10 ) );

    // Test fixed notation
    CHECK( " 1.00000+10" == write( +1.0000001e+10 ) );
    CHECK( " 1000000100" == write( +1.00000010e+9 ) );
    CHECK( "  100000010" == write( +1.00000010e+8 ) );
    CHECK( " 10000001.0" == write( +1.00000010e+7 ) );
    CHECK( " 1000000.10" == write( +1.00000010e+6 ) );
    CHECK( " 100000.010" == write( +1.00000010e+5 ) );
    CHECK( " 10000.0010" == write( +1.00000010e+4 ) );
    CHECK( " 1000.00010" == write( +1.00000010e+3 ) );
    CHECK( " 100.000010" == write( +1.00000010e+2 ) );
    CHECK( " 10.0000010" == write( +1.00000010e+1 ) );
    CHECK( " 1.00000010" == write( +1.00000010000 ) );
    CHECK( " 0.10000001" == write( +0.10000001000 ) );
    CHECK( " 1.000000-2" == write( +0.01000000100 ) );
    CHECK( " 1.000000-3" == write( +0.00100000010 ) );
    CHECK( " 1.000000-4" == write( +0.00010000001 ) );
    CHECK( " 0.000000+0" == write( 0.000000000000 ) );
    CHECK( "-1.000000-4" == write( -0.00010000001 ) );
    CHECK( "-1.000000-3" == write( -0.00100000010 ) );
    CHECK( "-1.000000-2" == write( -0.01000000100 ) );
    CHECK( "-0.10000001" == write( -0.10000001000 ) );
    CHECK( "-1.00000010" == write( -1.00000010000 ) );
    CHECK( "-10.0000010" == write( -1.00000010e+1 ) );
    CHECK( "-100.000010" == write( -1.00000010e+2 ) );
    CHECK( "-1000.00010" == write( -1.00000010e+3 ) );
    CHECK( "-10000.0010" == write( -1.00000010e+4 ) );
    CHECK( "-100000.010" == write( -1.00000010e+5 ) );
    CHECK( "-1000000.10" == write( -1.00000010e+6 ) );
    CHECK( "-10000001.0" == write( -1.00000010e+7 ) );
    CHECK( " -100000010" == write( -1.00000010e+8 ) );
    CHECK( "-1000000100" == write( -1.00000010e+9 ) );
    CHECK( "-1.00000+10" == write( -1.0000001e+10 ) );

    CHECK( " 1.000000+0" == write(  +1.000000004 ) );
    CHECK( "-1.000000+0" == write(  -1.000000004 ) );

    CHECK( " 1.00000000" == write(  +1.000000005 ) );
    CHECK( " 1.00000001" == write(  +1.000000006 ) );
    CHECK( " 1.00000001" == write(  +1.000000009 ) );
    CHECK( "-1.00000001" == write(  -1.000000009 ) );

    CHECK( " 1.00000010" == write(  +1.000000099 ) );
    CHECK( "-1.00000010" == write(  -1.000000099 ) );

    CHECK( " 1.000001+0" == write(  +1.000000999 ) );
    CHECK( "-1.000001+0" == write(  -1.000000999 ) );

    CHECK( " 9.000000+0" == write(  9.0000000000 ) );
    CHECK( " 9.900000+0" == write(  9.9000000000 ) );
    CHECK( " 9.990000+0" == write(  9.9900000000 ) );
    CHECK( " 9.999000+0" == write(  9.9990000000 ) );
    CHECK( " 9.999900+0" == write(  9.9999000000 ) );
    CHECK( " 9.999990+0" == write(  9.9999900000 ) );
    CHECK( " 9.999999+0" == write(  9.9999990000 ) );
    CHECK( " 9.99999990" == write(  9.9999999000 ) );
    CHECK( " 9.99999999" == write(  9.9999999900 ) );
    CHECK( " 1.000000+1" == write(  9.9999999990 ) );
    CHECK( " 1.000000+2" == write(  99.999999990 ) );
    CHECK( " 1.000000+3" == write(  999.99999990 ) );
    CHECK( " 1.000000+4" == write(  9999.9999990 ) );
    CHECK( " 1.000000+5" == write(  99999.999990 ) );
    CHECK( " 1.000000+6" == write(  999999.99990 ) );
    CHECK( " 1.000000+7" == write(  9999999.9990 ) );
    CHECK( " 1.000000+8" == write(  99999999.990 ) );
    CHECK( " 1.000000+9" == write(  999999999.90 ) );
    CHECK( " 1.00000+10" == write(  9999999999.0 ) );
    CHECK( " 1.00000+11" == write(  99999999999. ) );
    CHECK( " 1.00000+12" == write(  999999999999 ) );

    CHECK( "-9.000000+0" == write( -9.0000000000 ) );
    CHECK( "-9.900000+0" == write( -9.9000000000 ) );
    CHECK( "-9.990000+0" == write( -9.9900000000 ) );
    CHECK( "-9.999000+0" == write( -9.9990000000 ) );
    CHECK( "-9.999900+0" == write( -9.9999000000 ) );
    CHECK( "-9.999990+0" == write( -9.9999900000 ) );
    CHECK( "-9.999999+0" == write( -9.9999990000 ) );
    CHECK( "-9.99999990" == write( -9.9999999000 ) );
    CHECK( "-9.99999999" == write( -9.9999999900 ) );
    CHECK( "-1.000000+1" == write( -9.9999999990 ) );
    CHECK( "-1.000000+2" == write( -99.999999990 ) );
    CHECK( "-1.000000+3" == write( -999.99999990 ) );
    CHECK( "-1.000000+4" == write( -9999.9999990 ) );
    CHECK( "-1.000000+5" == write( -99999.999990 ) );
    CHECK( "-1.000000+6" == write( -999999.99990 ) );
    CHECK( "-1.000000+7" == write( -9999999.9990 ) );
    CHECK( "-1.000000+8" == write( -99999999.990 ) );
    CHECK( "-1.000000+9" == write( -999999999.90 ) );
    CHECK( "-1.00000+10" == write( -9999999999.0 ) );
    CHECK( "-1.00000+11" == write( -99999999999. ) );
    CHECK( "-1.00000+12" == write( -999999999999 ) );

    CHECK( " 1.314750-1" == write( 0.131474998875 ) );
    CHECK( " 1.314750-1" == write( 0.1314750 ) );
  } // THEN
} // SCENARIO
