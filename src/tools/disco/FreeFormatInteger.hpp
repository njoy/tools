#ifndef NJOY_TOOLS_DISCO_FREEFORMATINTEGER
#define NJOY_TOOLS_DISCO_FREEFORMATINTEGER

// system includes
#include <cstdlib>
#include <sstream>
#include <iomanip>

// other includes
#include "fast_float/fast_float.h"
#include "tools/disco/BaseField.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A class for reading free format integer values
 */
class FreeFormatInteger : public BaseField {

  /* fields */

protected:

  using BaseField::skipPlusSign;

public:

  /**
   *  @brief Read an integer
   *
   *  @param[in,out] iter    an iterator to a character in a range
   *  @param[in,out] end     an iterator to the end of the range
   */
  template < typename Representation, typename Iterator >
  static Representation read( Iterator& iter, const Iterator& end ) {

    Representation value = 0;

    // get the size of the string in case find_if returns iter == end 
    auto dist = std::distance( iter, end );

    iter = std::find_if( iter, end,
                         [] ( auto&& value )
                            { return ! std::isspace( value ); }  );

    // if the value is not in the string, find_if returns the end of the range, in 
    // which case msvc will not allow dereferencing iter. So, throw a runtime
    // error here in that case:
    if ( iter == end ) {

        std::string message( &*(iter - dist), &*std::prev( end ) + 1 );
        message.insert( 0, "Could not read valid integer: \"" );
        message += '\"';
        throw std::runtime_error( message );
    }

    // we are using fast_float::from_chars instead of std::from_chars since
    // not all standard c++ libraries implement the floating point version of
    // std::from_chars
    if ( *iter == '+' ) { ++iter; }
    auto result = fast_float::from_chars( &*iter, &*std::prev( end ) + 1, value );
    if ( result.ec == std::errc() ) {

      auto advance = result.ptr - &*iter;
      iter += advance;
    }
    else {

      auto temp = std::find_if( iter, end,
                                [] ( auto&& value )
                                   { return std::isspace( value ); } );
      std::string message( &*iter, temp - iter );
      message.insert( 0, "Could not read valid integer: \"" );
      message += '\"';
      throw std::runtime_error( message );
    }

    return value;
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
