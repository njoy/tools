#ifndef NJOY_TOOLS_DISCO_ENDF
#define NJOY_TOOLS_DISCO_ENDF

// system includes
#include <sstream>
#include <iomanip>

// other includes
#include "tools/disco/Real.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A class for reading and writing fixed ENDF style floating point values
 *
 *  This switches between scientific and fixed notation to maximise the precision
 *  of the numbers printed.
 */
class ENDF : public Real< 11 > {

  /* fields */

  // an ENDF field is 11 wide
  static constexpr int w = 11;
  // below this value, you loose precision if fixed notation is used:
  static constexpr double minFixed = 0.1;
  // above this value, you loose precision if fixed notation is used
  static constexpr double maxFixed = 1e+10;
  // roundoff
  static constexpr double roundoff = 0.5;
  // minimal exponent width (sign, one digit)
  static constexpr int minExpWidth = 2;
  // characters excluded for fixed notation precision (optional sign,
  // first digit, decimal point)
  static constexpr int excluded = 3;

public:

  using Real< 11 >::read;

  template< typename Representation, typename Iterator >
  static void write( Representation value, Iterator& it ) {

    const double absValue = std::abs( value );
    std::ostringstream buffer;

    if ( absValue == std::numeric_limits< Representation >::infinity() ) {

      buffer << std::right << std::setw( w );
      if ( value < 0 ) {

        buffer << "-Inf";
      }
      else {

        buffer << "Inf";
      }
    }
    else {

      // decompose value
      double significand = value;
      double tenToExponent = 1.;
      int exponent = 0;
      int expWidth = minExpWidth;
      if ( value != 0.0 ) {

        // log10(significand 10^exponent) = exponent + log10(significand) and
        // log10(significand) is within [0,1[ so that exponent is given by the
        // floor value
        exponent = static_cast< int >( std::floor( std::log10( absValue ) ) );

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
      if ( ( minFixed <= absValue ) and ( absValue < maxFixed ) ) {

        const double tenToFixedPrecision = std::pow( 10.0, precision + expWidth );
        const double rsreal = rssignificand * tenToExponent;
        const double rfreal = std::round( value * tenToFixedPrecision )
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

      buffer << std::setw( width ) << std::fixed << std::showpoint
             << std::right << std::setprecision( precision );
      if ( fixed ) {

        if ( 0 == precision ) {

          buffer << static_cast< int >( value );
        }
        else {

          buffer << value;
        }
      }
      else {

        buffer << significand << std::showpos << exponent;
      }
    }

    for ( auto b : buffer.str() ) {

      *it++ = b;
    }
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
