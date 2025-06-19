########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.27 )

set( subproject OFF )
if( DEFINED PROJECT_NAME )
  set( subproject ON )
endif()

project( tools
  VERSION 0.4.4
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
  "NOT ${subproject} OR DEFINED require.tools.python " OFF
)

option( tools.installation "Install njoy::tools" ON )

########################################################################
# Dependencies
########################################################################

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( cmake/dependencies.cmake )

########################################################################
# Project targets
########################################################################

string( CONCAT prefix
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# tools : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( tools INTERFACE )
add_library( njoy::tools ALIAS tools )

target_include_directories( tools INTERFACE ${prefix} )

target_link_libraries( tools
  INTERFACE
    spdlog::spdlog
    FastFloat::fast_float
)

target_compile_definitions( tools INTERFACE -DNANORANGE_NO_STD_FORWARD_DECLARATIONS )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# tools : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( tools.python )
  add_subdirectory( python )
endif()

if( tools.tests )
  add_subdirectory( test )
endif()

#######################################################################
# Installation
#######################################################################

if(tools.installation)
    include(CMakePackageConfigHelpers)

    install(TARGETS tools EXPORT tools-targets
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )

    install(EXPORT tools-targets
      FILE "tools-targets.cmake"
      NAMESPACE njoy::
      DESTINATION share/cmake/tools
    )

    install(DIRECTORY src/
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
      FILES_MATCHING PATTERN "*.hpp"
      PATTERN "*test*" EXCLUDE
    )

    write_basic_package_version_file("tools-config-version.cmake"
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY AnyNewerVersion)

    configure_package_config_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tools-config.cmake.in
      ${PROJECT_BINARY_DIR}/tools-config.cmake
      INSTALL_DESTINATION share/cmake/tools
    )

    install(FILES
      "${PROJECT_BINARY_DIR}/tools-config.cmake"
      "${PROJECT_BINARY_DIR}/tools-config-version.cmake"
      DESTINATION share/cmake/tools
    )

    if(NOT subproject)
      set(CPACK_PACKAGE_VENDOR "Los Alamos National Laboratory")
      set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
      include(CPack)
    endif()
endif()

########################################################################
# Windows-specific setup
########################################################################

# enable Edit and Continue in Visual Studio (for debugging)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(MSVC)
      target_compile_options(${PROJECT_NAME}  INTERFACE "/ZI")
      target_link_options(${PROJECT_NAME} INTERFACE "/INCREMENTAL")
    endif()
endif()
