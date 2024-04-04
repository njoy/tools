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
