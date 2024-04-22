// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/algorithm.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

SCENARIO( "equal" ) {

  int a[] = { 1, 2, 3 };
  int b[] = { 1, 2, 3 };
  int c[] = { 1, 2 };
  int d[] = { 3, 2, 1 };

  std::vector< int > va = { 1, 2, 3 };
  std::vector< int > vb = { 1, 2, 3 };
  std::vector< int > vc = { 1, 2 };
  std::vector< int > vd = { 3, 2, 1 };

  // without predicate
  CHECK( std20::ranges::equal( a, a ) );
  CHECK( std20::ranges::equal( a, b ) );
  CHECK( ! std20::ranges::equal( a, c ) );
  CHECK( ! std20::ranges::equal( a, d ) );
  CHECK( std20::ranges::equal( b, a ) );
  CHECK( ! std20::ranges::equal( c, a ) );
  CHECK( ! std20::ranges::equal( d, a ) );

  CHECK( std20::ranges::equal( a, a + 3, a, a + 3 ) );
  CHECK( std20::ranges::equal( a, a + 3, b, b + 3 ) );
  CHECK( ! std20::ranges::equal( a, a + 3, c, c + 2 ) );
  CHECK( !std20::ranges::equal( a, a + 3, d, d + 3 ) );
  CHECK( std20::ranges::equal( b, b + 3, a, a + 3 ) );
  CHECK( ! std20::ranges::equal( c, c + 2, a, a + 3 ) );
  CHECK( !std20::ranges::equal( d, d + 3, a, a + 3 ) );

  CHECK( std20::ranges::equal( va, va ) );
  CHECK( std20::ranges::equal( va, vb ) );
  CHECK( ! std20::ranges::equal( va, vc ) );
  CHECK( ! std20::ranges::equal( va, vd ) );
  CHECK( std20::ranges::equal( vb, va ) );
  CHECK( ! std20::ranges::equal( vc, va ) );
  CHECK( ! std20::ranges::equal( vd, va ) );

  CHECK( std20::ranges::equal( std::begin( va ), std::end( va ), std::begin( va ), std::end( va ) ) );
  CHECK( std20::ranges::equal( std::begin( va ), std::end( va ), std::begin( vb ), std::end( vb ) ) );
  CHECK( ! std20::ranges::equal( std::begin( va ), std::end( va ), std::begin( vc ), std::end( vc ) ) );
  CHECK( !std20::ranges::equal( std::begin( va ), std::end( va ), std::begin( vd ), std::end( vd ) ) );
  CHECK( std20::ranges::equal( std::begin( vb ), std::end( vb ), std::begin( va ), std::end( va ) ) );
  CHECK( ! std20::ranges::equal( std::begin( vc ), std::end( vc ), std::begin( va ), std::end( va ) ) );
  CHECK( !std20::ranges::equal( std::begin( vd ), std::end( vd ), std::begin( va ), std::end( va ) ) );

  CHECK( std20::ranges::equal( va, a ) );
  CHECK( std20::ranges::equal( va, b ) );
  CHECK( ! std20::ranges::equal( va, c ) );
  CHECK( ! std20::ranges::equal( va, d ) );
  CHECK( std20::ranges::equal( b, va ) );
  CHECK( ! std20::ranges::equal( c, va ) );
  CHECK( ! std20::ranges::equal( d, va ) );

  CHECK( std20::ranges::equal( std::begin( va ), std::end( va ), a, a + 3 ) );
  CHECK( std20::ranges::equal( std::begin( va ), std::end( va ), b, b + 3 ) );
  CHECK( ! std20::ranges::equal( std::begin( va ), std::end( va ), c, c + 2 ) );
  CHECK( !std20::ranges::equal( std::begin( va ), std::end( va ), d, d + 3 ) );
  CHECK( std20::ranges::equal( b, b + 3, std::begin( va ), std::end( va ) ) );
  CHECK( ! std20::ranges::equal( c, c + 2, std::begin( va ), std::end( va ) ) );
  CHECK( !std20::ranges::equal( d, d + 3, std::begin( va ), std::end( va ) ) );

  // with predicate
  CHECK( std20::ranges::equal( a, a + 3, a, a + 3, std::equal_to<int>() ) );
  CHECK( std20::ranges::equal( a, a + 3, b, b + 3, std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( a, a + 3, c, c + 2, std::equal_to<int>() ) );
  CHECK( !std20::ranges::equal( a, a + 3, d, d + 3, std::equal_to<int>() ) );
  CHECK( std20::ranges::equal( b, b + 3, a, a + 3, std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( c, c + 2, a, a + 3, std::equal_to<int>() ) );
  CHECK( !std20::ranges::equal( d, d + 3, a, a + 3, std::equal_to<int>() ) );

  CHECK( std20::ranges::equal( va, va, std::equal_to<int>() ) );
  CHECK( std20::ranges::equal( va, vb, std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( va, vc, std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( va, vd, std::equal_to<int>() ) );
  CHECK( std20::ranges::equal( vb, va, std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( vc, va, std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( vd, va, std::equal_to<int>() ) );

  CHECK( std20::ranges::equal( std::begin( va ), std::end( va ), std::begin( va ), std::end( va ), std::equal_to<int>() ) );
  CHECK( std20::ranges::equal( std::begin( va ), std::end( va ), std::begin( vb ), std::end( vb ), std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( std::begin( va ), std::end( va ), std::begin( vc ), std::end( vc ), std::equal_to<int>() ) );
  CHECK( !std20::ranges::equal( std::begin( va ), std::end( va ), std::begin( vd ), std::end( vd ), std::equal_to<int>() ) );
  CHECK( std20::ranges::equal( std::begin( vb ), std::end( vb ), std::begin( va ), std::end( va ), std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( std::begin( vc ), std::end( vc ), std::begin( va ), std::end( va ), std::equal_to<int>() ) );
  CHECK( !std20::ranges::equal( std::begin( vd ), std::end( vd ), std::begin( va ), std::end( va ), std::equal_to<int>() ) );

  CHECK( std20::ranges::equal( va, a, std::equal_to<int>() ) );
  CHECK( std20::ranges::equal( va, b, std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( va, c, std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( va, d, std::equal_to<int>() ) );
  CHECK( std20::ranges::equal( b, va, std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( c, va, std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( d, va, std::equal_to<int>() ) );

  CHECK( std20::ranges::equal( std::begin( va ), std::end( va ), a, a + 3, std::equal_to<int>() ) );
  CHECK( std20::ranges::equal( std::begin( va ), std::end( va ), b, b + 3, std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( std::begin( va ), std::end( va ), c, c + 2, std::equal_to<int>() ) );
  CHECK( !std20::ranges::equal( std::begin( va ), std::end( va ), d, d + 3, std::equal_to<int>() ) );
  CHECK( std20::ranges::equal( b, b + 3, std::begin( va ), std::end( va ), std::equal_to<int>() ) );
  CHECK( ! std20::ranges::equal( c, c + 2, std::begin( va ), std::end( va ), std::equal_to<int>() ) );
  CHECK( !std20::ranges::equal( d, d + 3, std::begin( va ), std::end( va ), std::equal_to<int>() ) );
} // SCENARIO
