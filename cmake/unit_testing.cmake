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

add_subdirectory( src/tools/concepts/Requires/test )
add_subdirectory( src/tools/concepts/IsRange/test )
add_subdirectory( src/tools/concepts/IsIterator/test )

add_subdirectory( src/tools/ranges/IteratorView/test )
add_subdirectory( src/tools/ranges/TransformIterator/test )
add_subdirectory( src/tools/ranges/make_view/test )
add_subdirectory( src/tools/ranges/make_transform_view/test )
