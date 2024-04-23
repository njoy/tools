#ifndef NJOY_TOOLS_DISCO_FIXEDPOINT
#define NJOY_TOOLS_DISCO_FIXEDPOINT

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/Real.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A class for reading and writing fixed width data fields containing
 *         floating point values
 *
 *  Floating point values can be read in any format but are written out
 *  in fixed notation.
 */
template < unsigned int Width, unsigned int Precision >
class FixedPoint : public Real< Width > {

  /* fields */

  /* auxiliary functions */

  template< typename T, typename Integer >
  static constexpr T pow( T real, Integer power ) {

    return
      ( power < 0 )          ? 1.0 / pow( real, -power ) :
      ( power == 0 )         ? 1.0 :
      ( power == 1 )         ? real :
      ( ( power % 2 ) == 0 ) ? pow( real * real , power / 2 ) :
                               real * pow( real, power - 1 );
  }

  /* constants */

  // min and max value beyond which we cannot write in the requested precision
  static constexpr double minFixed = -pow( 10., Width - Precision - 2 );
  static constexpr double maxFixed = pow( 10., Width - Precision - 1 );

public:

  using Real< Width >::read;

  /**
   *  @brief Write a floating point value to the output range using
   *         fixed point notation
   *
   *  @param[in,out] iter   an iterator to a character output range
   */
  template< typename Representation, typename Iterator >
  static void write( const Representation& value, Iterator& iter ) {

    const Representation absValue = std::abs( value );

    std::ostringstream buffer;
    buffer << std::right << std::setw( Width );

    if ( absValue == std::numeric_limits< Representation >::infinity() ) {

      if ( value < 0 ) {

        buffer << "-Inf";
      }
      else {

        buffer << "Inf";
      }
    }
    else {

      if ( ( minFixed >= value ) || ( maxFixed <= value ) ) {

        buffer << std::setfill( '*' ) << '*';
      }
      else {

        unsigned int precision = Width - 1;
        if ( value < 0 ) {

          precision -= 1;
        }
        precision = std::min( precision, Precision );

        buffer << std::fixed
               << std::setprecision( precision )
               << value;
      }
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
