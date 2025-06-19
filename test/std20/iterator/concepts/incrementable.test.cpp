// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/iterator.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "incrementable and weakly_incrementable" ) {

  CHECK( std20::weakly_incrementable< int > );
  CHECK( std20::weakly_incrementable< unsigned int > );
  CHECK( ! std20::weakly_incrementable< void > );
  CHECK( std20::weakly_incrementable< int* > );
  CHECK( std20::weakly_incrementable< const int* > );

  CHECK( std20::incrementable< int > );
  CHECK( std20::incrementable< unsigned int > );
  CHECK( ! std20::incrementable< void > );
  CHECK( std20::incrementable< int* > );
  CHECK( std20::incrementable< const int* > );
} // SCENARIO
