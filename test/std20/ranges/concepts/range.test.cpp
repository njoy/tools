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

SCENARIO( "range" ) {

  CHECK( ! std20::ranges::range< void > );
  CHECK( std20::ranges::range< int[2] > );
  CHECK( std20::ranges::range< int(&)[2] > );
  CHECK( std20::ranges::range< const int[2] > );
  CHECK( std20::ranges::range< const int(&)[2] > );

  CHECK( std20::ranges::range< Range > );

  CHECK( std20::ranges::range< std::array< int, 1 > > );
  CHECK( std20::ranges::range< std::array< Foo, 1 > > );

  CHECK( std20::ranges::range< std::deque< int > > );
  CHECK( std20::ranges::range< std::deque< Foo > > );

  CHECK( std20::ranges::range< std::forward_list< int > > );
  CHECK( std20::ranges::range< std::forward_list< Foo > > );

  CHECK( std20::ranges::range< std::list< int > > );
  CHECK( std20::ranges::range< std::list< Foo > > );

  CHECK( std20::ranges::range< std::set< int > > );
  CHECK( std20::ranges::range< std::set< Foo > > );

  CHECK( std20::ranges::range< std::string > );
  CHECK( std20::ranges::range< std::string > );

  CHECK( std20::ranges::range< std::string_view > );
  CHECK( std20::ranges::range< std::string_view > );

  CHECK( std20::ranges::range< std::vector< int > > );
  CHECK( std20::ranges::range< std::vector< Foo > > );
} // SCENARIO
