// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/BaseField.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

class TestBaseField : protected BaseField {

public:

  using BaseField::skipPlusSign;
};

SCENARIO( "BaseField" ) {

  std::string string = " a\t\n\r\n\f";
  string += std::char_traits<char>::eof();
  auto iter = string.begin();
  unsigned int position = 0;

  string = "+abc";
  position = 0;
  iter = string.begin();
  TestBaseField::skipPlusSign( iter, position );
  CHECK( iter == string.begin() + 1 );
  CHECK( position == 1 );

  string = "abc";
  position = 0;
  iter = string.begin();
  TestBaseField::skipPlusSign( iter, position );
  CHECK( iter == string.begin() );
  CHECK( position == 0 );
} // SCENARIO
