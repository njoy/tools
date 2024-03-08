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

SCENARIO( "readable" ) {

  CHECK( ! std20::readable< int > );
  CHECK( std20::readable< int* > );
  CHECK( std20::readable< iterator< int > > );

  CHECK( std20::readable< std::array< int, 1 >::iterator > );
  CHECK( std20::readable< std::array< Foo, 1 >::const_iterator > );

  CHECK( std20::readable< std::deque< int >::iterator > );
  CHECK( std20::readable< std::deque< Foo >::const_iterator > );

  CHECK( std20::readable< std::forward_list< int >::iterator > );
  CHECK( std20::readable< std::forward_list< Foo >::const_iterator > );

  CHECK( std20::readable< std::list< int >::iterator > );
  CHECK( std20::readable< std::list< Foo >::const_iterator > );

  CHECK( std20::readable< std::string::iterator > );
  CHECK( std20::readable< std::string::const_iterator > );

  CHECK( std20::readable< std::string_view::iterator > );
  CHECK( std20::readable< std::string_view::const_iterator > );

  CHECK( std20::readable< std::vector< int >::iterator > );
  CHECK( std20::readable< std::vector< Foo >::const_iterator > );

  CHECK( std20::readable< std::vector< bool >::iterator > );
  CHECK( std20::readable< std::vector< bool >::const_iterator > );
} // SCENARIO
