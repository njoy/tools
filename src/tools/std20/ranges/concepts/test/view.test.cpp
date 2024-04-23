// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/ranges.hpp"

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

struct Range {

  int* begin();
  int* end();

  const int* begin() const;
  const int* end() const;
};

SCENARIO( "view" ) {

  CHECK( ! std20::ranges::view< void > );
  CHECK( ! std20::ranges::view< int[2] > );
  CHECK( ! std20::ranges::view< int(&)[2] > );
  CHECK( ! std20::ranges::view< const int[2] > );
  CHECK( ! std20::ranges::view< const int(&)[2] > );

  CHECK( ! std20::ranges::view< Range > );

  CHECK( ! std20::ranges::view< std::array< int, 1 > > );
  CHECK( ! std20::ranges::view< std::array< Foo, 1 > > );

  CHECK( ! std20::ranges::view< std::deque< int > > );
  CHECK( ! std20::ranges::view< std::deque< Foo > > );

  CHECK( ! std20::ranges::view< std::forward_list< int > > );
  CHECK( ! std20::ranges::view< std::forward_list< Foo > > );

  CHECK( ! std20::ranges::view< std::list< int > > );
  CHECK( ! std20::ranges::view< std::list< Foo > > );

  CHECK( ! std20::ranges::view< std::set< int > > );
  CHECK( ! std20::ranges::view< std::set< Foo > > );

  CHECK( ! std20::ranges::view< std::string > );
  CHECK( ! std20::ranges::view< std::string > );

  CHECK( std20::ranges::view< std::string_view > );
  CHECK( std20::ranges::view< std::string_view > );

  CHECK( ! std20::ranges::view< std::vector< int > > );
  CHECK( ! std20::ranges::view< std::vector< Foo > > );
} // SCENARIO
