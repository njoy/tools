#ifndef NJOY_TOOLS_DISCO_CHARACTER
#define NJOY_TOOLS_DISCO_CHARACTER

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
class Character : public BaseFixedWidthField< Width > {

  /* fields */

protected:

  using BaseFixedWidthField< Width >::skipSpaces;
  using BaseFixedWidthField< Width >::skipPlusSign;

public:

  template < typename Iterator >
  static std::string read( Iterator& iter, const Iterator& ) {

    std::string value;
    value.reserve( Width );

    unsigned int position = 0;
    while( position < Width && ! ( isNewLine( iter ) || isEndOfFile( iter ) ) ) {

      ++position;
      value.push_back( *iter++ );
    }
    while ( position < Width ) {

      ++position;
      value.push_back( ' ' );
    }

    return value;
  }

  template< typename Iterator >
  static void write( const std::string& value, Iterator& iter ) {

    unsigned int position = 0;
    const unsigned int difference = value.size() >= Width ? 0 : Width - value.size();
    while ( position < difference ) {

      ++position;
      *iter++ = ' ';
    }
    auto viter = value.begin();
    while ( position < Width ) {

      ++position;
      *iter++ = *viter++;
    }
  }
  };

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
