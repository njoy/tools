#ifndef NJOY_TOOLS_DISCO_FIXEDWIDTHREAL
#define NJOY_TOOLS_DISCO_FIXEDWIDTHREAL

// system includes
#include <iostream>

// other includes
#include "fast_float/fast_float.h"
#include "tools/disco/BaseFixedWidthField.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A base class for reading fixed width data fields
 */
template < unsigned int Width >
class FixedWidthReal : public BaseFixedWidthField< Width > {

  /* fields */

protected:

  using BaseFixedWidthField< Width >::isSpace;
  using BaseFixedWidthField< Width >::isSpaceOrTabulation;
  using BaseFixedWidthField< Width >::isWhiteSpace;
  using BaseFixedWidthField< Width >::isNewLine;
  using BaseFixedWidthField< Width >::isEndOfFile;
  using BaseFixedWidthField< Width >::skipSpaces;
  using BaseFixedWidthField< Width >::skipPlusSign;

public:

  template < typename Representation, typename Iterator >
  static Representation read( Iterator& iter, const Iterator& ) {

    unsigned int position = 0;
    const auto end = iter + Width;
    Representation value = 0.0;

    skipSpaces( iter, position );
    if ( isNewLine( iter ) || isEndOfFile( iter ) ) {

      return value;
    }
    if ( Width == position ) {

      ++iter;
      return value;
    }

    skipPlusSign( iter, position );
    if ( Width == position ) {

      throw std::runtime_error( "cannot parse invalid real number 1" );
    }

    auto result = fast_float::from_chars( &*iter, &*end, value );
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

      throw std::runtime_error( "cannot parse invalid real number 3" );
    }

    return value;
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
