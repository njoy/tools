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

SCENARIO( "output_range" ) {

  CHECK( ! std20::ranges::output_range< void, void > );
  CHECK( std20::ranges::output_range< int[2], int > );
  CHECK( std20::ranges::output_range< int(&)[2], int > );
  CHECK( ! std20::ranges::output_range< const int[2], int > );
  CHECK( ! std20::ranges::output_range< const int(&)[2], int > );

  CHECK( std20::ranges::output_range< Range, int > );

  CHECK( std20::ranges::output_range< std::array< int, 1 >, int > );
  CHECK( std20::ranges::output_range< std::array< Foo, 1 >, Foo > );

  CHECK( std20::ranges::output_range< std::deque< int >, int > );
  CHECK( std20::ranges::output_range< std::deque< Foo >, Foo > );

  CHECK( std20::ranges::output_range< std::forward_list< int >, int > );
  CHECK( std20::ranges::output_range< std::forward_list< Foo >, Foo > );

  CHECK( std20::ranges::output_range< std::list< int >, int > );
  CHECK( std20::ranges::output_range< std::list< Foo >, Foo > );

  CHECK( ! std20::ranges::output_range< std::set< int >, int > );
  CHECK( ! std20::ranges::output_range< std::set< Foo >, Foo > );

  CHECK( std20::ranges::output_range< std::string, char > );
  CHECK( std20::ranges::output_range< std::string, char > );

  CHECK( ! std20::ranges::output_range< std::string_view, char > );
  CHECK( ! std20::ranges::output_range< std::string_view, char > );

  CHECK( std20::ranges::output_range< std::vector< int >, int > );
  CHECK( std20::ranges::output_range< std::vector< Foo >, Foo > );
} // SCENARIO
