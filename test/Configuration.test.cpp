// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/Configuration.hpp"

// other includes

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "Configuration" ) {

  std::ofstream out( "dsgdslglkjcskjdlskghlkfdh.config" );
  out << "# test config file" << std::endl;
  out << std::endl;
  out << " key1 = value1" << std::endl;
  out << "key2=value2 with some whitespace  " << std::endl;

  auto& config = Configuration::getInstance( "dsgdslglkjcskjdlskghlkfdh.config" );

  CHECK( true == config.hasKey( "key1" ) );
  CHECK( true == config.hasKey( "key2" ) );
  CHECK( false == config.hasKey( "key3" ) );

  CHECK( "value1" == config.get( "key1" ) );
  CHECK( "value2 with some whitespace" == config.get( "key2" ) );
  CHECK_THROWS( config.get( "key3" ) );

  std::remove( "dsgdslglkjcskjdlskghlkfdh.config" );
} // SCENARIO
