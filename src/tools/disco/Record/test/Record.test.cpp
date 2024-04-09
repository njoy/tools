// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/Record.hpp"

// other includes
#include <vector>
#include "tools/disco/Integer.hpp"
#include "tools/disco/Scientific.hpp"
#include "tools/disco/Column.hpp"
#include "tools/disco/Character.hpp"

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Record" ) {

  GIVEN( "a line of data" ) {

    THEN( "data can be read from it" ) {

      std::string source;
      auto iter = source.begin();
      auto end = source.end();

      double value;
      source = " 2.0000E+00\n";
      iter = source.begin();
      end = source.end();
      Record< Scientific< 11, 4 > >::read( iter, end, value );
      CHECK( 2 == value );
      CHECK( iter == end );

      std::vector< double > vector( 2 );
      source = " 1.0000E-11 2.0000E+07\n";
      iter = source.begin();
      end = source.end();
      Record< Scientific< 11, 4 >, Scientific< 11, 4 > >::read( iter, end, vector[0], vector[1] );
      CHECK( 1e-11 == vector[0] );
      CHECK(  2e+7 == vector[1] );
      CHECK( iter == end );

      std::tuple< double, int, std::string > tuple;
      source = " 1.0000E-11          2abcd\n";
      iter = source.begin();
      end = source.end();
      Record< Scientific< 11, 4 >,
              Integer< 11 >,
              Character< 4 > >::read( iter, end, std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple) );
      CHECK(  1e-11 == std::get<0>(tuple) );
      CHECK(      2 == std::get<1>(tuple) );
      CHECK( "abcd" == std::get<2>(tuple) );
      CHECK( iter == end );
    } // THEN
  } // GIVEN

  GIVEN( "a line of data" ) {

    WHEN( "reading only part of the data" ) {

      THEN( "the entire line is consumed" ) {

        std::string source;
        auto iter = source.begin();
        auto end = source.end();

        source = " 1.0000E-11 1.0000E-10 1.0000E-09\n";
        iter = source.begin();
        end = source.end();
        double value1;
        double value2;
        Record< Scientific< 11, 4 >,
                Scientific< 11, 4 >,
                Scientific< 11, 4 > >::read( iter, end, value1, value2 );
        CHECK( 1e-11 == value1 );
        CHECK( 1e-10 == value2 );
        CHECK( iter == end );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data" ) {

    WHEN( "writing the data" ) {

      THEN( "the line is written as expected" ) {

        std::string buffer;
        auto iter = std::back_inserter( buffer );

        double f = 2;
        int i = 4;
        std::string s = "abc";
        Record< Scientific< 11, 4 >,
                Integer< 4 >,
                Character< 5 > >::write( iter, f, i, s );
        CHECK( " 2.0000E+00   4  abc\n" == buffer );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
