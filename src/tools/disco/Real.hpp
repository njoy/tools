#ifndef NJOY_TOOLS_DISCO_REAL
#define NJOY_TOOLS_DISCO_REAL

// system includes

// other includes
#include "fast_float/fast_float.h"
#include "tools/disco/BaseFixedWidthField.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A class for reading fixed width data fields containing floating
 *         point values
 */
template < unsigned int Width >
class Real : public BaseFixedWidthField< Width > {

  /* fields */

protected:

  using BaseFixedWidthField< Width >::skipSpaces;
  using BaseFixedWidthField< Width >::skipPlusSign;

public:

  /**
   *  @brief Read a floating point value from the fixed width field
   *
   *  @param[in,out] iter       an iterator to a character in a range
   */
  template < typename Representation, typename Iterator >
  static Representation read( Iterator& iter, const Iterator& end ) {

    unsigned int position = 0;
    Representation value = 0.0;

    skipSpaces( iter, position );
    if ( iter >= end || isNewLine( iter ) || Width == position ) {

      return value;
    }

    skipPlusSign( iter, position );
    if ( Width == position ) {

      throw std::runtime_error( "cannot parse invalid real number 1" );
    }

    // we are using fast_float::from_chars_advanced instead of std::from_chars
    // since not all standard c++ libraries implement the floating point version
    // of std::from_chars and because this allows us to read fortran formatted
    // floats
    fast_float::parse_options options{ fast_float::chars_format::fortran };
    auto result = fast_float::from_chars_advanced( &*iter, &*std::prev( end ) + 1, value, options);
    if ( result.ec == std::errc() ) {

      auto advance = result.ptr - &*iter;
      iter += advance;
      position += advance;
    }
    else {

      throw std::runtime_error( "cannot parse invalid real number 2" );
    }

    skipSpaces( iter, position );
    if ( Width != position ) {

      if ( ! isNewLine( iter ) ) {

        throw std::runtime_error( "cannot parse invalid real number 3" );
      }
    }

    return value;
  }

  template < typename Iterator >
  static double read( Iterator& iter, const Iterator& end ) {

    return read< double >( iter, end );
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
