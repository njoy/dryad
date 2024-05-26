########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.14 )

set( subproject OFF )
if( DEFINED PROJECT_NAME )
  set( subproject ON )
endif()

project( dryad
  VERSION 0.1.0
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
  dryad.tests
  "Build the dryad unit tests and integrate with ctest" ON
  "BUILD_TESTING AND NOT ${subproject}" OFF
)
cmake_dependent_option(
  dryad.python
  "Build dryad python bindings" ON
  "NOT ${subproject}" OFF
)
if ( dryad.python )
  set( require.scion.python CACHE BOOL ON )
  set( require.ENDFtk.python CACHE BOOL ON )
endif()

########################################################################
# Dependencies
########################################################################

set( REPOSITORIES "release"
    CACHE STRING
    "Options for where to fetch repositories: develop, release, local"
    )

message( STATUS "Using ${REPOSITORIES} repositories" )

if( REPOSITORIES STREQUAL "develop" )
    include( cmake/develop_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "release" )
    include( cmake/release_dependencies.cmake )

elseif( REPOSITORIES STREQUAL "local" )
    include( cmake/local_dependencies.cmake )

endif()


########################################################################
# Project targets
########################################################################

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# dryad : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( dryad INTERFACE )
add_library( njoy::dryad ALIAS dryad )
target_include_directories( dryad
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries( dryad
  INTERFACE
    njoy::ENDFtk
    njoy::scion
    njoy::tools
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# dryad : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if( dryad.python )

  FetchContent_MakeAvailable( pybind11 )

  pybind11_add_module( dryad.python
      python/src/dryad.python.cpp
      python/src/TabulatedCrossSection.python.cpp
      python/src/Reaction.python.cpp
      python/src/ProjectileTarget.python.cpp
      )

  target_link_libraries( dryad.python PRIVATE dryad )
  add_dependencies( dryad.python ENDFtk.python scion.python )
  target_include_directories( dryad.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( dryad.python PRIVATE "-fvisibility=hidden" )
  set_target_properties( dryad.python PROPERTIES OUTPUT_NAME dryad )
  set_target_properties( dryad.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( dryad.python PROPERTIES POSITION_INDEPENDENT_CODE ON )

  message( STATUS "Building dryad's python API" )

  list( APPEND DRYAD_PYTHONPATH ${CMAKE_CURRENT_BINARY_DIR} )
  list( APPEND ENDFTK_PYTHONPATH ${CMAKE_CURRENT_BINARY_DIR}/_deps/endftk-build )
  list( APPEND SCION_PYTHONPATH ${CMAKE_CURRENT_BINARY_DIR}/_deps/scion-build )

  if( dryad.tests )
    include( cmake/unit_testing_python.cmake )
  endif()

endif()

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  if( dryad.tests )
    include( cmake/unit_testing.cmake )
  endif()
endif()
