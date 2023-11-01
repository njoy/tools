// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/concepts/IsIterator.hpp"

// other includes
#include <iterator>
#include <forward_list>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

// convenience typedefs
using namespace njoy::tools::concepts;

SCENARIO( "IsIterator sfinae objects" ) {

  GIVEN( "different types" ) {

    WHEN( "when applying IsIterator" ) {

      THEN( "true is returned for iterators and false for everything else" ) {

        // non iterator type
        CHECK( false == IsIterator< int >::value );

        // input iterator types
        CHECK( true == IsIterator< std::istream_iterator< int > >::value );

        // output iterator types
        CHECK( true == IsIterator< std::ostream_iterator< int > >::value );

        // forward iterator types
        CHECK( true == IsIterator< std::forward_list< int >::iterator >::value );
        CHECK( true == IsIterator< std::unordered_set< int >::iterator >::value );
        CHECK( true == IsIterator< std::unordered_map< int, int >::iterator >::value );

        // bidirectional iterator types
        CHECK( true == IsIterator< std::list< int >::iterator >::value );
        CHECK( true == IsIterator< std::set< int >::iterator >::value );
        CHECK( true == IsIterator< std::map< int, int >::iterator >::value );

        // random access iterator types
        CHECK( true == IsIterator< std::vector< int >::iterator >::value );
      } // THEN
    } // WHEN

    WHEN( "when applying IsInputIterator" ) {

      THEN( "true is returned for iterators that conform to input iterators" ) {

        // input iterator type
        CHECK( true == IsInputIterator< std::istream_iterator< int > >::value );

        // output iterator types
        CHECK( false == IsInputIterator< std::ostream_iterator< int > >::value );

        // forward iterator types
        CHECK( true == IsInputIterator< std::forward_list< int >::iterator >::value );
        CHECK( true == IsInputIterator< std::unordered_set< int >::iterator >::value );
        CHECK( true == IsInputIterator< std::unordered_map< int, int >::iterator >::value );

        // bidirectional iterator types
        CHECK( true == IsInputIterator< std::list< int >::iterator >::value );
        CHECK( true == IsInputIterator< std::set< int >::iterator >::value );
        CHECK( true == IsInputIterator< std::map< int, int >::iterator >::value );

        // random access iterator types
        CHECK( true == IsInputIterator< std::vector< int >::iterator >::value );
      } // THEN
    } // WHEN

    WHEN( "when applying IsOutputIterator" ) {

      THEN( "true is returned for iterators that conform to output iterators" ) {

        // input iterator types
        CHECK( false == IsOutputIterator< std::istream_iterator< int > >::value );

        // output iterator types
        CHECK( true == IsOutputIterator< std::ostream_iterator< int > >::value );

        // forward iterator types
        CHECK( false == IsOutputIterator< std::forward_list< int >::iterator >::value );
        CHECK( false == IsOutputIterator< std::unordered_set< int >::iterator >::value );
        CHECK( false == IsOutputIterator< std::unordered_map< int, int >::iterator >::value );

        // bidirectional iterator types
        CHECK( false == IsOutputIterator< std::list< int >::iterator >::value );
        CHECK( false == IsOutputIterator< std::set< int >::iterator >::value );
        CHECK( false == IsOutputIterator< std::map< int, int >::iterator >::value );

        // random access iterator types
        CHECK( false == IsOutputIterator< std::vector< int >::iterator >::value );
      } // THEN
    } // WHEN

    WHEN( "when applying IsForwardIterator" ) {

      THEN( "true is returned for iterators that conform to forward iterators" ) {

        // input iterator types
        CHECK( false == IsForwardIterator< std::istream_iterator< int > >::value );

        // output iterator types
        CHECK( false == IsForwardIterator< std::ostream_iterator< int > >::value );

        // forward iterator types
        CHECK( true == IsForwardIterator< std::forward_list< int >::iterator >::value );
        CHECK( true == IsForwardIterator< std::unordered_set< int >::iterator >::value );
        CHECK( true == IsForwardIterator< std::unordered_map< int, int >::iterator >::value );

        // bidirectional iterator types
        CHECK( true == IsForwardIterator< std::list< int >::iterator >::value );
        CHECK( true == IsForwardIterator< std::set< int >::iterator >::value );
        CHECK( true == IsForwardIterator< std::map< int, int >::iterator >::value );

        // random access iterator types
        CHECK( true == IsForwardIterator< std::vector< int >::iterator >::value );
      } // THEN
    } // WHEN

    WHEN( "when applying IsBidirectionalIterator" ) {

      THEN( "true is returned for iterators that conform to bidirectional iterators" ) {

        // input iterator types
        CHECK( false == IsBidirectionalIterator< std::istream_iterator< int > >::value );

        // output iterator types
        CHECK( false == IsBidirectionalIterator< std::ostream_iterator< int > >::value );

        // forward iterator types
        CHECK( false == IsBidirectionalIterator< std::forward_list< int >::iterator >::value );
        CHECK( false == IsBidirectionalIterator< std::unordered_set< int >::iterator >::value );
        CHECK( false == IsBidirectionalIterator< std::unordered_map< int, int >::iterator >::value );

        // bidirectional iterator types
        CHECK( true == IsBidirectionalIterator< std::list< int >::iterator >::value );
        CHECK( true == IsBidirectionalIterator< std::set< int >::iterator >::value );
        CHECK( true == IsBidirectionalIterator< std::map< int, int >::iterator >::value );

        // random access iterator types
        CHECK( true == IsBidirectionalIterator< std::vector< int >::iterator >::value );
      } // THEN
    } // WHEN

    WHEN( "when applying IsRandomAccessIterator" ) {

      THEN( "true is returned for iterators that conform to random access iterators" ) {

        // input iterator types
        CHECK( false == IsRandomAccessIterator< std::istream_iterator< int > >::value );

        // output iterator types
        CHECK( false == IsRandomAccessIterator< std::ostream_iterator< int > >::value );

        // forward iterator types
        CHECK( false == IsRandomAccessIterator< std::forward_list< int >::iterator >::value );
        CHECK( false == IsRandomAccessIterator< std::unordered_set< int >::iterator >::value );
        CHECK( false == IsRandomAccessIterator< std::unordered_map< int, int >::iterator >::value );

        // bidirectional iterator types
        CHECK( false == IsRandomAccessIterator< std::list< int >::iterator >::value );
        CHECK( false == IsRandomAccessIterator< std::set< int >::iterator >::value );
        CHECK( false == IsRandomAccessIterator< std::map< int, int >::iterator >::value );

        // random access iterator types
        CHECK( true == IsRandomAccessIterator< std::vector< int >::iterator >::value );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
