// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/concepts/IsIterator.hpp"

// other includes
#include <vector>
#include <map>

// convenience typedefs
using namespace njoy::tools::concepts;

SCENARIO( "IsIterator" ) {

  GIVEN( "different types" ) {

    WHEN( "when applying IsIterator" ) {

      THEN( "true is returned for iterators and false for everything else" ) {

        CHECK( false == IsIterator< int >::value );

        CHECK( true == IsIterator< std::vector< int >::iterator >::value );
        CHECK( true == IsIterator< std::vector< int >::const_iterator >::value );

        CHECK( true == IsIterator< int* >::value );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
