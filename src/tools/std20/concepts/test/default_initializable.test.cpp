// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/concepts.hpp"

// other includes
#include <string>

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano;

// test code
struct Foo {

  ~Foo() noexcept {};
};

struct NonDefaultConstructableFoo {

  NonDefaultConstructableFoo() = delete;
  ~NonDefaultConstructableFoo() noexcept {};
};

SCENARIO( "default_initializable" ) {

  CHECK( std20::default_initializable< Foo > );
  CHECK( ! std20::default_initializable< NonDefaultConstructableFoo > );

  CHECK( ! std20::default_initializable< void > );
  CHECK( std20::default_initializable< void* > );
  CHECK( std20::default_initializable< const void* > );
  CHECK( ! std20::default_initializable< void() > );
  CHECK( std20::default_initializable< char > );
  CHECK( std20::default_initializable< float > );
  CHECK( ! std20::default_initializable< const int > );
  CHECK( std20::default_initializable< int > );
  CHECK( std20::default_initializable< int* > );
  CHECK( ! std20::default_initializable< int& > );
  CHECK( ! std20::default_initializable< int&& > );
  CHECK( ! std20::default_initializable< const int& > );
  CHECK( ! std20::default_initializable< const int&& > );
  CHECK( ! std20::default_initializable< int[] > );
  CHECK( std20::default_initializable< int[2] > );
  CHECK( ! std20::default_initializable< int() > );
  CHECK( std20::default_initializable< int(*)() > );
  CHECK( ! std20::default_initializable< int(&)() > );
} // SCENARIO
