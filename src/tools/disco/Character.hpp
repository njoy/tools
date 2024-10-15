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
 *  @brief A class for reading and writing fixed width data fields containing
 *         characters.
 */
template< unsigned int Width >
class Character : public BaseFixedWidthField< Width > {

  /* fields */

protected:

  using BaseFixedWidthField< Width >::skipSpaces;
  using BaseFixedWidthField< Width >::skipPlusSign;

public:

  /**
   *  @brief Read character data from the fixed width field
   *
   *  The resulting character data has a length equal to the width of the field.
   *  Spaces are appended to the character data if a new line character or if the
   *  end of file character is encountered.
   *
   *  @param[in,out] iter       an iterator to a character in a range
   */
  template < typename Representation, typename Iterator >
  static Representation read( Iterator& iter, const Iterator& end ) {

    Representation value;
    if ( iter >= end ) {

      return value;
    }
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

  template < typename Iterator >
  static std::string read( Iterator& iter, const Iterator& end ) {

    return read< std::string >( iter, end );
  }

  template< typename Representation, typename Iterator >
  static void write( const Representation& value, Iterator& iter ) {

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
