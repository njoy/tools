// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

// other includes
#include "tools/views/views-python.hpp"

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

  // create the views submodule
  python::module viewmodule = module.def_submodule(

    "sequence",
    "sequence - tools sequences (internal use only)"
  );

  // wrap some basic recurring views
  // none of these are supposed to be created directly by the user
  // @todo test performance against range-v3
  wrapBasicRandomAccessAnyViewOf< double >(
      viewmodule,
      "AnyRandomAccessView< double >" );
  wrapBasicRandomAccessAnyViewOf< int >(
      viewmodule,
      "AnyRandomAccessView< int >" );
  wrapBasicRandomAccessAnyViewOf< unsigned int >(
      viewmodule,
      "AnyRandomAccessView< unsigned int >" );
  wrapBasicRandomAccessAnyViewOf< long >(
      viewmodule,
      "AnyRandomAccessView< long >" );
  wrapBasicRandomAccessAnyViewOf< BasicRandomAccessAnyView< double > >(
      viewmodule,
      "any_view< any_view< double, random_access >, random_access >" );
  wrapBasicRandomAccessAnyViewOf< BasicRandomAccessAnyView< BasicRandomAccessAnyView< double > > >(
      viewmodule,
      "any_view< any_view< any_view< double, random_access >, random_access >, random_access >" );
  wrapBasicRandomAccessAnyViewOf< std::complex< double > >(
      viewmodule,
      "any_view< std::complex< double >, random_access >" );
  wrapBasicRandomAccessAnyViewOf< std::string >(
      viewmodule,
      "any_view< std::string, random_access >" );
}
