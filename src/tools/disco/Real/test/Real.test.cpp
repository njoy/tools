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

      string = "    +123";
      string += char{ std::char_traits<char>::eof() };
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

      string = "      +123\n";
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );

      string = "      +123";
      string += char{ std::char_traits<char>::eof() };
      begin = string.begin();
      end = string.end();
      CHECK_THAT( 123, WithinRel( Real< 10 >::read< double >( begin, end ) ) );
      CHECK( begin == end - 1 );
    } // THEN
  } // GIVEN
} // SCENARIO
