#ifndef NJOY_TOOLS_DISCO_BASEFIELD
#define NJOY_TOOLS_DISCO_BASEFIELD

// system includes
#include <cctype>

// other includes
#include "tools/disco/functions.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A base class for reading data fields (either fixed width or free
 *         format).
 */
class BaseField {

  /* fields */

protected:

  /* auxiliary functions */

  /**
   *  @brief Skip the '+' character
   *
   *  Note: when a plus sign is encountered, the position is incremented.
   *  In the case of a fixed width field, this may put the position over
   *  the width so this must be checked prior to calling this function.
   *
   *  @param[in,out] iter       an iterator to a character in a range
   *  @param[in,out] position   the current position in the field
   */
  template < typename Iterator >
  static void skipPlusSign( Iterator& iter, unsigned int& position ) {

    if ( *iter == '+' ) {

      ++iter;
      ++position;
    }
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
