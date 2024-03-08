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
namespace std20 = nano;

// test code
struct Foo {};

template < typename T >
struct iterator {

	using iterator_category = std::input_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;

	T* pointer_;

	iterator() = default;
	iterator( T* pointer ) noexcept : pointer_{ pointer } {}

	T& operator*() noexcept {

    return *pointer_;
	}

	const T& operator*() const noexcept {

    return *pointer_;
	}

	T* operator->() const noexcept {

    return pointer_;
	}
};

SCENARIO( "writable" ) {

  CHECK( ! std20::writable< int, int > );
  CHECK( std20::writable< int*, int > );
  CHECK( ! std20::writable< int*, Foo > );
  CHECK( std20::writable< iterator< int >, int > );

  CHECK( std20::writable< std::array< int, 1 >::iterator, int > );
  CHECK( ! std20::writable< std::array< Foo, 1 >::const_iterator, Foo > );

  CHECK( std20::writable< std::deque< int >::iterator, int > );
  CHECK( ! std20::writable< std::deque< Foo >::const_iterator, Foo > );

  CHECK( std20::writable< std::forward_list< int >::iterator, int > );
  CHECK( ! std20::writable< std::forward_list< Foo >::const_iterator, Foo > );

  CHECK( std20::writable< std::list< int >::iterator, int > );
  CHECK( ! std20::writable< std::list< Foo >::const_iterator, Foo > );

  CHECK( std20::writable< std::string::iterator, char > );
  CHECK( ! std20::writable< std::string::const_iterator, char > );

  // std::string_view iterator is a const_iterator so is not writable
  CHECK( ! std20::writable< std::string_view::iterator, char > );
  CHECK( ! std20::writable< std::string_view::const_iterator, Foo > );

  CHECK( std20::writable< std::vector< int >::iterator, int > );
  CHECK( ! std20::writable< std::vector< Foo >::const_iterator, Foo > );
} // SCENARIO
