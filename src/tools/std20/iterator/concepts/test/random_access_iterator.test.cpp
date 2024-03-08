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
//using namespace njoy::tools;
namespace std20 = nano::ranges;

// test code
struct Foo {};

SCENARIO( "random_access_iterator" ) {

  CHECK( std20::random_access_iterator< int* > );
  CHECK( std20::random_access_iterator< const int* > );
  CHECK( std20::random_access_iterator< void** > );

  CHECK( ! std20::random_access_iterator< int* const > );
  CHECK( ! std20::random_access_iterator< const int* const > );
  CHECK( ! std20::random_access_iterator< void** const > );

  CHECK( ! std20::random_access_iterator< void(*)() > );
  CHECK( ! std20::random_access_iterator< void(&)() > );

  CHECK( ! std20::random_access_iterator< void(Foo::*)() > );
  CHECK( ! std20::random_access_iterator< int Foo::* > );

  CHECK( std20::random_access_iterator< std::array< int, 1 >::iterator > );
  CHECK( std20::random_access_iterator< std::array< Foo, 1 >::const_iterator > );

  CHECK( std20::random_access_iterator< std::deque< int >::iterator > );
  CHECK( std20::random_access_iterator< std::deque< Foo >::const_iterator > );

  CHECK( ! std20::random_access_iterator< std::forward_list< int >::iterator > );
  CHECK( ! std20::random_access_iterator< std::forward_list< Foo >::const_iterator > );

  CHECK( ! std20::random_access_iterator< std::list< int >::iterator > );
  CHECK( ! std20::random_access_iterator< std::list< Foo >::const_iterator > );

  CHECK( std20::random_access_iterator< std::string::iterator > );
  CHECK( std20::random_access_iterator< std::string::const_iterator > );

  CHECK( std20::random_access_iterator< std::string_view::iterator > );
  CHECK( std20::random_access_iterator< std::string_view::const_iterator > );

  CHECK( std20::random_access_iterator< std::vector< int >::iterator > );
  CHECK( std20::random_access_iterator< std::vector< Foo >::const_iterator > );
} // SCENARIO
