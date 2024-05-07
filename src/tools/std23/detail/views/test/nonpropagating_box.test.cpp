// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std23/detail/views/nonpropagating_box.hpp"

// other includes
#include <vector>

// convenience typedefs
using namespace njoy::tools;

SCENARIO( "nonpropagating_box" ) {

  std::vector< double > values = { 1., 2., 3., 4. };
  using Iterator = std::vector< double >::iterator;

  THEN( "the default constructor makes an empty box" ) {

    // default constructor: no content
    std23::ranges::detail::nonpropagating_box< Iterator > box;
    CHECK( false == box.has_value() );
  } // THEN

  THEN( "emplace sets the content in the box" ) {

    std23::ranges::detail::nonpropagating_box< Iterator > box;
    CHECK( false == box.has_value() );

    // emplace
    auto value = box.emplace( values.begin() );
    CHECK( true == box.has_value() );
    CHECK( values.begin() == value );
    CHECK( values.begin() == *box );
  } // THEN

  THEN( "copy constructor" ) {

    std23::ranges::detail::nonpropagating_box< Iterator > box;
    box.emplace( values.begin() );

    // copy construction: other has no content, box unchanged
    std23::ranges::detail::nonpropagating_box< Iterator > other( box );
    CHECK( false == other.has_value() );
    CHECK( true == box.has_value() );
  } // THEN

  THEN( "move constructor" ) {

    std23::ranges::detail::nonpropagating_box< Iterator > box;
    box.emplace( values.begin() );

    // move construction: other has no content, box reset
    std23::ranges::detail::nonpropagating_box< Iterator > other( std::move( box ) );
    CHECK( false == other.has_value() );
    CHECK( false == box.has_value() );
  } // THEN

  THEN( "copy assignment" ) {

    std23::ranges::detail::nonpropagating_box< Iterator > box, other;
    box.emplace( values.begin() );
    other.emplace( values.end() );
    CHECK( true == box.has_value() );
    CHECK( true == other.has_value() );

    // copy assignment: reset the content of other, box unchanged
    other = box;
    CHECK( true == box.has_value() );
    CHECK( false == other.has_value() );
  } // THEN

  THEN( "move assignment" ) {

    std23::ranges::detail::nonpropagating_box< Iterator > box, other;
    box.emplace( values.begin() );
    other.emplace( values.end() );
    CHECK( true == box.has_value() );
    CHECK( true == other.has_value() );

    // move assignment: reset the content of other and box
    other = std::move( box );
    CHECK( false == box.has_value() );
    CHECK( false == other.has_value() );
  } // THEN
} // SCENARIO
