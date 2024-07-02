cmake_minimum_required( VERSION 3.27 )
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( FetchContent )
#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( FastFloat
    GIT_REPOSITORY  ../../fastfloat/fast_float
    GIT_TAG         f476bc713fda06fbd34dc621b466745a574b3d4c # tag: v6.1.1
    )

FetchContent_Declare( spdlog
    GIT_REPOSITORY  ../../gabime/spdlog
    GIT_TAG         ad0e89cbfb4d0c1ce4d097e134eb7be67baebb36 # tag: v1.11.0
    )
set( SPDLOG_BUILD_PIC CACHE INTERNAL BOOL ON )

if (tools.installation)
    set( SPDLOG_INSTALL CACHE INTERNAL BOOL ON )
else()
    set( SPDLOG_INSTALL CACHE INTERNAL BOOL OFF )
endif()

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    FastFloat
    spdlog
    )

if (tools.tests)
  FetchContent_Declare( Catch2
      GIT_REPOSITORY  ../../catchorg/Catch2
      GIT_TAG         3f0283de7a9c43200033da996ff9093be3ac84dc # tag: v3.3.2
      )
  
  FetchContent_MakeAvailable(Catch2)
endif()

if (tools.python)
  FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         5b0a6fc2017fcc176545afe3e09c9f9885283242 # tag: v2.10.4
      )
  FetchContent_MakeAvailable(pybind11)
endif()
