// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/overload.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "overload" ) {

  WHEN( "using overload{}, it compiles" ) {

    std::variant< int, std::vector< int > > variant = 1;

    auto first = overload{

      [] ( int value ) { return value; },
      [] ( const std::vector< int >& vector ) { return vector.front(); }
    };

    auto value = std::visit( first, variant );
    CHECK( 1 == value );
  } // WHEN

  WHEN( "using overload(), it compiles" ) {

    std::variant< int, std::vector< int > > variant = 1;

    auto first = overload(

      [] ( int value ) { return value; },
      [] ( const std::vector< int >& vector ) { return vector.front(); }
    );

    auto value = std::visit( first, variant );
    CHECK( 1 == value );
  } // WHEN
} // SCENARIO
