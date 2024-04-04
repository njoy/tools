// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "tools/disco/Integer.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Integer" ) {

  GIVEN( "strings of length 10" ) {

    THEN( "the strings are entirely consumed for a field width of equal length" ) {

      std::string string;
      auto begin = string.begin();
      auto end = string.end();

      string = "          ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 0, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "      +123";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "       123";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "      -123";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "+123      ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "123       ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "-123      ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "   +123   ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "   123    ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "   -123   ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end );

      string = "    +123\n";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "    +123";
      string += char{ std::char_traits<char>::eof() };
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );
    } // THEN
  } // GIVEN

  GIVEN( "strings of length 11" ) {

    THEN( "the strings are not entirely consumed for a field width of smaller length" ) {

      std::string string;
      auto begin = string.begin();
      auto end = string.end();

      string = "           ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 0, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "      +123 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "       123 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "      -123 ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "+123       ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "123        ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "-123       ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "   +123    ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "   123     ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "   -123    ";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( -123, WithinRel( Integer< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );
    } // THEN
  } // GIVEN

  GIVEN( "integer values" ) {

    THEN( "they can be written" ) {

      int value;
      std::string buffer;
      auto iter = std::back_inserter( buffer );

      value = 0;
      buffer = "";
      iter = std::back_inserter( buffer );
      Integer< 12 >::write( value, iter );
      CHECK( "           0" == buffer );
      CHECK( 12 == buffer.size() );

      value = 2;
      buffer = "";
      iter = std::back_inserter( buffer );
      Integer< 12 >::write( value, iter );
      CHECK( "           2" == buffer );
      CHECK( 12 == buffer.size() );

      value = 10;
      buffer = "";
      iter = std::back_inserter( buffer );
      Integer< 12 >::write( value, iter );
      CHECK( "          10" == buffer );
      CHECK( 12 == buffer.size() );
    } // THEN
  } // GIVEN
} // SCENARIO