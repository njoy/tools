// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/views/AnyView.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>

// convenience typedefs
using namespace njoy::tools::ranges;

// a class with data
class Data {

  std::vector< double > data_;

public:

  Data( int size ) : data_( size ) {

    for ( unsigned int i = 0; i < data_.size(); ++i ) {

      data_[i] = i;
    }
  }

   const std::vector< double >& data() const { return this->data_; }

  auto view() const { return nano::ranges::subrange( this->data() ); }

  auto transformview() const {

    return this->data() | nano::views::transform( [] ( auto&& value ) { return value + 1.; } );
  }
};

SCENARIO( "use case" ) {

  GIVEN( "a data object that returns a range" ) {

    Data object( 1000 );

    WHEN( "retrieving the view and converting it to an AnyView" ) {

      AnyRandomAccessView< const double& > chunk = object.view();

      THEN( "an AnyView can be constructed and members can be tested" ) {

        CHECK( 1000 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        unsigned int counter = 0;
        for ( auto value : chunk ) {

          ++counter;
        }
        CHECK( 1000 == counter );

        CHECK(   0. == chunk[0] );
        CHECK( 999. == chunk[999] );

        CHECK(   0. == chunk.front() );
        CHECK( 999. == chunk.back() );
      } // THEN
    } // WHEN

    WHEN( "retrieving the transformview and converting it to an AnyView" ) {

      AnyRandomAccessView< double > chunk = object.transformview();

      THEN( "an AnyView can be constructed and members can be tested" ) {

        CHECK( 1000 == chunk.size() );
        CHECK( false == chunk.empty() );
        CHECK( true == bool( chunk ) );

        unsigned int counter = 0;
        for ( auto value : chunk ) {

          ++counter;
        }
        CHECK( 1000 == counter );

        CHECK(    1. == chunk[0] );
        CHECK( 1000. == chunk[999] );

        CHECK(    1. == chunk.front() );
        CHECK( 1000. == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
