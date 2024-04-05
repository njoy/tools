#ifndef NJOY_TOOLS_DISCO_INTEGER
#define NJOY_TOOLS_DISCO_INTEGER

// system includes
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

public:

  template < typename Representation, typename Iterator >
  static Representation read( Iterator& iter, const Iterator& ) {

    unsigned int position = 0;
    const auto end = iter + Width;
    Representation value = 0;

    skipSpaces( iter, position );
    if ( isNewLine( iter ) || isEndOfFile( iter ) || Width == position ) {

      return value;
    }

    skipPlusSign( iter, position );
    if ( Width == position ) {

      throw std::runtime_error( "cannot parse invalid integer number 1" );
    }

    // we are using fast_float::from_chars instead of std::from_chars since
    // not all standard c++ libraries implement the floating point version of
    // std::from_chars
    auto result = fast_float::from_chars( &*iter, &*end, value );
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

      if ( ! isNewLine( iter ) && ! isEndOfFile( iter ) ) {

        throw std::runtime_error( "cannot parse invalid integer number 3" );
      }
    }

    return value;
  }

  template < typename Iterator >
  static int read( Iterator& iter, const Iterator& end ) {

        return read< int >( iter, end );
  }

  template< typename Representation, typename Iterator >
  static void write( const Representation& value, Iterator& iter ) {

    std::ostringstream buffer;
    buffer << std::right << std::setw( Width ) << value;

    for ( auto b : buffer.str() ) {

      *iter++ = b;
    }
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
