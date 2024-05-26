#######################################################################
# Setup
#######################################################################

enable_testing()

function( add_python_test name source )

  set( test_name "dryad.python.${name}.test" )
  add_test( NAME ${test_name}
            COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/${source}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
  set_tests_properties( ${test_name}
                        PROPERTIES ENVIRONMENT
                        PYTHONPATH=${ENDFTK_PYTHONPATH}:${SCION_PYTHONPATH}:${DRYAD_PYTHONPATH}: $ENV{PYTHONPATH})

endfunction()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding dryad Python unit testing" )

add_python_test( TabulatedCrossSection Test_dryad_TabulatedCrossSection.py )
