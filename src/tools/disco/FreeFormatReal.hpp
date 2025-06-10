#ifndef NJOY_TOOLS_DISCO_FREEFORMATREAL
#define NJOY_TOOLS_DISCO_FREEFORMATREAL

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
class FreeFormatReal : public BaseField {

  /* fields */

protected:

  using BaseField::skipPlusSign;

public:

  /**
   *  @brief Read a floating point value
   *
   *  @param[in,out] iter    an iterator to a character in a range
   *  @param[in,out] end     an iterator to the end of the range
   */
  template < typename Representation, typename Iterator >
  static Representation read( Iterator& iter, const Iterator& end ) {

    Representation value = 0;

    // copy the start before find_if modifies iter
    auto start = iter;

    iter = std::find_if( iter, end,
                         [] ( auto&& value )
                            { return ! std::isspace( value ); }  );

    // if the value is not in the string, find_if returns the end of the range, in 
    // which case msvc will not allow dereferencing iter. So, throw a runtime
    // error here in that case:
    if ( iter == end ) {

        std::string message( &*start, &*std::prev( end ) + 1 );
        message.insert( 0, "Could not read valid real value: " );
        message += '\"';
        throw std::runtime_error( message );
    }

    // we are using fast_float::from_chars_advanced instead of std::from_chars
    // since not all standard c++ libraries implement the floating point version
    // of std::from_chars and because this allows us to read fortran formatted
    // floats
    if ( *iter == '+' ) { ++iter; }
    fast_float::parse_options options{ fast_float::chars_format::fortran };
    auto result = fast_float::from_chars_advanced( &*iter, &*std::prev( end ) + 1, value, options );
    if ( result.ec == std::errc() ) {

      auto advance = result.ptr - &*iter;
      iter += advance;
    }
    else {

      auto temp = std::find_if( iter, end,
                                [] ( auto&& value )
                                   { return std::isspace( value ); } );
      std::string message( &*iter, temp - iter );
      message.insert( 0, "Could not read valid real value: " );
      throw std::runtime_error( message );
    }

    return value;
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
