// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/type_traits.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

SCENARIO( "type_identity and type_identity_t" ) {

  CHECK( std::is_same_v< std20::type_identity< int >::type, int > );
  CHECK( std::is_same_v< std20::type_identity< int& >::type, int& > );
  CHECK( std::is_same_v< std20::type_identity< int&& >::type, int&& > );
  CHECK( std::is_same_v< std20::type_identity< const int& >::type, const int& > );
  CHECK( std::is_same_v< std20::type_identity< int[2] >::type, int[2] > );
  CHECK( std::is_same_v< std20::type_identity< const int[2] >::type, const int[2] > );
  CHECK( std::is_same_v< std20::type_identity< const int(&)[2] >::type, const int(&)[2] > );
  CHECK( std::is_same_v< std20::type_identity< int(int) >::type, int(int) > );

  CHECK( std::is_same_v< std20::type_identity_t< int >, int > );
  CHECK( std::is_same_v< std20::type_identity_t< int& >, int& > );
  CHECK( std::is_same_v< std20::type_identity_t< int&& >, int&& > );
  CHECK( std::is_same_v< std20::type_identity_t< const int& >, const int& > );
  CHECK( std::is_same_v< std20::type_identity_t< int[2] >, int[2] > );
  CHECK( std::is_same_v< std20::type_identity_t< const int[2] >, const int[2] > );
  CHECK( std::is_same_v< std20::type_identity_t< const int(&)[2] >, const int(&)[2] > );
  CHECK( std::is_same_v< std20::type_identity_t< int(int) >, int(int) > );
} // SCENARIO
