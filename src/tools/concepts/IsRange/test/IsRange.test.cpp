// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/concepts/IsRange.hpp"

// other includes
#include <vector>
#include <map>

// convenience typedefs
using namespace njoy::tools::concepts;

SCENARIO( "IsRange" ) {

  GIVEN( "different types" ) {

    WHEN( "when applying IsRange" ) {

      THEN( "true is returned for ranges and false for everything else" ) {

        CHECK( false == IsRange< int >::value );

        CHECK( true == IsRange< std::vector< int > >::value );
        CHECK( true == IsRange< const std::vector< int > >::value );
        CHECK( true == IsRange< std::map< int, int > >::value );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
