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

  value = 0;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( " 0.00000E+00" == buffer );
  CHECK( 12 == buffer.size() );

  value = 2;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( " 2.00000E+00" == buffer );
  CHECK( 12 == buffer.size() );

  value = 10;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( " 1.00000E+01" == buffer );
  CHECK( 12 == buffer.size() );

  value = 3.14159265359;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( " 3.14159E+00" == buffer );
  CHECK( 12 == buffer.size() );

  value = 0.69314718056;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( " 6.93147E-01" == buffer );
  CHECK( 12 == buffer.size() );

  value = 1e-100;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( "1.00000E-100" == buffer );
  CHECK( 12 == buffer.size() );

  value = 1e+100;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( "1.00000E+100" == buffer );
  CHECK( 12 == buffer.size() );

  value = -2;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( "-2.00000E+00" == buffer );
  CHECK( 12 == buffer.size() );

  value = -10;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( "-1.00000E+01" == buffer );
  CHECK( 12 == buffer.size() );

  value = -3.14159265359;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( "-3.14159E+00" == buffer );
  CHECK( 12 == buffer.size() );

  value = -0.69314718056;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( "-6.93147E-01" == buffer );
  CHECK( 12 == buffer.size() );

  value = -1e-100;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( "-1.0000E-100" == buffer );
  CHECK( 12 == buffer.size() );

  value = -1e+100;
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( "-1.0000E+100" == buffer );
  CHECK( 12 == buffer.size() );

  value = std::numeric_limits< double >::max();
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( "         Inf" == buffer );
  CHECK( 12 == buffer.size() );

  value = -std::numeric_limits< double >::max();
  buffer = "";
  iter = std::back_inserter( buffer );
  Scientific< 12, 5 >::write( value, iter );
  CHECK( "        -Inf" == buffer );
  CHECK( 12 == buffer.size() );
} // SCENARIO
