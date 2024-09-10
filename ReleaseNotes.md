# Release Notes&mdash;tools
Given here are some release notes for tools.

## [tools v0.4.0](https://github.com/njoy/tools/pull/xxx)
New features:
  - added a partial implementation of the C++23 ranges standard: chunk_view, chunk_by_view, stride_view and repeat_view
  - updates to drop_view, values_view, keys_view and take _view
  - made nanorange's adjacent_find and count ranges algorithms available and provided unit tests

This update also modifies the build system to use shacl-cmake.

Note: this also contains an implementation for the C++23 zip_view and zip_transform_view but these are not entirely workign as they should and should therefore not be used.

## [ACEtk v0.3.1](https://github.com/njoy/tools/pull/41)
This updates the build system for tools and contains no functional changes.

## [ACEtk v0.3.0](https://github.com/njoy/tools/pull/23)
New features:
  - the disco tool (which replaces the njoy::disco library)
  - a partial implementation of the C++20 ranges standard (based in NanoRange to replace the range-v3 library)
  - an AnyView component for use in njoy library python bindings
  - python bindings for common AnyView types (for double, int, unsigned int, complex, etc.)

## [ACEtk v0.2.0](https://github.com/njoy/tools/pull/4)
New features:
  - the Log tool (which replaces the njoy::Log library)

## [tools v0.1.0](https://github.com/njoy/tools/pull/1)
First release of the tools library