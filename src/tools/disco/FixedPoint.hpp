#ifndef NJOY_TOOLS_DISCO_FIXEDPOINT
#define NJOY_TOOLS_DISCO_FIXEDPOINT

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "fast_float/fast_float.h"
#include "tools/disco/Real.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A class for reading and writing fixed width data fields containing floating
 *         point values
 */
template < unsigned int Width, unsigned int Precision >
class FixedPoint : public Real< Width > {

  /* fields */

public:

  using Real< Width >::read;

  template< typename Representation, typename Iterator >
  static void write( const Representation& value, Iterator& iter ) {

    const double absValue = std::abs( value );

    std::ostringstream buffer;
    buffer << std::right << std::setw( Width );

    if ( absValue == std::numeric_limits< Representation >::max() ) {

      if ( value < 0 ) {

        buffer << "-Inf";
      }
      else {

        buffer << "Inf";
      }
    }
    else {

      unsigned int precision = Width - 1;
      if ( value < 0 ) {

        precision -= 1;
      }
      precision = std::min( precision, Precision );

      buffer << std::fixed
             << std::uppercase
             << std::setprecision( precision )
             << value;
    }

    for ( auto b : buffer.str() ) {

      *iter++ = b;
    }
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
