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
  template < typename Iterator >
  constexpr static bool isSpace( const Iterator& iter ) { return *iter == ' '; }

  /**
   *  @brief Return whether or not a character is a space or tab
   */
  template < typename Iterator >
  constexpr static bool isSpaceOrTabulation( const Iterator& iter ) {

    const char c = *iter;
    return c == ' ' || c == '\t';
  }

  /**
   *  @brief Return whether or not a character is a newline character
   *
   *  This also checks for \r\n endline characters. In this case, the
   *  iterator is incremented by 1 to point to the \n character instead
   *  of the \r character.
   */
  template < typename Iterator >
  constexpr static bool isNewLine( Iterator& iter ) {

    const char c = *iter;
    if ( c == '\n' || c == '\f' ) {

      return true;
    }
    else if ( c == '\r' ) {

      auto current = iter;
      if ( *(++iter) == '\n' ) {

        return true;
      }
      else {

        iter = current;
        throw std::runtime_error( "carriage return unsupported" );
      }
    }
    return false;
  }

  /**
   *  @brief Return whether or not a character is whitespace
   *
   *  Not all implementations of std::isspace are constexpr so we cannot make
   *  this function constexpr.
   */
  template < typename Iterator >
  static bool isWhiteSpace( const Iterator& iter ) {

    return std::isspace( *iter );
  }

  /**
   *  @brief Return whether or not a character is the end of file character
   */
  template < typename Iterator >
  static bool isEndOfFile( const Iterator& iter ) {

    return std::char_traits< char >::eof() == *iter;
  }

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
