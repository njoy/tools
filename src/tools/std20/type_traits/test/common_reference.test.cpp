// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/type_traits.hpp"

// other includes

// convenience typedefs
//using namespace njoy::tools;
namespace std20 = nano::ranges;

class Base {};
class First : public Base {};
class Second : public Base {};

SCENARIO( "common_reference and common_reference_t" ) {

  CHECK( std::is_same_v< std20::common_reference< int >::type, int > );
  CHECK( std::is_same_v< std20::common_reference< int&, int& >::type, int& > );
  CHECK( std::is_same_v< std20::common_reference< const int&, int& >::type, const int& > );
  CHECK( std::is_same_v< std20::common_reference< int&, const int& >::type, const int& > );
  CHECK( std::is_same_v< std20::common_reference< int&&, int& >::type, const int& > );
  CHECK( std::is_same_v< std20::common_reference< int&&, const int& >::type, const int& > );
  CHECK( std::is_same_v< std20::common_reference< int&, int&& >::type, const int& > );
  CHECK( std::is_same_v< std20::common_reference< const int&, int&& >::type, const int& > );
  CHECK( std::is_same_v< std20::common_reference< int&&, int&& >::type, int&& > );
  CHECK( std::is_same_v< std20::common_reference< const int&&, int&& >::type, const int&& > );
  CHECK( std::is_same_v< std20::common_reference< int&&, const int&& >::type, const int&& > );

  CHECK( std::is_same_v< std20::common_reference< volatile int >::type, volatile int > );
  CHECK( std::is_same_v< std20::common_reference< volatile int&, int& >::type, volatile int& > );
  CHECK( std::is_same_v< std20::common_reference< volatile int&, const int& >::type, const volatile int& > );
  CHECK( std::is_same_v< std20::common_reference< const volatile int&, int& >::type, const volatile int& > );
  CHECK( std::is_same_v< std20::common_reference< int&, volatile int& >::type, volatile int& > );
  CHECK( std::is_same_v< std20::common_reference< const int&, volatile int& >::type, const volatile int& > );
  CHECK( std::is_same_v< std20::common_reference< int&, const volatile int& >::type, const volatile int& > );

  CHECK( std::is_same_v< std20::common_reference< Base& >::type, Base& > );
  CHECK( std::is_same_v< std20::common_reference< Base&, First& >::type, Base& > );
  CHECK( std::is_same_v< std20::common_reference< Base&, Second& >::type, Base& > );
  CHECK( std::is_same_v< std20::common_reference< Base&, First&, Second& >::type, Base& > );
  CHECK( std::is_same_v< std20::common_reference< Base&&, First&& >::type, Base&& > );
  CHECK( std::is_same_v< std20::common_reference< Base&&, Second&& >::type, Base&& > );
  CHECK( std::is_same_v< std20::common_reference< Base&&, First&&, Second&& >::type, Base&& > );
  CHECK( std::is_same_v< std20::common_reference< Base&, First&& >::type, const Base& > );
  CHECK( std::is_same_v< std20::common_reference< Base&&, First& >::type, const Base& > );
  CHECK( std::is_same_v< std20::common_reference< Base&, First&, Second& >::type, Base& > );
  CHECK( std::is_same_v< std20::common_reference< Base&&, First&& >::type, Base&& > );
  CHECK( std::is_same_v< std20::common_reference< Base&&, Second&& >::type, Base&& > );
  CHECK( std::is_same_v< std20::common_reference< Base&&, First&&, Second&& >::type, Base&& > );
  CHECK( std::is_same_v< std20::common_reference< Base&, First&&, Second&& >::type, const Base& > );

  CHECK( std::is_same_v< std20::common_reference_t< int >, int > );
  CHECK( std::is_same_v< std20::common_reference_t< int&, int& >, int& > );
  CHECK( std::is_same_v< std20::common_reference_t< const int&, int& >, const int& > );
  CHECK( std::is_same_v< std20::common_reference_t< int&, const int& >, const int& > );
  CHECK( std::is_same_v< std20::common_reference_t< int&&, int& >, const int& > );
  CHECK( std::is_same_v< std20::common_reference_t< int&&, const int& >, const int& > );
  CHECK( std::is_same_v< std20::common_reference_t< int&, int&& >, const int& > );
  CHECK( std::is_same_v< std20::common_reference_t< const int&, int&& >, const int& > );
  CHECK( std::is_same_v< std20::common_reference_t< int&&, int&& >, int&& > );
  CHECK( std::is_same_v< std20::common_reference_t< const int&&, int&& >, const int&& > );
  CHECK( std::is_same_v< std20::common_reference_t< int&&, const int&& >, const int&& > );

  CHECK( std::is_same_v< std20::common_reference_t< volatile int >, volatile int > );
  CHECK( std::is_same_v< std20::common_reference_t< volatile int&, int& >, volatile int& > );
  CHECK( std::is_same_v< std20::common_reference_t< volatile int&, const int& >, const volatile int& > );
  CHECK( std::is_same_v< std20::common_reference_t< const volatile int&, int& >, const volatile int& > );
  CHECK( std::is_same_v< std20::common_reference_t< int&, volatile int& >, volatile int& > );
  CHECK( std::is_same_v< std20::common_reference_t< const int&, volatile int& >, const volatile int& > );
  CHECK( std::is_same_v< std20::common_reference_t< int&, const volatile int& >, const volatile int& > );

  CHECK( std::is_same_v< std20::common_reference_t< Base& >, Base& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&, First& >, Base& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&, Second& >, Base& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&, First&, Second& >, Base& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&&, First&& >, Base&& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&&, Second&& >, Base&& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&&, First&&, Second&& >, Base&& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&, First&& >, const Base& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&&, First& >, const Base& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&, First&, Second& >, Base& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&&, First&& >, Base&& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&&, Second&& >, Base&& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&&, First&&, Second&& >, Base&& > );
  CHECK( std::is_same_v< std20::common_reference_t< Base&, First&&, Second&& >, const Base& > );
} // SCENARIO
