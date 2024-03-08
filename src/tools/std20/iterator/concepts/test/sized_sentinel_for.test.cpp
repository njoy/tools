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

struct InputIterator {

	using difference_type = signed char;
	using iterator_category = std::input_iterator_tag;
	using value_type = int;

	InputIterator& operator++();
	InputIterator operator++( int );
	int operator*() const;

	bool operator == ( const InputIterator& ) const;
	bool operator != ( const InputIterator& ) const;

	InputIterator& operator+=( difference_type );
	InputIterator operator+( difference_type ) const;
	friend InputIterator operator+( difference_type, InputIterator );
	InputIterator& operator-=( difference_type );
	InputIterator operator-( difference_type ) const;
	difference_type operator-( InputIterator ) const;
};

SCENARIO( "sized_sentinel_for" ) {

	CHECK( std20::sized_sentinel_for< InputIterator, InputIterator >);

  CHECK( std20::sized_sentinel_for< int*, int* > );
  CHECK( std20::sized_sentinel_for< const int*, const int* > );
  CHECK( std20::sized_sentinel_for< const int*, int* > );
  CHECK( std20::sized_sentinel_for< void**, void** > );

  CHECK( ! std20::sized_sentinel_for< int* const, int* const > );
  CHECK( ! std20::sized_sentinel_for< const int* const, const int* const > );
  CHECK( ! std20::sized_sentinel_for< void** const, void** const > );

  CHECK( ! std20::sized_sentinel_for< void(*)(), void(*)() > );
  CHECK( ! std20::sized_sentinel_for< void(&)(), void(&)() > );

  CHECK( ! std20::sized_sentinel_for< void(Foo::*)(), void(Foo::*)() > );
  CHECK( ! std20::sized_sentinel_for< int Foo::*, int Foo::* > );

  CHECK( std20::sized_sentinel_for< std::array< int, 1 >::iterator, std::array< int, 1 >::iterator > );
  CHECK( std20::sized_sentinel_for< std::array< Foo, 1 >::const_iterator, std::array< Foo, 1 >::iterator > );
  CHECK( std20::sized_sentinel_for< std::array< Foo, 1 >::const_iterator, std::array< Foo, 1 >::const_iterator > );

  CHECK( std20::sized_sentinel_for< std::deque< int >::iterator, std::deque< int >::iterator > );
  CHECK( std20::sized_sentinel_for< std::deque< Foo >::const_iterator, std::deque< Foo >::iterator > );
  CHECK( std20::sized_sentinel_for< std::deque< Foo >::const_iterator, std::deque< Foo >::const_iterator > );

  CHECK( ! std20::sized_sentinel_for< std::forward_list< int >::iterator, std::forward_list< int >::iterator > );
  CHECK( ! std20::sized_sentinel_for< std::forward_list< Foo >::const_iterator, std::forward_list< Foo >::iterator > );
  CHECK( ! std20::sized_sentinel_for< std::forward_list< Foo >::const_iterator, std::forward_list< Foo >::const_iterator > );

  CHECK( ! std20::sized_sentinel_for< std::list< int >::iterator, std::list< int >::iterator > );
  CHECK( ! std20::sized_sentinel_for< std::list< Foo >::const_iterator, std::list< Foo >::iterator > );
  CHECK( ! std20::sized_sentinel_for< std::list< Foo >::const_iterator, std::list< Foo >::const_iterator > );

  CHECK( std20::sized_sentinel_for< std::string::iterator, std::string::iterator > );
  CHECK( std20::sized_sentinel_for< std::string::const_iterator, std::string::iterator > );
  CHECK( std20::sized_sentinel_for< std::string::const_iterator, std::string::const_iterator > );

  CHECK( std20::sized_sentinel_for< std::string_view::iterator, std::string_view::iterator > );
  CHECK( std20::sized_sentinel_for< std::string_view::const_iterator, std::string_view::iterator > );
  CHECK( std20::sized_sentinel_for< std::string_view::const_iterator, std::string_view::const_iterator > );

  CHECK( std20::sized_sentinel_for< std::vector< int >::iterator, std::vector< int >::iterator > );
  CHECK( std20::sized_sentinel_for< std::vector< Foo >::const_iterator, std::vector< Foo >::iterator > );
  CHECK( std20::sized_sentinel_for< std::vector< Foo >::const_iterator, std::vector< Foo >::const_iterator > );
} // SCENARIO
