#ifndef NJOY_TOOLS_DISCO_FIXEDWIDTHSCIENTIFIC
#define NJOY_TOOLS_DISCO_FIXEDWIDTHSCIENTIFIC

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "fast_float/fast_float.h"
#include "tools/disco/BaseFixedWidthReal.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A class for reading and writing fixed width data fields containing floating
 *         point values
 */
template < unsigned int Width, unsigned int Precision >
class FixedWidthScientific : public BaseFixedWidthReal< Width > {

  /* fields */

public:

  using BaseFixedWidthReal< Width >::read;

  template< typename Representation, typename Iterator >
  static void write( Representation value, Iterator& iter ) {

    std::ostringstream buffer;
    buffer << std::setw( Width ) << std::scientific
            << std::uppercase
           << std::right << std::setprecision( Precision )
           << value;

    for ( auto b : buffer.str() ) {

      *iter++ = b;
    }
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
