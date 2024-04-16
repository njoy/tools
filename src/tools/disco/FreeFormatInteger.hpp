#ifndef NJOY_TOOLS_DISCO_INTEGER
#define NJOY_TOOLS_DISCO_INTEGER

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

    iter = std::find_if( iter, end,
                         [] ( auto&& value )
                            { return ! std::isspace( value ); }  );
    if ( isEndOfFile( iter ) ) {

      throw std::runtime_error( "Cannot read valid integer: end of file encountered" );
    }

    // we are using fast_float::from_chars instead of std::from_chars since
    // not all standard c++ libraries implement the floating point version of
    // std::from_chars
    if ( *iter == '+' ) { ++iter; }
    auto result = fast_float::from_chars( &*iter, &*end, value );
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
