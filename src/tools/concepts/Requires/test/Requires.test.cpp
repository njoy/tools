// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/concepts/Requires.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::concepts;

template< typename T, Requires< true, std::is_integral, T > = true >
bool integer_type( const T& ){ return true; }

template< typename T, Requires< false, std::is_integral, T > = true >
bool integer_type( const T& ){ return false; }

SCENARIO( "Require" ) {

  GIVEN( "different types" ) {

    WHEN( "when applying Require" ) {

      THEN( "true is returned for integers and false for everything else" ) {

        CHECK( true == integer_type( 1 ) );
        CHECK( false == integer_type( 1.0 ) );
        CHECK( false == integer_type( std::vector< int >{} ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
