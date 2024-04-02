// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/BaseField.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

class TestBaseField : protected BaseField {

public:

  using BaseField::isSpace;
  using BaseField::isSpaceOrTabulation;
  using BaseField::isNewLine;
  using BaseField::isWhiteSpace;
  using BaseField::isEndOfFile;
  using BaseField::skipPlusSign;
};

SCENARIO( "BaseField" ) {

  std::string string = " a\t\n\r\n\f";
  string += char{ std::char_traits<char>::eof() };
  auto iter = string.begin();
  unsigned int position = 0;

  iter = string.begin();
  CHECK( true == TestBaseField::isSpace( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpace( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpace( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpace( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpace( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpace( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpace( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpace( iter ) ); ++iter;
  CHECK( iter == string.end() );

  iter = string.begin();
  CHECK( true == TestBaseField::isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( true == TestBaseField::isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == TestBaseField::isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( iter == string.end() );

  iter = string.begin();
  CHECK( true == TestBaseField::isWhiteSpace( iter ) ); ++iter;
  CHECK( false == TestBaseField::isWhiteSpace( iter ) ); ++iter;
  CHECK( true == TestBaseField::isWhiteSpace( iter ) ); ++iter;
  CHECK( true == TestBaseField::isWhiteSpace( iter ) ); ++iter;
  CHECK( true == TestBaseField::isWhiteSpace( iter ) ); ++iter;
  CHECK( true == TestBaseField::isWhiteSpace( iter ) ); ++iter;
  CHECK( true == TestBaseField::isWhiteSpace( iter ) ); ++iter;
  CHECK( false == TestBaseField::isWhiteSpace( iter ) ); ++iter;
  CHECK( iter == string.end() );

  iter = string.begin();
  CHECK( false == TestBaseField::isNewLine( iter ) ); ++iter;
  CHECK( false == TestBaseField::isNewLine( iter ) ); ++iter;
  CHECK( false == TestBaseField::isNewLine( iter ) ); ++iter;
  // \n is a newline
  CHECK( true == TestBaseField::isNewLine( iter ) ); ++iter;
  // \r\n is a newline, iterator is incremented
  CHECK( iter == string.begin() + 4 );
  CHECK( true == TestBaseField::isNewLine( iter ) );
  CHECK( iter == string.begin() + 5 ); ++iter;
  // \f is a newline
  CHECK( true == TestBaseField::isNewLine( iter ) ); ++iter;
  CHECK( false == TestBaseField::isNewLine( iter ) ); ++iter;
  CHECK( iter == string.end() );

  iter = string.begin();
  CHECK( false == TestBaseField::isEndOfFile( iter ) ); ++iter;
  CHECK( false == TestBaseField::isEndOfFile( iter ) ); ++iter;
  CHECK( false == TestBaseField::isEndOfFile( iter ) ); ++iter;
  CHECK( false == TestBaseField::isEndOfFile( iter ) ); ++iter;
  CHECK( false == TestBaseField::isEndOfFile( iter ) ); ++iter;
  CHECK( false == TestBaseField::isEndOfFile( iter ) ); ++iter;
  CHECK( false == TestBaseField::isEndOfFile( iter ) ); ++iter;
  CHECK( true == TestBaseField::isEndOfFile( iter ) ); ++iter;
  CHECK( iter == string.end() );

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
