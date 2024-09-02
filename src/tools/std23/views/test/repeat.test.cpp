// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std23/views.hpp"

// other includes
#include <forward_list>
#include <list>
#include <vector>
#include "tools/std20/algorithm.hpp"
#include <string_view>
#include "tools/std20/iterator/unreachable.hpp"
// convenience typedefs
using namespace njoy::tools;

SCENARIO( "repeat_view" ) {
	// Use a single bound limit for all bound tests
	int boundLimit = 4;

	GIVEN( "Test repeat integer" ) {
		int repeated = 9;
		WHEN("Bound repeater"){
			auto RepeatedInt = std23::views::repeat(repeated, boundLimit);
			THEN("Check all ints in bound limit"){
				CHECK(RepeatedInt.size() == boundLimit);
				for (int i : RepeatedInt){
					CHECK(i == repeated);
				}
			} //THEN
		} //WHEN
		WHEN("Unbound repeater"){
			auto RepeatedInt = std23::views::repeat(repeated);
			THEN("Check that end is unbound and int is repeated within 2x listed limit"){
				CHECK( std20::same_as<std::remove_cv_t<decltype(std20::unreachable_sentinel)>, 
						      decltype(RepeatedInt.end())>);
				int UnboundLimit = 0; 
				for (int i : RepeatedInt){
					UnboundLimit += 1;
					CHECK(i == repeated);
					if (UnboundLimit > 2*boundLimit){
						break;
					}
				}
			} //THEN

		} //WHEN
	} //GIVEN
	GIVEN( "Test repeat float" ) {
		float repeated = 9.0;
		WHEN("Bound repeater"){
			auto RepeatedInt = std23::views::repeat(repeated, boundLimit);
			THEN("Check all ints in bound limit"){
				CHECK(RepeatedInt.size() == boundLimit);
				for (float i : RepeatedInt){
					CHECK(i == repeated);
				}
			} //THEN
		} //WHEN
		WHEN("Unbound repeater"){
			auto RepeatedInt = std23::views::repeat(repeated);
			THEN("Check that end is unbound and int is repeated within 2x listed limit"){
				CHECK( std20::same_as<std::remove_cv_t<decltype(std20::unreachable_sentinel)>, 
						      decltype(RepeatedInt.end())>);
				int UnboundLimit = 0; 
				for (float i : RepeatedInt){
					UnboundLimit += 1;
					CHECK(i == repeated);
					if (UnboundLimit > 2*boundLimit){
						break;
					}
				}
			} //THEN

		} //WHEN
	} //GIVEN
	GIVEN( "Test repeat string views" ) {
		using namespace std::literals::string_view_literals;
		WHEN("Bound repeater"){
			auto RepeatedInt = std23::views::repeat("testMe"sv, boundLimit);
			THEN("Check all ints in bound limit"){
				CHECK(RepeatedInt.size() == boundLimit);
				for (auto i : RepeatedInt){
					CHECK(i == "testMe");
				}
			} //THEN
		} //WHEN
		WHEN("Unbound repeater"){
			auto RepeatedInt = std23::views::repeat("testMe"sv);
			THEN("Check that end is unbound and int is repeated within 2x listed limit"){
				CHECK( std20::same_as<std::remove_cv_t<decltype(std20::unreachable_sentinel)>, 
						      decltype(RepeatedInt.end())>);
				int UnboundLimit = 0; 
				for (auto i : RepeatedInt){
					UnboundLimit += 1;
					CHECK(i == "testMe");
					if (UnboundLimit > 2*boundLimit){
						break;
					}
				}
			} //THEN

		} //WHEN
	} //GIVEN

} //SCENARIO

