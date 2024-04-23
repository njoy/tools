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

// test code
struct Foo {};

SCENARIO( "contiguous_iterator" ) {

  CHECK( std20::contiguous_iterator< int* > );
  CHECK( std20::contiguous_iterator< const int* > );
  CHECK( std20::contiguous_iterator< void** > );

  CHECK( ! std20::contiguous_iterator< int* const > );
  CHECK( ! std20::contiguous_iterator< const int* const > );
  CHECK( ! std20::contiguous_iterator< void** const > );

  CHECK( ! std20::contiguous_iterator< void(*)() > );
  CHECK( ! std20::contiguous_iterator< void(&)() > );

  CHECK( ! std20::contiguous_iterator< void(Foo::*)() > );
  CHECK( ! std20::contiguous_iterator< int Foo::* > );

  CHECK( std20::contiguous_iterator< std::array< int, 1 >::iterator > );
  CHECK( std20::contiguous_iterator< std::array< Foo, 1 >::const_iterator > );

  CHECK( ! std20::contiguous_iterator< std::deque< int >::iterator > );
  CHECK( ! std20::contiguous_iterator< std::deque< Foo >::const_iterator > );

  CHECK( ! std20::contiguous_iterator< std::forward_list< int >::iterator > );
  CHECK( ! std20::contiguous_iterator< std::forward_list< Foo >::const_iterator > );

  CHECK( ! std20::contiguous_iterator< std::list< int >::iterator > );
  CHECK( ! std20::contiguous_iterator< std::list< Foo >::const_iterator > );

  // @todo: std::string and std::vector have contiguous iterators in C++20
  // The concept uses the contiguous iterator tag to determine this, which is not
  // implemented in C++17

  // CHECK( std20::contiguous_iterator< std::string::iterator > );
  // CHECK( std20::contiguous_iterator< std::string::const_iterator > );

  // CHECK( std20::contiguous_iterator< std::string_view::iterator > );
  // CHECK( std20::contiguous_iterator< std::string_view::const_iterator > );

  // CHECK( std20::contiguous_iterator< std::vector< int >::iterator > );
  // CHECK( std20::contiguous_iterator< std::vector< Foo >::const_iterator > );

  CHECK( ! std20::contiguous_iterator< std::vector< bool >::iterator > );
  CHECK( ! std20::contiguous_iterator< std::vector< bool >::const_iterator > );
} // SCENARIO
