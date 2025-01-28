// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "tools/disco/FreeFormatReal.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Integer" ) {

  GIVEN ( "strings with data" ) {

    THEN( "the strings are consumed up to the valid data" ) {

      std::string string;
      auto iter = string.begin();
      auto begin = string.begin();
      auto end = string.end();

      string = "       Inf";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( std::numeric_limits< double >::infinity(),
                  WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end );

      string = "      -Inf";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( -std::numeric_limits< double >::infinity(),
                  WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end );

      string = "     Inf  ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( std::numeric_limits< double >::infinity(),
                  WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 8 );

      string = "    -Inf  ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( -std::numeric_limits< double >::infinity(),
                  WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 8 );

      string = "Inf       ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( std::numeric_limits< double >::infinity(),
                  WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 3 );

      string = "-Inf      ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( -std::numeric_limits< double >::infinity(),
                  WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 4 );

      string = "      +123";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end );

      string = "     123.0";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end );

      string = "   123.123";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 123.123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end );

      string = "      -123";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end );

      string = "      1E99";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end );

      string = "    1.E+99";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end );

      string = "     1E-99";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 1e-99, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end );

      string = "+123      ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 4 );

      string = "123.0     ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 5 );

      string = "123.123   ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 123.123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 7 );

      string = "-123      ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 4 );

      string = "1E99      ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 4 );

      string = "1.E+99    ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 6 );

      string = "1E-99     ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 1e-99, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 5 );

      string = "   +123   ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 7 );

      string = "   123.0  ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 8 );

      string = "  123.123 ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 123.123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 9 );

      string = "   -123   ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 7 );

      string = "   1E99   ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 7 );

      string = "   1.E+99 ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 1e+99, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin +9 );

      string = "   1E-99  ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 1e-99, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == begin + 8 );

      string = "10.0000e+1";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 100, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end );

      string = " 10.000e+1";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 100, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end );

      string = "10.000e+1 ";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 100, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end - 1 );

      string = "    +123\n";
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end - 1 );

      string = "    +123";
      string += std::char_traits<char>::eof();
      iter = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( FreeFormatReal::read< double >( iter, end ) ) );
      CHECK( iter == end - 1 );
    } // THEN
  } // GIVEN

  GIVEN ( "strings with invalid data" ) {

    THEN( "the strings are consumed up to the invalid data and an "
          "exception is thrown" ) {

      std::string string;
      auto iter = string.begin();
      auto begin = string.begin();
      auto end = string.end();

      string = "      ";
      iter = string.begin();
      end = string.end();
      CHECK_THROWS( FreeFormatReal::read< double >( iter, end ) );
      CHECK( iter == end );

      string = " \n    ";
      iter = string.begin();
      end = string.end();
      CHECK_THROWS( FreeFormatReal::read< double >( iter, end ) );
      CHECK( iter == end );

      string = " \r\n   ";
      iter = string.begin();
      end = string.end();
      CHECK_THROWS( FreeFormatReal::read< double >( iter, end ) );
      CHECK( iter == end );

      string = " \t    ";
      iter = string.begin();
      end = string.end();
      CHECK_THROWS( FreeFormatReal::read< double >( iter, end ) );
      CHECK( iter == end );

      string = "  abc ";
      iter = string.begin();
      end = string.end();
      CHECK_THROWS( FreeFormatReal::read< double >( iter, end ) );
      CHECK( iter == begin + 2 );
    } // THEN
  } // GIVEN
} // SCENARIO
