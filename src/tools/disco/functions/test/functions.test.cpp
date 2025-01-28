// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/disco/functions.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools::disco;

SCENARIO( "functions" ) {

  std::string string = " a\t\n\r\n\f";
  string += std::char_traits<char>::eof();
  auto iter = string.begin();
  unsigned int position = 0;

  iter = string.begin();
  CHECK( true == isSpace( iter ) ); ++iter;
  CHECK( false == isSpace( iter ) ); ++iter;
  CHECK( false == isSpace( iter ) ); ++iter;
  CHECK( false == isSpace( iter ) ); ++iter;
  CHECK( false == isSpace( iter ) ); ++iter;
  CHECK( false == isSpace( iter ) ); ++iter;
  CHECK( false == isSpace( iter ) ); ++iter;
  CHECK( false == isSpace( iter ) ); ++iter;
  CHECK( iter == string.end() );

  iter = string.begin();
  CHECK( true == isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( true == isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( false == isSpaceOrTabulation( iter ) ); ++iter;
  CHECK( iter == string.end() );

  iter = string.begin();
  CHECK( true == isWhiteSpace( iter ) ); ++iter;
  CHECK( false == isWhiteSpace( iter ) ); ++iter;
  CHECK( true == isWhiteSpace( iter ) ); ++iter;
  CHECK( true == isWhiteSpace( iter ) ); ++iter;
  CHECK( true == isWhiteSpace( iter ) ); ++iter;
  CHECK( true == isWhiteSpace( iter ) ); ++iter;
  CHECK( true == isWhiteSpace( iter ) ); ++iter;
  CHECK( false == isWhiteSpace( iter ) ); ++iter;
  CHECK( iter == string.end() );

  iter = string.begin();
  CHECK( false == isNewLine( iter ) ); ++iter;
  CHECK( false == isNewLine( iter ) ); ++iter;
  CHECK( false == isNewLine( iter ) ); ++iter;
  // \n is a newline
  CHECK( true == isNewLine( iter ) ); ++iter;
  // \r\n is a newline, iterator is incremented
  CHECK( iter == string.begin() + 4 );
  CHECK( true == isNewLine( iter ) );
  CHECK( iter == string.begin() + 5 ); ++iter;
  // \f is a newline
  CHECK( true == isNewLine( iter ) ); ++iter;
  CHECK( false == isNewLine( iter ) ); ++iter;
  CHECK( iter == string.end() );

  iter = string.begin();
  CHECK( false == isEndOfFile( iter ) ); ++iter;
  CHECK( false == isEndOfFile( iter ) ); ++iter;
  CHECK( false == isEndOfFile( iter ) ); ++iter;
  CHECK( false == isEndOfFile( iter ) ); ++iter;
  CHECK( false == isEndOfFile( iter ) ); ++iter;
  CHECK( false == isEndOfFile( iter ) ); ++iter;
  CHECK( false == isEndOfFile( iter ) ); ++iter;
  CHECK( true == isEndOfFile( iter ) ); ++iter;
  CHECK( iter == string.end() );
} // SCENARIO
