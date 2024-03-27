#ifndef NJOY_TOOLS_DISCO_BASEFIXEDWIDTHFIELD
#define NJOY_TOOLS_DISCO_BASEFIXEDWIDTHFIELD

// system includes
#include <cctype>

// other includes
#include "tools/disco?BaseField.hpp"

namespace njoy {
namespace tools {
namespace disco {

/**
 *  @brief A base class for reading fixed width data fields
 */
class BaseFixedWidthField : public BaseField {

  /* fields */

protected:

  using BaseField::isSpace;
  using BaseField::isSpaceOrTabulation;
  using BaseField::isWhiteSpace;
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
