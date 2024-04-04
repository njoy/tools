#ifndef NJOY_TOOLS_DISCO_BASEFIXEDWIDTHFIELD
#define NJOY_TOOLS_DISCO_BASEFIXEDWIDTHFIELD

// system includes
#include <cctype>

// other includes
#include "tools/disco/BaseField.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A base class for reading fixed width data fields
 */
template < unsigned int Width >
class BaseFixedWidthField : public BaseField {

  /* fields */

protected:

  using BaseField::skipPlusSign;

  /**
   *  @brief Skip over spaces until the end of the field or until
   *         a non-space character is encountered
   */
  template < typename Iterator >
  static void skipSpaces( Iterator& iter, unsigned int& position ) {

    while( position < Width && isSpace( iter ) ) {

      ++position;
      ++iter;
    }
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
