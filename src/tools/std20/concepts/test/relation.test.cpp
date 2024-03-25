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

  void operator()( long, long ) const;
  bool& operator()( int, const int& ) const;
};

SCENARIO( "relation and equivalence_relation" ) {

  CHECK( ! std20::relation< bool, void, void > );
  CHECK( ! std20::relation< bool(), void, void > );
  CHECK( ! std20::relation< bool(*)(), void, void > );
  CHECK( ! std20::relation< bool(&)(int, int), void, void > );
  CHECK( ! std20::relation< bool(), int, int > );
  CHECK( ! std20::relation< bool() const, int, int > );

  CHECK( std20::relation< bool(*)( int, int ), short, long> );
  CHECK( std20::relation< bool(&)( const void*, const void* ), char[2], int*> );

  CHECK( ! std20::relation< bool& ( const long*, short ), long*, char > );

  CHECK( ! std20::relation< int Foo::*, const Foo&, const Foo& > );
  CHECK( ! std20::relation< void (Foo::*)( long& ), const Foo*, long& > );
  CHECK( ! std20::relation< void (Foo::*)( long& ) const, Foo*, long& > );
  CHECK( std20::relation< long (Foo::*)( Foo* ) const, Foo*, Foo* > );

  CHECK( ! std20::relation< Bar, long, long > );
  CHECK( std20::relation< Bar&, int, int > );
  CHECK( std20::relation< const Bar&, const int, const int > );

  CHECK( std20::equivalence_relation< bool(*)(int, int), short, long > );
  CHECK( ! std20::equivalence_relation< Bar, long, long > );
  CHECK( std20::equivalence_relation< const Bar&, const int, const int > );
} // SCENARIO
