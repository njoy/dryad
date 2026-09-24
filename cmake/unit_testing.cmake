#######################################################################
# Setup
#######################################################################

enable_testing()

FetchContent_MakeAvailable( Catch2 )

function( add_cpp_test name source )

  set( test_name "njoy.${name}.test" )
  add_executable( ${test_name} ${source} )
  add_test( NAME ${test_name} COMMAND ${test_name} )
  target_link_libraries( ${test_name} PRIVATE njoy )
  target_link_libraries( ${test_name} PRIVATE Catch2::Catch2WithMain )

  file( GLOB resources "resources/*" )
  foreach( resource ${resources} )
    file( COPY "${resource}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
  endforeach()

endfunction()

#######################################################################
# Unit testing directories
#######################################################################

message( STATUS "Adding njoy C++ unit testing" )

add_cpp_test( format.endf.read.resonances.urr.caseA.createCompoundSystem                     format/endf/read/resonances/urr/caseA/createCompoundSystem.test.cpp )
add_cpp_test( format.endf.read.resonances.urr.caseB.createCompoundSystem                     format/endf/read/resonances/urr/caseB/createCompoundSystem.test.cpp )
add_cpp_test( format.endf.read.resonances.urr.caseC.createCompoundSystem                     format/endf/read/resonances/urr/caseC/createCompoundSystem.test.cpp )
