#ifndef NJOY_TOOLS_DISCO_COLUMN
#define NJOY_TOOLS_DISCO_COLUMN

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/BaseFixedWidthField.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A class for reading and writing fixed width data fields containing floating
 *         point values
 */
template< unsigned int Width >
class Column : public BaseFixedWidthField< Width > {

  /* fields */

protected:

  using BaseFixedWidthField< Width >::skipSpaces;
  using BaseFixedWidthField< Width >::skipPlusSign;

public:

  /**
   *  @brief Read over columns
   *
   *  This skips over the width of the field, or until a new line or
   *  end of file character are encountered.
   *
   *  @param[in,out] iter   an iterator to a character in a range
   */
  template < typename Iterator >
  static void read( Iterator& iter, const Iterator& ) {

    unsigned int position = 0;
    while( position < Width && ! ( isNewLine( iter ) || isEndOfFile( iter ) ) ) {

      ++position;
      ++iter;
    }
  }

  /**
   *  @brief Write columns to the output range
   *
   *  @param[in,out] iter   an iterator to a character output range
   */
  template< typename Iterator >
  static void write( Iterator& iter ) {

    unsigned int position = 0;
    while ( position < Width ) {

      ++position;
      *iter++ = ' ';
    }
  }
  };

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
