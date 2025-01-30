#ifndef NJOY_TOOLS_DISCO_FREEFORMATCHARACTER
#define NJOY_TOOLS_DISCO_FREEFORMATCHARACTER

// system includes
#include <cstdlib>
#include <sstream>
#include <iomanip>

// other includes
#include "fast_float/fast_float.h"
#include "tools/disco/BaseField.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A class for reading free format string values
 */
class FreeFormatCharacter : public BaseField {

  /* fields */

public:

  /**
   *  @brief Read a string
   *
   *  @param[in,out] iter    an iterator to a character in a range
   *  @param[in,out] end     an iterator to the end of the range
   */
  template < typename Representation, typename Iterator >
  static Representation read( Iterator& iter, const Iterator& end ) {

    iter = std::find_if( iter, end,
                         [] ( auto&& value )
                            { return ! std::isspace( value ); }  );

    auto temp = std::find_if( iter, end,
                              [] ( auto&& value )
                                 { return std::isspace( value ); }  );
    Representation value( &*iter, temp - iter );
    iter = temp;
    return value;
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
