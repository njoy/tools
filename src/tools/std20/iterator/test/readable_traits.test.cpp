// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/iterator.hpp"

// other includes
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <string>
#include <string_view>
#include <vector>

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "readable_traits" ) {

  CHECK( std20::same_as< std20::readable_traits< int* >::value_type, int > );
  CHECK( std20::same_as< std20::readable_traits< const int* >::value_type, int > );
  CHECK( std20::same_as< std20::readable_traits< int[] >::value_type, int > );
  CHECK( std20::same_as< std20::readable_traits< const int[] >::value_type, int > );

  CHECK( std20::same_as< std20::readable_traits< std::array< int, 1 >::iterator >::value_type, int > );
  CHECK( std20::same_as< std20::readable_traits< std::array< const int, 1 >::iterator >::value_type, const int > );

  CHECK( std20::same_as< std20::readable_traits< std::deque< int >::iterator >::value_type, std::deque< int >::iterator::value_type > );

  CHECK( std20::same_as< std20::readable_traits< std::forward_list< int >::iterator >::value_type, std::forward_list< int >::iterator::value_type > );

  CHECK( std20::same_as< std20::readable_traits< std::list< int >::iterator >::value_type, std::list< int >::iterator::value_type > );

  CHECK( std20::same_as< std20::readable_traits< std::vector< int >::iterator >::value_type, std::vector< int >::iterator::value_type > );

  CHECK( std20::same_as< std20::readable_traits< const std::array< int, 1 >::iterator >::value_type, int > );

  CHECK( std20::same_as< std20::readable_traits< const std::deque< int >::iterator >::value_type, std::deque< int >::iterator::value_type > );

  CHECK( std20::same_as< std20::readable_traits< const std::forward_list< int >::iterator >::value_type, std::forward_list< int >::iterator::value_type > );

  CHECK( std20::same_as< std20::readable_traits< const std::list< int >::iterator >::value_type, std::list< int >::iterator::value_type > );

  CHECK( std20::same_as< std20::readable_traits< const std::vector< int >::iterator >::value_type, std::vector< int >::iterator::value_type > );
} // SCENARIO
