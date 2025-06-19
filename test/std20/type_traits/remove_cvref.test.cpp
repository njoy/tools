// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/type_traits.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "remove_cvref and remove_cvref_t" ) {

  CHECK( std::is_same_v< std20::remove_cvref< int >::type, int > );
  CHECK( std::is_same_v< std20::remove_cvref< int& >::type, int > );
  CHECK( std::is_same_v< std20::remove_cvref< int&& >::type, int > );
  CHECK( std::is_same_v< std20::remove_cvref< const int& >::type, int > );
  CHECK( std::is_same_v< std20::remove_cvref< int[2] >::type, int[2] > );
  CHECK( std::is_same_v< std20::remove_cvref< const int[2] >::type, int[2] > );
  CHECK( std::is_same_v< std20::remove_cvref< const int(&)[2] >::type, int[2] > );
  CHECK( std::is_same_v< std20::remove_cvref< int(int) >::type, int(int) > );

  CHECK( std::is_same_v< std20::remove_cvref_t< int >, int > );
  CHECK( std::is_same_v< std20::remove_cvref_t< int& >, int > );
  CHECK( std::is_same_v< std20::remove_cvref_t< int&& >, int > );
  CHECK( std::is_same_v< std20::remove_cvref_t< const int& >, int > );
  CHECK( std::is_same_v< std20::remove_cvref_t< int[2] >, int[2] > );
  CHECK( std::is_same_v< std20::remove_cvref_t< const int[2] >, int[2] > );
  CHECK( std::is_same_v< std20::remove_cvref_t< const int(&)[2] >, int[2] > );
  CHECK( std::is_same_v< std20::remove_cvref_t< int(int) >, int(int) > );
} // SCENARIO
