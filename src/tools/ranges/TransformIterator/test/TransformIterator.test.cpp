// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/ranges/TransformIterator.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::ranges;

SCENARIO( "TransformIterator" ) {

  GIVEN( "a container with values and a transformation operation" ) {

    std::vector< int > values = { -2, -1, 0, 1, 2 };
    auto transform = [] ( auto&& value ) { return 2 * value; };

    WHEN( "when iterators are used" ) {

      TransformIterator iter( values.begin(), transform );
      TransformIterator begin( values.begin(), transform );
      TransformIterator end( values.end(), transform );

      THEN( "TransformIterator behaves as an iterator" ) {

        CHECK( *iter == -4 );

        CHECK( iter[0] == -4 );
        CHECK( iter[1] == -2 );
        CHECK( iter[2] ==  0 );
        CHECK( iter[3] ==  2 );
        CHECK( iter[4] ==  4 );

        CHECK( *( begin + 0 ) == -4 );
        CHECK( *( begin + 1 ) == -2 );
        CHECK( *( begin + 2 ) ==  0 );
        CHECK( *( begin + 3 ) ==  2 );
        CHECK( *( begin + 4 ) ==  4 );

        CHECK( *( 0 + begin ) == -4 );
        CHECK( *( 1 + begin ) == -2 );
        CHECK( *( 2 + begin ) ==  0 );
        CHECK( *( 3 + begin ) ==  2 );
        CHECK( *( 4 + begin ) ==  4 );

        CHECK( *( end - 1 ) ==  4 );
        CHECK( *( end - 2 ) ==  2 );
        CHECK( *( end - 3 ) ==  0 );
        CHECK( *( end - 4 ) == -2 );
        CHECK( *( end - 5 ) == -4 );

        CHECK( end - begin ==  5 );

        iter += 3;
        CHECK( *iter ==  2 );
        iter -= 3;
        CHECK( *iter == -4 );

        ++iter;
        CHECK( *iter == -2 );
        --iter;
        CHECK( *iter == -4 );

        CHECK( *( iter++ ) == -4 );
        CHECK( *iter == -2 );
        CHECK( *( iter-- ) == -2 );
        CHECK( *iter == -4 );

        CHECK( true  == ( iter == begin ) );
        CHECK( false == ( iter == end ) );
        CHECK( true  == ( iter != end ) );
        CHECK( false == ( iter != begin ) );
        CHECK( true  == ( iter < end ) );
        CHECK( false == ( iter < begin ) );
        CHECK( true  == ( iter <= begin ) );
        CHECK( false == ( end <= iter ) );
        CHECK( true  == ( end > iter ) );
        CHECK( false == ( iter > begin ) );
        CHECK( true  == ( end >= iter ) );
        CHECK( false == ( begin >= end ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
