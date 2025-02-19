cmake_minimum_required( VERSION 3.27 )
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( shacl_FetchContent )
#######################################################################
# Declare project dependencies
#######################################################################

shacl_FetchContent_Declare( FastFloat
    GIT_REPOSITORY  ../../fastfloat/fast_float
    GIT_TAG         00c8c7b0d5c722d2212568d915a39ea73b08b973 # tag: v6.1.6
    )

shacl_FetchContent_Declare( spdlog
    GIT_REPOSITORY  ../../gabime/spdlog
    GIT_TAG         27cb4c76708608465c413f6d0e6b8d99a4d84302 # tag: v1.14.1
    )
set( SPDLOG_BUILD_PIC CACHE INTERNAL BOOL ON )
# thenext line prevents spdlog from populating the .cmake/packages folder
set( CMAKE_EXPORT_NO_PACKAGE_REGISTRY ON )

if (tools.installation)
    set( SPDLOG_INSTALL CACHE INTERNAL BOOL ON )
else()
    set( SPDLOG_INSTALL CACHE INTERNAL BOOL OFF )
endif()

#######################################################################
# Load dependencies
#######################################################################

shacl_FetchContent_MakeAvailable(
    FastFloat
    spdlog
    )

if (tools.tests)
  shacl_FetchContent_Declare( Catch2
      GIT_REPOSITORY  ../../catchorg/Catch2
      GIT_TAG         3f0283de7a9c43200033da996ff9093be3ac84dc # tag: v3.3.2
      )

  shacl_FetchContent_MakeAvailable(Catch2)
endif()

if (tools.python)
  shacl_FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         a2e59f0e7065404b44dfe92a28aca47ba1378dc4 # tag: v2.13.6
      )
  shacl_FetchContent_MakeAvailable(pybind11)
endif()
