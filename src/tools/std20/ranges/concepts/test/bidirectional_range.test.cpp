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

SCENARIO( "bidirectional_range" ) {

  CHECK( ! std20::ranges::bidirectional_range< void > );
  CHECK( std20::ranges::bidirectional_range< int[2] > );
  CHECK( std20::ranges::bidirectional_range< int(&)[2] > );
  CHECK( std20::ranges::bidirectional_range< const int[2] > );
  CHECK( std20::ranges::bidirectional_range< const int(&)[2] > );

  CHECK( std20::ranges::bidirectional_range< Range > );

  CHECK( std20::ranges::bidirectional_range< std::array< int, 1 > > );
  CHECK( std20::ranges::bidirectional_range< std::array< Foo, 1 > > );

  CHECK( std20::ranges::bidirectional_range< std::deque< int > > );
  CHECK( std20::ranges::bidirectional_range< std::deque< Foo > > );

  CHECK( ! std20::ranges::bidirectional_range< std::forward_list< int > > );
  CHECK( ! std20::ranges::bidirectional_range< std::forward_list< Foo > > );

  CHECK( std20::ranges::bidirectional_range< std::list< int > > );
  CHECK( std20::ranges::bidirectional_range< std::list< Foo > > );

  CHECK( std20::ranges::bidirectional_range< std::set< int > > );
  CHECK( std20::ranges::bidirectional_range< std::set< Foo > > );

  CHECK( std20::ranges::bidirectional_range< std::string > );
  CHECK( std20::ranges::bidirectional_range< std::string > );

  CHECK( std20::ranges::bidirectional_range< std::string_view > );
  CHECK( std20::ranges::bidirectional_range< std::string_view > );

  CHECK( std20::ranges::bidirectional_range< std::vector< int > > );
  CHECK( std20::ranges::bidirectional_range< std::vector< Foo > > );
} // SCENARIO
