// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano::ranges;

// test code
struct Foo {};

struct Bar {

  void operator()() const;
  void operator()(int);
};

SCENARIO( "invocable and regular_invocable" ) {

  CHECK( ! std20::invocable< int > );
  CHECK( std20::invocable< int() > );
  CHECK( std20::invocable< int(*)() > );
  CHECK( std20::invocable< int(&)() > );
  CHECK( ! std20::invocable< int(), int > );
  CHECK( ! std20::invocable< int() const > );

  CHECK( std20::invocable< int( const long*, short ), long*, char > );

  CHECK( std20::invocable< int Foo::*, const Foo& > );
  CHECK( ! std20::invocable< void (Foo::*)(long&), const Foo*, long& > );
  CHECK( std20::invocable< void (Foo::*)(long&) const, Foo*, long& > );

  CHECK( std20::invocable< Bar > );
  CHECK( std20::invocable< Bar, int > );
  CHECK( std20::invocable< const Bar& > );
  CHECK( ! std20::invocable< const Bar&, int > );

  CHECK( ! std20::regular_invocable< int > );
  CHECK( std20::regular_invocable< int() > );
  CHECK( std20::regular_invocable< int(*)() > );
  CHECK( std20::regular_invocable< int(&)() > );
  CHECK( ! std20::regular_invocable< int(), int > );
  CHECK( ! std20::regular_invocable< int() const > );

  CHECK( std20::regular_invocable< int( const long*, short ), long*, char > );

  CHECK( std20::regular_invocable< int Foo::*, const Foo& > );
  CHECK( ! std20::regular_invocable< void (Foo::*)(long&), const Foo*, long& > );
  CHECK( std20::regular_invocable< void (Foo::*)(long&) const, Foo*, long& > );

  CHECK( std20::regular_invocable< Bar > );
  CHECK( std20::regular_invocable< Bar, int > );
  CHECK( std20::regular_invocable< const Bar& > );
  CHECK( ! std20::regular_invocable< const Bar&, int > );
} // SCENARIO
