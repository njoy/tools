#ifndef NJOY_TOOLS_DISCO_SCIENTIFIC
#define NJOY_TOOLS_DISCO_SCIENTIFIC

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
class Scientific : public Real< Width > {

  /* fields */

public:

  using Real< Width >::read;

  template< typename Representation, typename Iterator >
  static void write( Representation value, Iterator& iter ) {

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

      unsigned int precision = Width - 6;
      if ( value < 0 ) {

        precision -= 1;
      }
      if ( value != 0.0 ) {

        // log10(significand 10^exponent) = exponent + log10( significand ) and
        // log10( significand ) is within [0,1[ so that exponent is given by the
        // floor value
        const int exponent = static_cast< int >( std::floor( std::log10( absValue ) ) );
        precision -= static_cast< int >( std::floor( std::log10( std::abs( exponent ) ) ) ) - 1;
      }
      precision = std::min( precision, Precision );

      buffer << std::scientific
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
