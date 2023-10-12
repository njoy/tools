########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )

set( subproject OFF )
if( DEFINED PROJECT_NAME )
  set( subproject ON )
endif()

project( tools
  VERSION 0.3.0
  LANGUAGES CXX
)

include( CTest )
include( CMakeDependentOption )
include( GNUInstallDirs )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

cmake_dependent_option(
  tools.tests
  "Build the tools unit tests and integrate with ctest" ON
  "BUILD_TESTING AND NOT ${subproject}" OFF
)
cmake_dependent_option(
  tools.python
  "Build tools python bindings" ON
  "NOT ${subproject}" OFF
)

########################################################################
# Dependencies
########################################################################

set( REPOSITORIES "release"
    CACHE STRING
    "Options for where to fetch repositories: develop, release, local"
    )

message( STATUS "Using ${REPOSITORIES} repositories" )

if( REPOSITORIES STREQUAL "develop" )
    include( cmake/develop_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "release" )
    include( cmake/release_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "local" )
    include( cmake/local_dependencies.cmake )

endif()


########################################################################
# Project targets
########################################################################

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# tools : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( tools INTERFACE )
add_library( njoy::tools ALIAS tools )
target_include_directories( tools
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries( tools
  INTERFACE
    spdlog::spdlog
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# tools : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( tools.python )

  FetchContent_MakeAvailable( pybind11 )

  pybind11_add_module( tools.python
      python/src/tools.python.cpp
      )

  target_link_libraries( tools.python PRIVATE tools )
  target_include_directories( tools.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( tools.python PRIVATE "-fvisibility=hidden" )
  set_target_properties( tools.python PROPERTIES OUTPUT_NAME tools )
  set_target_properties( tools.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( tools.python PROPERTIES POSITION_INDEPENDENT_CODE ON )

  message( STATUS "Building tools' python API" )

  list( APPEND SCION_PYTHONPATH ${CMAKE_CURRENT_BINARY_DIR} )

  include( cmake/unit_testing_python.cmake )

endif()

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  if( tools.tests )
    include( cmake/unit_testing.cmake )
  endif()
endif()
