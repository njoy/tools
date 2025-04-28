#######################################################################
# Setup
#######################################################################

enable_testing()

function( add_python_test name source )

  set(PYTHONPATH_PARTS ${TOOLS_PYTHONPATH} $ENV{PYTHONPATH})
  string( JOIN "${PATH_DELIM}" PYTHONPATH_VALUE ${PYTHONPATH_PARTS})

  set( test_name "tools.python.${name}.test" )
  add_test( NAME ${test_name}
            COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/${source}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
  set_tests_properties( ${test_name}
                        PROPERTIES ENVIRONMENT
                        "PYTHONPATH=${PYTHONPATH_VALUE}")

endfunction()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding tools Python unit testing" )
