// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

// test code
struct Foo {};

struct Bar {

  void operator()( long, long ) const;
  bool& operator()( int, const int& ) const;
};

SCENARIO( "strict_weak_order" ) {

  CHECK( ! std20::strict_weak_order< bool, void, void > );
  CHECK( ! std20::strict_weak_order< bool(), void, void > );
  CHECK( ! std20::strict_weak_order< bool(*)(), void, void > );
  CHECK( ! std20::strict_weak_order< bool(&)(int, int), void, void > );
  CHECK( ! std20::strict_weak_order< bool(), int, int > );
  CHECK( ! std20::strict_weak_order< bool() const, int, int > );

  CHECK( std20::strict_weak_order< bool(*)( int, int ), short, long> );
  CHECK( std20::strict_weak_order< bool(&)( const void*, const void* ), char[2], int*> );

  CHECK( ! std20::strict_weak_order< bool& ( const long*, short ), long*, char > );

  CHECK( ! std20::strict_weak_order< int Foo::*, const Foo&, const Foo& > );
  CHECK( ! std20::strict_weak_order< void (Foo::*)( long& ), const Foo*, long& > );
  CHECK( ! std20::strict_weak_order< void (Foo::*)( long& ) const, Foo*, long& > );
  CHECK( std20::strict_weak_order< long (Foo::*)( Foo* ) const, Foo*, Foo* > );

  CHECK( ! std20::strict_weak_order< Bar, long, long > );
  CHECK( std20::strict_weak_order< Bar&, int, int > );
  CHECK( std20::strict_weak_order< const Bar&, const int, const int > );
} // SCENARIO
