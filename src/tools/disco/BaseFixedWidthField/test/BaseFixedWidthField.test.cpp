// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/BaseFixedWidthField.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

template < unsigned int Width >
class TestBaseFixedWidthField : protected BaseFixedWidthField< Width > {

public:

  using BaseFixedWidthField< Width >::skipPlusSign;
  using BaseFixedWidthField< Width >::skipSpaces;
};

SCENARIO( "BaseFixedWidthField" ) {

  std::string string = " a\t\n\r\n\f";
  string += char{ std::char_traits<char>::eof() };
  auto iter = string.begin();
  unsigned int position = 0;

  string = "+abc";
  position = 0;
  iter = string.begin();
  TestBaseFixedWidthField< 6 >::skipPlusSign( iter, position );
  CHECK( iter == string.begin() + 1 );
  CHECK( position == 1 );

  string = "abc";
  position = 0;
  iter = string.begin();
  TestBaseFixedWidthField< 6 >::skipPlusSign( iter, position );
  CHECK( iter == string.begin() );
  CHECK( position == 0 );

  string = "      ";
  position = 0;
  iter = string.begin();
  TestBaseFixedWidthField< 6 >::skipSpaces( iter, position );
  CHECK( iter == string.end() );
  CHECK( position == 6 );

  string = "       ";
  position = 0;
  iter = string.begin();
  TestBaseFixedWidthField< 6 >::skipSpaces( iter, position );
  CHECK( iter == string.end() - 1 );
  CHECK( position == 6 );
} // SCENARIO
