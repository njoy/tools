#ifndef NJOY_TOOLS_DISCO_ENDF
#define NJOY_TOOLS_DISCO_ENDF

// system includes

// other includes
#include "fast_float/fast_float.h"
#include "tools/disco/BaseFixedWidthField.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A class for reading fixed width data fields containing floating
 *         point values
 */
template < unsigned int Width >
class ENDF : public BaseFixedWidthField< Width > {

  /* fields */

public:

  using Real< Width >::read;

  template< typename Representation, typename Iterator >
  static void write( Representation real, Iterator& it ) {

    const double absReal = std::abs( real );

    if ( absReal == std::numeric_limits<Representation>::infinity() ) {

      writeInfinity( it, ( real < 0 ), InfinityPrintingPolicy() );
    }
    else {

      // decompose real
      double significand = real;
      double tenToExponent = 1.;
      int exponent = 0;
      int expWidth = minExpWidth;
      if ( real != 0.0 ) {

        // log10(significand 10^exponent) = exponent + log10(significand) and
        // log10(significand) is within [0,1[ so that exponent is given by the
        // floor value
        exponent = static_cast< int >( std::floor( std::log10( absReal ) ) );

        if ( 0 != exponent ) {

          tenToExponent = std::pow( 10.0, exponent );
          significand /= tenToExponent;
          expWidth += static_cast< int >(
              std::floor( std::log10( std::abs( exponent ) ) ) );
        }
      }

      unsigned int width = w - expWidth;
      unsigned int precision = width - excluded;
      bool fixed = false;

      const double tenToPrecision = std::pow( 10.0, precision );
      const double rssignificand = std::round( significand * tenToPrecision )
                                   / tenToPrecision;

      // only check for fixed when the value is in [minFixed,maxFixed[
      if ( ( minFixed <= absReal ) and ( absReal < maxFixed ) ) {

        const double tenToFixedPrecision = std::pow( 10.0, precision + expWidth );
        const double rsreal = rssignificand * tenToExponent;
        const double rfreal = std::round( real * tenToFixedPrecision )
                              / tenToFixedPrecision;

        // only continue if fixed notation would not produce the same value
        if ( rsreal != rfreal ) {

          double max = std::pow( 10.0, expWidth );
          double remainder = std::abs( significand ) * tenToPrecision;
          remainder -= std::floor( remainder );
          remainder *= max;

          if ( ( roundoff <= remainder ) and ( remainder <= max - roundoff ) ) {

            fixed = true;
            precision += expWidth;
            width += expWidth;

            if ( exponent > static_cast< int >( precision ) ) {

              precision = 0;
            }
            else if ( 0 < exponent ) {

              precision -= exponent;
            }
          }
        }
      }

      // due to roundoff, we sometimes produce 10.+x values instead of 1.+(x+1)
      if ( not fixed ) {

        significand = rssignificand;
        if ( std::abs( rssignificand ) >= 10. ) {

          significand = significand >= 0. ? 1. : -1.;
          exponent += 1;
          if ( exponent == 10 ) {

            width -= 1;
            precision -= 1;
          }
        }
      }

      std::ostringstream buffer;
      buffer << std::setw( width ) << std::fixed << std::showpoint
             << std::right << std::setprecision( precision );
      if ( fixed ) {

        if ( 0 == precision ) {

          buffer << static_cast< int >( real );
        }
        else {

          buffer << real;
        }
      }
      else {

        buffer << significand << std::showpos << exponent;
      }

      for ( auto b : buffer.str() ) {

        *it++ = b;
      }
    }
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
