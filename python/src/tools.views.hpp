#ifndef NJOY_TOOLS_PYTHON_VIEWS
#define NJOY_TOOLS_PYTHON_VIEWS

// system includes
#include <complex>

// other includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "tools/ranges/AnyView.hpp"

namespace python = pybind11;

/**
 *  @brief Type aliases for basic any views
 *
 *  The Element template represents the type of the any_view element.
 */
template < typename Element >
using BasicInputAnyView = njoy::tools::ranges::AnyInputView< Element >;
template < typename Element >
using BasicForwardAnyView = njoy::tools::ranges::AnyForwardView< Element >;
template < typename Element >
using BasicBidirectionalAnyView = njoy::tools::ranges::AnyBidirectionalView< Element >;
template < typename Element >
using BasicRandomAccessAnyView = njoy::tools::ranges::AnyRandomAccessView< Element >;

/**
 *  @brief Type aliases for any views using a reference wrapper to a const
 *         Element
 *
 *  The resulting any_view contains std::reference_wrapper< const Element >
 *  instead of just Element to fix an issue with any_views. Views already
 *  containing reference wrappers (e.g. variants of reference wrappers) should
 *  continue to use the Basic... versions of the any views.
 */
template < typename Element >
using RefWrapper = std::reference_wrapper< const Element >;
template < typename Element >
using InputAnyView = BasicInputAnyView< RefWrapper< Element > >;
template < typename Element >
using ForwardAnyView = BasicForwardAnyView< RefWrapper< Element > >;
template < typename Element >
using BidirectionalAnyView = BasicBidirectionalAnyView< RefWrapper< Element > >;
template < typename Element >
using RandomAccessAnyView = BasicRandomAccessAnyView< RefWrapper< Element > >;

/**
 *  @brief Some recurring basic views
 */
using DoubleRange = BasicRandomAccessAnyView< double >;
using LongRange = BasicRandomAccessAnyView< long >;
using IntRange = BasicRandomAccessAnyView< int >;
using UnsignedIntRange = BasicRandomAccessAnyView< unsigned int >;
using DoubleRange2D = BasicRandomAccessAnyView< DoubleRange >;
using DoubleRange3D = BasicRandomAccessAnyView< DoubleRange2D >;
using ComplexRange = BasicRandomAccessAnyView< std::complex< double > >;

/**
 *  @brief Wrap a BasicBidirectionalAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element, typename CopyElement = Element >
void wrapBasicBidirectionalAnyViewOf( python::module& module, const std::string& name ) {

  python::class_< BasicBidirectionalAnyView< Element > >( module, name.c_str() )
  .def( "__len__",
        [] ( BasicBidirectionalAnyView< Element >& view )
           { return view.size(); },
        "Return the length of the sequence" )
  .def( "__iter__",
        [] ( BasicBidirectionalAnyView< Element >& view )
           { return python::make_iterator<
                        python::return_value_policy::reference_internal,
                        typename BasicBidirectionalAnyView< Element >::iterator,
                        typename BasicBidirectionalAnyView< Element >::iterator,
                        Element >( view.begin(), view.end() ); },
        "Return an iterator for the sequence",
        python::keep_alive< 0, 1 >() )
  .def( "front",
        [] ( BasicBidirectionalAnyView< Element >& view )
           { return view.front(); },
        "Return the front element of the sequence",
        python::keep_alive< 0, 1 >() )
  .def( "to_list",
        [] ( BasicBidirectionalAnyView< Element >& view )
           -> std::vector< Element >
           { return std::vector< Element >( view.begin(), view.end() ); },
        "Convert the sequence to a list (this is a deep copy for primitive\n"
        "types (like integer and floats) and a shallow copy for custom types" )
  .def( "copy",
      	[] ( BasicRandomAccessAnyView< Element >& view )
           -> std::vector< CopyElement >
           { return std::vector< CopyElement >( view.begin(), view.end() ); },
        "Copy the sequence to a list (this is a deep copy for both primitive\n"
        "types (like integer and floats) and custom types" );
}

/**
 *  @brief Wrap a BasicRandomAccessAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element, typename CopyElement = Element >
void wrapBasicRandomAccessAnyViewOf( python::module& module, const std::string& name ) {

  auto index = [] ( auto i, auto length ) {

      if ( i < 0 ) {

          i += length;
      }
      if ( i < 0 || i >= length ) {

          throw python::index_error();
      }
      return i;
  };

  python::class_< BasicRandomAccessAnyView< Element > >( module, name.c_str() )
  .def( "__len__",
        [] ( BasicRandomAccessAnyView< Element >& view )
           { return view.size(); },
        "Return the length of the sequence" )
  .def( "__getitem__",
        [index] ( BasicRandomAccessAnyView< Element >& view, int i ) {

          return view[i];
        },
        "Return the value in the sequence at the given index or throw an\n"
        "exception when the index is out of range",
   	    python::return_value_policy::reference_internal )
  .def( "__getitem__",
        [] ( BasicRandomAccessAnyView< Element >& view,
             const python::slice& slice ) {

          python::size_t start, stop, step, length;
          if ( !slice.compute( view.size(),
                               &start, &stop, &step, &length ) ) {

            throw python::error_already_set();
          }
          std::vector< Element > list;
          for ( unsigned int i = 0; i < length; ++i ) {

             list.emplace_back( view[start] );
             start += step;
          }
          return list;
        },
        "Return a list corresponding to the sliced sequence or throw an\n"
        "exception when the slice is invalid. The resulting list is a deep\n"
        "copy for primitive types (like integer and floats) and a shallow\n"
        "copy for custom types",
        python::return_value_policy::reference_internal )
  .def( "__iter__",
        [] ( BasicRandomAccessAnyView< Element >& view )
           { return python::make_iterator<
                        python::return_value_policy::reference_internal,
                        typename BasicRandomAccessAnyView< Element >::iterator,
                        typename BasicRandomAccessAnyView< Element >::iterator,
                        Element >( view.begin(), view.end() ); },
        "Return an iterator for the sequence",
        python::keep_alive< 0, 1 >() )
  .def( "front",
        [] ( BasicRandomAccessAnyView< Element >& view )
           { return view.front(); },
        "Return the front element of the sequence",
        python::keep_alive< 0, 1 >() )
  .def( "to_list",
      	[] ( BasicRandomAccessAnyView< Element >& view )
           -> std::vector< Element >
           { return std::vector< Element >( view.begin(), view.end() ); },
        "Convert the sequence to a list (this is a deep copy for primitive\n"
        "types (like integer and floats) and a shallow copy for custom types" )
  .def( "copy",
      	[] ( BasicRandomAccessAnyView< Element >& view )
           -> std::vector< Element >
           { return std::vector< Element >( view.begin(), view.end() ); },
        "Copy the sequence to a list (this is a deep copy for both primitive\n"
        "types (like integer and floats) and custom types" );
}

/**
 *  @brief Wrap a BidirectionalAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element >
void wrapBidirectionalAnyViewOf( python::module& module, const std::string& name ) {

  wrapBasicBidirectionalAnyViewOf< RefWrapper< Element >, Element >( module, name );
}

/**
 *  @brief Wrap a RandomAccessAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element >
void wrapRandomAccessAnyViewOf( python::module& module, const std::string& name ) {

  wrapBasicRandomAccessAnyViewOf< RefWrapper< Element >, Element >( module, name );
}

#endif
