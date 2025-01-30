#ifndef NJOY_TOOLS_DISCO_INTEGER
#define NJOY_TOOLS_DISCO_INTEGER

// system includes
#include <cstdlib>
#include <sstream>
#include <iomanip>

// other includes
#include "fast_float/fast_float.h"
#include "tools/disco/BaseFixedWidthField.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A class for reading fixed width data fields containing integer values
 */
template < unsigned int Width >
class Integer : public BaseFixedWidthField< Width > {

  /* fields */

protected:

  using BaseFixedWidthField< Width >::skipSpaces;
  using BaseFixedWidthField< Width >::skipPlusSign;

  template< typename Representation >
  static constexpr int minimumRequiredWidth( Representation i ) {

    return ( i < 10 ) ? 1 : 1 + minimumRequiredWidth( i / 10 );
  }

public:

  /**
   *  @brief Read an integer from the fixed width field
   *
   *  @param[in,out] iter       an iterator to a character in a range
   */
  template < typename Representation, typename Iterator >
  static Representation read( Iterator& iter, const Iterator& end ) {

    unsigned int position = 0;
    const auto final = iter + Width;
    Representation value = 0;

    skipSpaces( iter, position );
    if ( isNewLine( iter ) || Width == position || iter >= end ) {

      return value;
    }

    skipPlusSign( iter, position );
    if ( Width == position ) {

      throw std::runtime_error( "cannot parse invalid integer number 1" );
    }

    // we are using fast_float::from_chars instead of std::from_chars since
    // not all standard c++ libraries implement the floating point version of
    // std::from_chars
    auto result = fast_float::from_chars( &*iter, &*final, value );
    if ( result.ec == std::errc() ) {

      auto advance = result.ptr - &*iter;
      iter += advance;
      position += advance;
    }
    else {

      throw std::runtime_error( "cannot parse invalid integer number 2" );
    }

    skipSpaces( iter, position );
    if ( Width != position ) {

      if ( ! isNewLine( iter ) ) {

        throw std::runtime_error( "cannot parse invalid integer number 3" );
      }
    }

    return value;
  }

  template < typename Iterator >
  static int read( Iterator& iter, const Iterator& end ) {

    return read< int >( iter, end );
  }

  /**
   *  @brief Write an integer value to the output range
   *
   *  @param[in,out] iter   an iterator to a character output range
   */
  template< typename Representation, typename Iterator >
  static void write( const Representation& value, Iterator& iter ) {

    // std::abs does not exist for all integer types (e.g. unsigned)
    const Representation absValue = value < 0 ? -value : value;
    const auto required = minimumRequiredWidth( absValue )
                        + ( value < 0 ? 1 : 0 );

    std::ostringstream buffer;
    buffer << std::right << std::setw( Width );
    if ( required > Width ) {

      buffer << std::setfill( '*' ) << '*';
    }
    else {

      buffer << value;
    }

    for ( auto b : buffer.str() ) {

      *iter++ = b;
    }
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
