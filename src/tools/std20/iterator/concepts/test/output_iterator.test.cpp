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

struct Bar {

  bool operator<( const Bar& ) const;
};

SCENARIO( "output_iterator" ) {

  CHECK( std20::output_iterator< int*, int > );
  CHECK( std20::output_iterator< int*, const int > );
  CHECK( std20::output_iterator< int*, long > );
  CHECK( std20::output_iterator< void**, void* > );
  CHECK( std20::output_iterator< void**, long* > );
  CHECK( ! std20::output_iterator< const int*, int > );

  CHECK( ! std20::output_iterator< int* const, int > );
  CHECK( ! std20::output_iterator< const int* const, int > );
  CHECK( ! std20::output_iterator< void** const, void* > );

  CHECK( ! std20::output_iterator< void(*)(), void(&)() > );
  CHECK( ! std20::output_iterator< void(&)(), void(&)() > );
  CHECK( std20::output_iterator< void(**)(), void(*)() > );
  CHECK( std20::output_iterator< void(**)(), void(&)() > );

  CHECK( ! std20::output_iterator< void(Foo::*)(), Foo* > );
  CHECK( ! std20::output_iterator< void(Foo::*)(), void(Foo::*)() > );
  CHECK( ! std20::output_iterator< int Foo::*, int > );
  CHECK( ! std20::output_iterator< int Foo::*, int Foo::* > );

  CHECK( std20::output_iterator< std::array< int, 1 >::iterator, int > );
  CHECK( std20::output_iterator< std::array< Bar, 1 >::iterator, Bar > );
  CHECK( ! std20::output_iterator< std::array< int, 1 >::const_iterator, int > );
  CHECK( ! std20::output_iterator< std::array< Bar, 1 >::const_iterator, Bar > );

  CHECK( std20::output_iterator< std::deque< int >::iterator, int > );
  CHECK( std20::output_iterator< std::deque< Bar >::iterator, Bar > );
  CHECK( ! std20::output_iterator< std::deque< int >::const_iterator, int > );
  CHECK( ! std20::output_iterator< std::deque< Bar >::const_iterator, Bar > );

  CHECK( std20::output_iterator< std::forward_list< int >::iterator, int > );
  CHECK( std20::output_iterator< std::forward_list< Bar >::iterator, Bar > );
  CHECK( ! std20::output_iterator< std::forward_list< int >::const_iterator, int > );
  CHECK( ! std20::output_iterator< std::forward_list< Bar >::const_iterator, Bar > );

  CHECK( std20::output_iterator< std::list< int >::iterator, int > );
  CHECK( std20::output_iterator< std::list< Bar >::iterator, Bar > );
  CHECK( ! std20::output_iterator< std::list< int >::const_iterator, int > );
  CHECK( ! std20::output_iterator< std::list< Bar >::const_iterator, Bar > );

  CHECK( ! std20::output_iterator< std::set< int >::iterator, int > );
  CHECK( ! std20::output_iterator< std::set< Bar >::iterator, Bar > );
  CHECK( ! std20::output_iterator< std::set< int >::const_iterator, int > );
  CHECK( ! std20::output_iterator< std::set< Bar >::const_iterator, Bar > );

  CHECK( std20::output_iterator< std::string::iterator, char > );
  CHECK( std20::output_iterator< std::string::iterator, int > );
  CHECK( ! std20::output_iterator< std::string::const_iterator, char > );
  CHECK( ! std20::output_iterator< std::string::const_iterator, int > );

  CHECK( ! std20::output_iterator< std::string_view::iterator, char > );
  CHECK( ! std20::output_iterator< std::string_view::iterator, int > );
  CHECK( ! std20::output_iterator< std::string_view::const_iterator, char > );
  CHECK( ! std20::output_iterator< std::string_view::const_iterator, int > );

  CHECK( std20::output_iterator< std::vector< int >::iterator, int > );
  CHECK( std20::output_iterator< std::vector< Bar >::iterator, Bar > );
  CHECK( ! std20::output_iterator< std::vector< int >::const_iterator, int > );
  CHECK( ! std20::output_iterator< std::vector< Bar >::const_iterator, Bar > );
} // SCENARIO
