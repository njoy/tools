cmake_minimum_required( VERSION 3.24 )
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( shacl_FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

shacl_FetchContent_Declare( Catch2
    GIT_REPOSITORY  ../../catchorg/catch2
    GIT_TAG         v3.3.2
    GIT_SHALLOW     TRUE
    )

shacl_FetchContent_Declare( pybind11
    GIT_REPOSITORY  ../../pybind/pybind11
    GIT_TAG         v2.10.4
    GIT_SHALLOW     TRUE
    )

shacl_FetchContent_Declare( FastFloat
    GIT_REPOSITORY  https://github.com/fastfloat/fast_float
    GIT_TAG         v6.1.1
    GIT_SHALLOW     TRUE
    )

shacl_FetchContent_Declare( spdlog
    GIT_REPOSITORY  ../../gabime/spdlog
    GIT_TAG         v1.11.0
    GIT_SHALLOW     TRUE
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

shacl_FetchContent_MakeAvailable(
    spdlog
    FastFloat
    )
