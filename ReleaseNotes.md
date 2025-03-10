# Release Notes&mdash;tools
Given here are some release notes for tools.

## tools v0.4.3
Bug fixes:
  - fix an issue using intel classic 2023.1.0 (compilation error on the all view)

There are no functional changes in this version.

## tools v0.4.2
This version updates the pybind11 version to 2.13.6 and makes an update to the GitHub CI file. There are no functional changes.

## tools v0.4.1
Bug fixes:
  - iterator guards were added to the disco parser to avoid valgrind errors in ENDFtk.
  - the stride_view iterator was missing the reference type, which is required to create vectors using these stride view iterators in C++17.

A few updates were made in the CMake files for Windows compilation issues. The GitHub CI was also updated: macos-14 (arm64 architecture) was added in addition to macos-13 (intel architecture).

## [tools v0.4.0](https://github.com/njoy/tools/pull/44)
New features:
  - added a partial implementation of the C++23 ranges standard: chunk_view, chunk_by_view, stride_view and repeat_view (LLVM implementations for these views were used as models for our C++17 based implementations)
  - updates to drop_view, values_view, keys_view and take _view
  - made nanorange's adjacent_find and count ranges algorithms available and provided unit tests

Bug fixes:
  - apply the ranges::range concept on the AnyView constructor taking a Container template as input (this fixes a rare compilation error encountered with the GitHub CI)

This update also modifies the build system to use shacl-cmake.

Note: this also contains an implementation for the C++23 zip_view and zip_transform_view but these are not entirely working as they should and should therefore not be used.

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