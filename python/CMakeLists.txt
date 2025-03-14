if(tools.python)

    pybind11_add_module( tools.python
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tools.python.cpp
    )

    add_library( njoy::tools.python ALIAS tools.python )

    target_link_libraries( tools.python PRIVATE tools )
    target_include_directories( tools.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
    set_target_properties( tools.python PROPERTIES CXX_VISIBILITY_PRESET hidden)
    set_target_properties( tools.python PROPERTIES OUTPUT_NAME tools )
    set_target_properties( tools.python PROPERTIES LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR})
    set_target_properties( tools.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
    set_target_properties( tools.python PROPERTIES POSITION_INDEPENDENT_CODE ON )
    # add all .so's that are installed with njoy::tools to the installed library rpath
    set_target_properties( tools.python PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
    # add all .so's that are linked to at build time to the installed library rpath
    set_target_properties( tools.python PROPERTIES INSTALL_RPATH_USE_LINK_PATH ON)

    set(PyVersion "${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}")
    set( py_library_install_prefix ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/python${PyVersion}/site-packages )

    if (tools.installation)
        install( TARGETS tools.python LIBRARY DESTINATION ${py_library_install_prefix} )
    endif()

    message( STATUS "Building tools' python API" )

    set( TOOLS_PYTHONPATH "${CMAKE_CURRENT_BINARY_DIR}" )

    if( tools.tests )
        include( ${PROJECT_SOURCE_DIR}/cmake/unit_testing_python.cmake )
    endif()

    # generate python stubs if possible
    find_program(pybind11stubgen_exe pybind11-stubgen)

    set(stubdir "${CMAKE_CURRENT_SOURCE_DIR}/stubs/tools")
    if (pybind11stubgen_exe)
        # the following command executes the pybind11-stubgen executable found via find_program
        # and puts its terminal output into pybind11-stubgen.log in the build tree.
        # The stubs get generated in the source tree so users can determine what changes if any were made to the stubs.
        # The stubs are then copied into the build tree so developers get the stubs when using the build tree's python bindings.
        # If the stubs fail to generate then this command exits gracefully and allows the build to continue.
        add_custom_command(
            TARGET tools.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${tools_PYTHONPATH}:${tools_PYTHONPATH}:$ENV{PYTHONPATH} ${pybind11stubgen_exe} tools -o ${CMAKE_CURRENT_SOURCE_DIR}/stubs &> ${CMAKE_CURRENT_BINARY_DIR}/pybind11-stubgen.log || true
            COMMAND ${CMAKE_COMMAND} -E rename ${stubdir}/__init__.pyi ${stubdir}/tools.pyi &> /dev/null || true
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Building tools' python stub files via pybind11-stubgen. See pybind11-stubgen.log for details."
            VERBATIM
        )

    else()
        # copy stub files to build tree even if pybind11stubgen isn't available.
        add_custom_command(
            TARGET tools.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
        )
    endif()

    # install stubs so the installed binaries play nice with IDEs
    if (tools.installation)
        install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/stubs/tools/ DESTINATION ${py_library_install_prefix} )
    endif()

endif() # end tools.python check
