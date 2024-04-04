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

  template < typename Iterator >
  static void read( Iterator& iter, const Iterator& ) {

    unsigned int position = 0;
    while( position < Width && ! ( isNewLine( iter ) || isEndOfFile( iter ) ) ) {

      ++position;
      ++iter;
    }
  }

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
