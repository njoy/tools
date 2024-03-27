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
  using BaseField::isWhiteSpace;
};

SCENARIO( "BaseField" ) {

  CHECK( true == TestBaseField::isSpace( ' ' ) );
  CHECK( false == TestBaseField::isSpace( 'a' ) );
  CHECK( false == TestBaseField::isSpace( '\t' ) );
  CHECK( false == TestBaseField::isSpace( '\n' ) );

  CHECK( true == TestBaseField::isSpaceOrTabulation( ' ' ) );
  CHECK( false == TestBaseField::isSpaceOrTabulation( 'a' ) );
  CHECK( true == TestBaseField::isSpaceOrTabulation( '\t' ) );
  CHECK( false == TestBaseField::isSpaceOrTabulation( '\n' ) );

  CHECK( true == TestBaseField::isWhiteSpace( ' ' ) );
  CHECK( false == TestBaseField::isWhiteSpace( 'a' ) );
  CHECK( true == TestBaseField::isWhiteSpace( '\t' ) );
  CHECK( true == TestBaseField::isWhiteSpace( '\n' ) );
} // SCENARIO
