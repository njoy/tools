// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes
#include "tools.views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations

/**
 *  @brief tools python bindings
 *
 *  The name given here (tools) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( tools, module ) {

  // wrap some basic recurring views
  // none of these are supposed to be created directly by the user
  wrapBasicRandomAccessAnyViewOf< double >(
      module,
      "AnyRandomAccessView< double >" );
  wrapBasicRandomAccessAnyViewOf< int >(
      module,
      "AnyRandomAccessView< int >" );
  wrapBasicRandomAccessAnyViewOf< unsigned int >(
      module,
      "AnyRandomAccessView< unsigned int >" );
  wrapBasicRandomAccessAnyViewOf< long >(
      module,
      "AnyRandomAccessView< long >" );
  wrapBasicRandomAccessAnyViewOf< BasicRandomAccessAnyView< double > >(
      module,
      "AnyRandomAccessView< AnyRandomAccessView< double > >" );
  wrapBasicRandomAccessAnyViewOf< BasicRandomAccessAnyView< BasicRandomAccessAnyView< double > > >(
      module,
      "AnyRandomAccessView< AnyRandomAccessView< AnyRandomAccessView< double > > >" );
  wrapBasicRandomAccessAnyViewOf< std::complex< double > >(
      module,
      "AnyRandomAccessView< std::complex< double >" );
}
