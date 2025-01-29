// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/FreeFormatInteger.hpp"

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

      string = "    10 ";
      iter = string.begin();
      end = string.end();
      CHECK( 10 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == end - 1 );

      string = " \n  10 ";
      iter = string.begin();
      end = string.end();
      CHECK( 10 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == end - 1 );

      string = " \r\n 10 ";
      iter = string.begin();
      end = string.end();
      CHECK( 10 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == end - 1 );

      string = " \t  10 ";
      iter = string.begin();
      end = string.end();
      CHECK( 10 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == end - 1 );

      string = "      +123";
      iter = string.begin();
      end = string.end();
      CHECK( 123 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == end );

      string = "       123";
      iter = string.begin();
      end = string.end();
      CHECK( 123 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == end );

      string = "      -123";
      iter = string.begin();
      end = string.end();
      CHECK( -123 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == end );

      string = "+123      ";
      iter = string.begin();
      end = string.end();
      CHECK( 123 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == begin + 4 );

      string = "123       ";
      iter = string.begin();
      end = string.end();
      CHECK( 123 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == begin + 3 );

      string = "-123      ";
      iter = string.begin();
      end = string.end();
      CHECK( -123 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == begin + 4 );

      string = "   +123   ";
      iter = string.begin();
      end = string.end();
      CHECK( 123 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == begin + 7 );

      string = "   123    ";
      iter = string.begin();
      end = string.end();
      CHECK( 123 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == begin + 6 );

      string = "   -123   ";
      iter = string.begin();
      end = string.end();
      CHECK( -123 == FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == begin + 7 );

      string = "    +123\n";
      iter = string.begin();
      end = string.end();
      CHECK( 123 == FreeFormatInteger::read< int >( iter, end ) );
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
      CHECK_THROWS( FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == end );

      string = " \n    ";
      iter = string.begin();
      end = string.end();
      CHECK_THROWS( FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == end );

      string = " \r\n   ";
      iter = string.begin();
      end = string.end();
      CHECK_THROWS( FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == end );

      string = " \t    ";
      iter = string.begin();
      end = string.end();
      CHECK_THROWS( FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == end );

      string = "  abc ";
      iter = string.begin();
      end = string.end();
      CHECK_THROWS( FreeFormatInteger::read< int >( iter, end ) );
      CHECK( iter == begin + 2 );
    } // THEN
  } // GIVEN
} // SCENARIO
