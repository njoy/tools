// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/Record.hpp"

// other includes
#include <vector>
#include "tools/disco/Integer.hpp"
#include "tools/disco/Scientific.hpp"
#include "tools/disco/Column.hpp"

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "Record" ) {

    std::string source;;
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

} // SCENARIO