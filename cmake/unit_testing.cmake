#######################################################################
# Setup
#######################################################################

message( STATUS "Adding tools unit testing" )
enable_testing()

FetchContent_MakeAvailable( Catch2 )

function( add_cpp_test name source )

  set( test_name "tools.${name}.test" )
  add_executable( ${test_name} ${source} )
  add_test( NAME ${test_name} COMMAND ${test_name} )
  target_link_libraries( ${test_name} PRIVATE tools )
  target_link_libraries( ${test_name} PRIVATE Catch2::Catch2WithMain )

  file( GLOB resources "resources/*" )
  foreach( resource ${resources} )
    file( COPY "${resource}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
  endforeach()

endfunction()

#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/tools/Log/test )

add_subdirectory( src/tools/disco/BaseField/test )
add_subdirectory( src/tools/disco/BaseFixedWidthField/test )
add_subdirectory( src/tools/disco/FixedWidthReal/test )

add_subdirectory( src/tools/std20/algorithm/test )
add_subdirectory( src/tools/std20/concepts/test )
add_subdirectory( src/tools/std20/functional/test )
add_subdirectory( src/tools/std20/iterator/concepts/test )
add_subdirectory( src/tools/std20/iterator/operations/test )
add_subdirectory( src/tools/std20/iterator/test )
add_subdirectory( src/tools/std20/ranges/access/test )
add_subdirectory( src/tools/std20/ranges/concepts/test )
add_subdirectory( src/tools/std20/type_traits/test )
add_subdirectory( src/tools/std20/views/test )

add_subdirectory( src/tools/views/AnyIterator/test )
add_subdirectory( src/tools/views/AnyView/test )
