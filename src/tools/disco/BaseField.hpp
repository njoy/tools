#ifndef NJOY_TOOLS_DISCO_BASEFIELD
#define NJOY_TOOLS_DISCO_BASEFIELD

// system includes
#include <cctype>

// other includes

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
   *  @brief Return whether or not a character is a space
   */
  constexpr static bool isSpace( const char c ) { return c == ' '; }

  /**
   *  @brief Return whether or not a character is a space or tab
   */
  constexpr static bool isSpaceOrTabulation( const char c ) { 

    return c == ' ' || c == '\t'; 
  }

  /**
   *  @brief Return whether or not a character is a newline character
   */
  template < typename Iterator >
  constexpr static bool isNewLine( const char c, Iterator& iter ) { 

    if ( c == '\n' || c == '\f' ) {

      return true;
    }
    else if ( c == '\r' ) {

      if ( *(++iter) == '\n' ) {

        return true;
      }
      else {

        throw std::exception( "carriage return unsupported" );
      }
    }
    return c == ' ' || c == '\t'; 
  }

  /**
   *  @brief Return whether or not a character is whitespace
   *
   *  Not all implementations of std::isspace are constexpr so we cannot make 
   *  this function constexpr.
   */
  static bool isWhiteSpace( const char c ) { 

    return std::isspace( c );
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
