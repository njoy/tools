// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "tools/disco/Real.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Real" ) {

  GIVEN( "strings of length 10" ) {

    THEN( "the strings are entirely consumed for a field width of equal length" ) {

      std::string string;
      auto begin = string.begin();
      auto end = string.end();

      string = "       Inf";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "      -Inf";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "     Inf  ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "    -Inf  ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "Inf       ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "-Inf      ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "          ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 0, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "      +123";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "     123.0";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "   123.123";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123.123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "      -123";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "      1E99";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "    1.E+99";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "     1E-99";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e-99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "+123      ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "123.0     ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "123.123   ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123.123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "-123      ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "1E99      ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "1.E+99    ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "1E-99     ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e-99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "   +123   ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "   123.0  ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "  123.123 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123.123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "   -123   ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "   1E99   ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "   1.E+99 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "   1E-99  ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e-99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "10.0000e+1";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 100, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = " 10.000e+1";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 100, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "10.000e+1 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 100, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "    +123\n";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );
    } // THEN
  } // GIVEN

  GIVEN( "strings of length 11" ) {

    THEN( "the strings are not entirely consumed for a field width of smaller length" ) {

      std::string string;
      auto begin = string.begin();
      auto end = string.end();

      string = "       Inf ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "      -Inf ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "     Inf   ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "    -Inf   ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "Inf        ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "-Inf       ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -std::numeric_limits< double >::infinity(),
                  WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "           ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 0, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "      +123 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "     123.0 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "   123.123 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123.123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "      -123 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "      1E99 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "    1.E+99 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "     1E-99 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e-99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "+123       ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "123.0      ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "123.123    ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123.123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "-123       ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "1E99       ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "1.E+99     ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "1E-99      ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e-99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "   +123    ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "   123.0   ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "  123.123  ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123.123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "   -123    ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "   1E99    ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "   1.E+99  ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "   1E-99   ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 1e-99, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "10.0000e+1 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 100, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = " 10.000e+1 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 100, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "10.000e+1  ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 100, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );
    } // THEN
  } // GIVEN

  GIVEN( "strings with fortran style floating points" ) {

    THEN( "the strings are read correctly" ) {

      std::vector< std::string > fields = {

        "       -.5", "     -.5E0", "    -.5E+0", "    -.5E-0",
        "     -.5e0", "    -.5e+0", "    -.5e-0", "     -.5D0",
        "    -.5D+0", "    -.5D-0", "     -.5d0", "    -.5d+0",
        "    -.5d-0", "     -.5+0", "     -.5-0", "      -0.5",
        "    -0.5E0", "   -0.5E+0", "   -0.5E-0", "    -0.5e0",
        "   -0.5e+0", "   -0.5e-0", "    -0.5D0", "   -0.5D+0",
        "   -0.5D-0", "    -0.5d0", "   -0.5d+0", "   -0.5d-0",
        "     -0.50", "    -0.5-0", "     -0.50", "   -0.50E0",
        "  -0.50E+0", "  -0.50E-0", "   -0.50e0", "  -0.50e+0",
        "  -0.50e-0", "   -0.50D0", "  -0.50D+0", "  -0.50D-0",
        "   -0.50d0", "  -0.50d+0", "  -0.50d-0", "   -0.50+0",
        "   -0.50-0", "      -.50", "    -.50E0", "   -.50E+0",
        "   -.50E-0", "    -.50e0", "   -.50e+0", "   -.50e-0",
        "    -.50D0", "   -.50D+0", "   -.50D-0", "    -.50d0",
        "   -.50d+0", "   -.50d-0", "    -.50+0", "    -.50-0",
        "   -0.05E1", "  -0.05E+1", "   -0.05e1", "  -0.05e+1",
        "   -0.05D1", "  -0.05D+1", "   -0.05d1", "  -0.05d+1",
        "   -0.05+1", "     -5E-1", "     -5e-1", "     -5D-1",
        "     -5d-1", "      -5-1"
      };

      for ( const auto& string : fields ) {

        auto begin = string.begin();
        auto end = string.end();
        CHECK_THAT( -0.5, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
        CHECK( begin == end );
      }

      fields = {

        "        .5", "      .5E0", "     .5E+0", "     .5E-0",
        "      .5e0", "     .5e+0", "     .5e-0", "      .5D0",
        "     .5D+0", "     .5D-0", "      .5d0", "     .5d+0",
        "     .5d-0", "      .5+0", "      .5-0", "       0.5",
        "     0.5E0", "    0.5E+0", "    0.5E-0", "     0.5e0",
        "    0.5e+0", "    0.5e-0", "     0.5D0", "    0.5D+0",
        "    0.5D-0", "     0.5d0", "    0.5d+0", "    0.5d-0",
        "      0.50", "     0.5-0", "      0.50", "    0.50E0",
        "   0.50E+0", "   0.50E-0", "    0.50e0", "   0.50e+0",
        "   0.50e-0", "    0.50D0", "   0.50D+0", "   0.50D-0",
        "    0.50d0", "   0.50d+0", "   0.50d-0", "    0.50+0",
        "    0.50-0", "       .50", "     .50E0", "    .50E+0",
        "    .50E-0", "     .50e0", "    .50e+0", "    .50e-0",
        "     .50D0", "    .50D+0", "    .50D-0", "     .50d0",
        "    .50d+0", "    .50d-0", "     .50+0", "     .50-0",
        "       +.5", "     +.5E0", "    +.5E+0", "    +.5E-0",
        "     +.5e0", "    +.5e+0", "    +.5e-0", "     +.5D0",
        "    +.5D+0", "    +.5D-0", "     +.5d0", "    +.5d+0",
        "    +.5d-0", "     +.5+0", "     +.5-0", "      +0.5",
        "    +0.5E0", "   +0.5E+0", "   +0.5E-0", "    +0.5e0",
        "   +0.5e+0", "   +0.5e-0", "    +0.5D0", "   +0.5D+0",
        "   +0.5D-0", "    +0.5d0", "   +0.5d+0", "   +0.5d-0",
        "     +0.50", "    +0.5-0", "     +0.50", "   +0.50E0",
        "  +0.50E+0", "  +0.50E-0", "   +0.50e0", "  +0.50e+0",
        "  +0.50e-0", "   +0.50D0", "  +0.50D+0", "  +0.50D-0",
        "   +0.50d0", "  +0.50d+0", "  +0.50d-0", "   +0.50+0",
        "   +0.50-0", "      +.50", "    +.50E0", "   +.50E+0",
        "   +.50E-0", "    +.50e0", "   +.50e+0", "   +.50e-0",
        "    +.50D0", "   +.50D+0", "   +.50D-0", "    +.50d0",
        "   +.50d+0", "   +.50d-0", "    +.50+0", "    +.50-0",
        "    0.05E1", "   0.05E+1", "    0.05e1", "   0.05e+1",
        "    0.05D1", "   0.05D+1", "    0.05d1", "   0.05d+1",
        "    0.05+1", "   +0.05E1", "  +0.05E+1", "   +0.05e1",
        "  +0.05e+1", "   +0.05D1", "  +0.05D+1", "   +0.05d1",
        "  +0.05d+1", "   +0.05+1", "      5E-1", "      5e-1",
        "      5D-1", "      5d-1", "       5-1", "     +5E-1",
        "     +5e-1", "     +5D-1", "     +5d-1", "      +5-1"
      };

      for ( const auto& string : fields ) {

        auto begin = string.begin();
        auto end = string.end();
        CHECK_THAT( 0.5, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
        CHECK( begin == end );
      }

      fields = {

        "       -10", "     -10E0", "    -10E+0", "    -10E-0",
        "     -10e0", "    -10e+0", "    -10e-0", "     -10D0",
        "    -10D+0", "    -10D-0", "     -10d0", "    -10d+0",
        "    -10d-0", "     -10+0", "     -10-0", "      -10.",
        "    -10.E0", "   -10.E+0", "   -10.E-0", "    -10.e0",
        "   -10.e+0", "   -10.e-0", "    -10.D0", "   -10.D+0",
        "   -10.D-0", "    -10.d0", "   -10.d+0", "   -10.d-0",
        "    -10.+0", "    -10.-0", "     -10.0", "   -10.0E0",
        "  -10.0E+0", "  -10.0E-0", "   -10.0e0", "  -10.0e+0",
        "  -10.0e-0", "   -10.0D0", "  -10.0D+0", "  -10.0D-0",
        "   -10.0d0", "  -10.0d+0", "  -10.0d-0", "   -10.0+0",
        "   -10.0-0", "      -1E1", "     -1E+1", "      -1e1",
        "     -1e+1", "      -1D1", "     -1D+1", "      -1d1",
        "     -1d+1", "      -1+1", "   -100E-1", "   -100e-1",
        "   -100D-1", "   -100d-1", "    -100-1"
      };

      for ( const auto& string : fields ) {

        auto begin = string.begin();
        auto end = string.end();
        CHECK_THAT( -10., WithinRel( Real< 10 >::read< double >( begin, end ) ) );
        CHECK( begin == end );
      }

      fields = {

        "        10", "      10E0", "     10E+0", "     10E-0",
        "      10e0", "     10e+0", "     10e-0", "      10D0",
        "     10D+0", "     10D-0", "      10d0", "     10d+0",
        "     10d-0", "      10+0", "      10-0", "       10.",
        "     10.E0", "    10.E+0", "    10.E-0", "     10.e0",
        "    10.e+0", "    10.e-0", "     10.D0", "    10.D+0",
        "    10.D-0", "     10.d0", "    10.d+0", "    10.d-0",
        "     10.+0", "     10.-0", "      10.0", "    10.0E0",
        "   10.0E+0", "   10.0E-0", "    10.0e0", "   10.0e+0",
        "   10.0e-0", "    10.0D0", "   10.0D+0", "   10.0D-0",
        "    10.0d0", "   10.0d+0", "   10.0d-0", "    10.0+0",
        "    10.0-0", "       +10", "     +10E0", "    +10E+0",
        "    +10E-0", "     +10e0", "    +10e+0", "    +10e-0",
        "     +10D0", "    +10D+0", "    +10D-0", "     +10d0",
        "    +10d+0", "    +10d-0", "     +10+0", "     +10-0",
        "      +10.", "    +10.E0", "   +10.E+0", "   +10.E-0",
        "    +10.e0", "   +10.e+0", "   +10.e-0", "    +10.D0",
        "   +10.D+0", "   +10.D-0", "    +10.d0", "   +10.d+0",
        "   +10.d-0", "    +10.+0", "    +10.-0", "     +10.0",
        "   +10.0E0", "  +10.0E+0", "  +10.0E-0", "   +10.0e0",
        "  +10.0e+0", "  +10.0e-0", "   +10.0D0", "  +10.0D+0",
        "  +10.0D-0", "   +10.0d0", "  +10.0d+0", "  +10.0d-0",
        "   +10.0+0", "   +10.0-0", "       1E1", "      1E+1",
        "       1e1", "      1e+1", "       1D1", "      1D+1",
        "       1d1", "      1d+1", "       1+1", "      +1E1",
        "     +1E+1", "      +1e1", "     +1e+1", "      +1D1",
        "     +1D+1", "      +1d1", "     +1d+1", "      +1+1",
        "    100E-1", "    100e-1", "    100D-1", "    100d-1",
        "     100-1", "   +100E-1", "   +100e-1", "   +100D-1",
        "   +100d-1", "    +100-1"
      };

      for ( const auto& string : fields ) {

        auto begin = string.begin();
        auto end = string.end();
        CHECK_THAT( 10., WithinRel( Real< 10 >::read< double >( begin, end ) ) );
        CHECK( begin == end );
      }

      fields = {

        "   3.14159", "3.14159   ", " 3.14159E0", "3.14159E0 ",
        "3.14159E+0", "3.14159E-0", "3.14159e+0", "3.14159e0 ",
        "3.14159e-0", " 3.14159D0", "3.14159D0 ", "3.14159D+0",
        "3.14159D-0", " 3.14159d0", "3.14159d0 ", "3.14159d+0",
        "3.14159d-0", " 3.14159+0", "3.14159+0 ", " 3.14159-0",
        "3.14159-0 ", " .314159E1", ".314159E1 " , ".314159E+1",
        " .314159e1", ".314159e1 ", ".314159e+1", " .314159D1",
        ".314159D1 ", ".314159D+1", " .314159d1", ".314159d1 ",
        ".314159d+1", " .314159+1", ".314159+1 ", "0.314159E1",
        "0.314159E1", "0.314159e1", ".314159e+1", "0.314159D1",
        ".314159D+1", "0.314159d1", ".314159d+1", "0.314159+1",
        "31.4159E-1", "31.4159e-1", "31.4159D-1", "31.4159d-1",
        " 31.4159-1", "31.4159-1 ", "  +3.14159", "+3.14159  ",
        "+3.14159E0", "+3.14159D0", "+3.14159e0", "+3.14159d0"
      };

      for ( const auto& string : fields ) {

        auto begin = string.begin();
        auto end = string.end();
        CHECK_THAT( 3.14159, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
        CHECK( begin == end );
      }

      fields = {

        "         0", "       0E0", "      0E+0", "      0E-0",
        "       0e0", "      0e+0", "      0e-0", "       0D0",
        "      0D+0", "      0D-0", "       0d0", "      0d+0",
        "      0d-0", "       0+0", "       0-0", "        0.",
        "      0.E0", "     0.E+0", "     0.E-0", "      0.e0",
        "     0.e+0", "     0.e-0", "      0.D0", "     0.D+0",
        "     0.D-0", "      0.d0", "     0.d+0", "     0.d-0",
        "      0.+0", "      0.-0", "       0.0", "     0.0E0",
        "    0.0E+0", "    0.0E-0", "     0.0e0", "    0.0e+0",
        "    0.0e-0", "     0.0D0", "    0.0D+0", "    0.0D-0",
        "     0.0d0", "    0.0d+0", "    0.0d-0", "     0.0+0",
        "     0.0-0", "        +0", "      +0E0", "     +0E+0",
        "     +0E-0", "      +0e0", "     +0e+0", "     +0e-0",
        "      +0D0", "     +0D+0", "     +0D-0", "      +0d0",
        "     +0d+0", "     +0d-0", "      +0+0", "      +0-0",
        "       +0.", "     +0.E0", "    +0.E+0", "    +0.E-0",
        "     +0.e0", "    +0.e+0", "    +0.e-0", "     +0.D0",
        "    +0.D+0", "    +0.D-0", "     +0.d0", "    +0.d+0",
        "    +0.d-0", "     +0.+0", "     +0.-0", "      +0.0",
        "    +0.0E0", "   +0.0E+0", "   +0.0E-0", "    +0.0e0",
        "   +0.0e+0", "   +0.0e-0", "    +0.0D0", "   +0.0D+0",
        "   +0.0D-0", "    +0.0d0", "   +0.0d+0", "   +0.0d-0",
        "    +0.0+0", "    +0.0-0", "        -0", "      -0E0",
        "     -0E+0", "     -0E-0", "      -0e0", "     -0e+0",
        "     -0e-0", "      -0D0", "     -0D+0", "     -0D-0",
        "      -0d0", "     -0d+0", "     -0d-0", "      -0+0",
        "      -0-0", "       -0.", "     -0.E0", "    -0.E+0",
        "    -0.E-0", "     -0.e0", "    -0.e+0", "    -0.e-0",
        "     -0.D0", "    -0.D+0", "    -0.D-0", "     -0.d0",
        "    -0.d+0", "    -0.d-0", "     -0.+0", "     -0.-0",
        "      -0.0", "    -0.0E0", "   -0.0E+0", "   -0.0E-0",
        "    -0.0e0", "   -0.0e+0", "   -0.0e-0", "    -0.0D0",
        "   -0.0D+0", "   -0.0D-0", "    -0.0d0", "   -0.0d+0",
        "   -0.0d-0", "    -0.0+0", "    -0.0-0", "       0E1",
        "      0E+1", "       0e1", "      0e+1", "       0D1",
        "      0D+1", "       0d1", "      0d+1", "       0+1",
        "      +0E1", "     +0E+1", "      +0e1", "     +0e+1",
        "      +0D1", "     +0D+1", "      +0d1", "     +0d+1",
        "      +0+1", "      0E-1", "      0e-1", "      0D-1",
        "      0d-1", "       0-1", "     +0E-1", "     +0e-1",
        "     +0D-1", "     +0d-1", "      +0-1", "      -0E1",
        "     -0E+1", "      -0e1", "     -0e+1", "      -0D1",
        "     -0D+1", "      -0d1", "     -0d+1", "      -0+1",
        "     -0E-1", "     -0e-1", "     -0D-1", "     -0d-1",
        "      -0-1", "          "
      };

      for ( const auto& string : fields ) {

        auto begin = string.begin();
        auto end = string.end();
        CHECK_THAT( 0., WithinRel( Real< 10 >::read< double >( begin, end ) ) );
        CHECK( begin == end );
      }
    } // THEN
  } // GIVEN

  GIVEN( "invalid strings" ) {

    THEN( "an exception is thrown" ) {

      std::vector< std::string > fields = {

        "         +", "       + 1", "   .      ", "   .inf   ",
        "        E3", "    .E3   ", "         E", "      1.2E",
        " -123.0a  ", " -123.0 a "
      };

      for ( const auto& string : fields ) {

        auto begin = string.begin();
        auto end = string.end();
        CHECK_THROWS( Real< 10 >::read< double >( begin, end ) );
      }
    }
  }
} // SCENARIO
