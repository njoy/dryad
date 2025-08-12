########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.27 )

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
  "NOT ${subproject} OR DEFINED require.dryad.python " OFF
)

option( dryad.installation "Install dryad" ON )

if(MSVC)
  add_compile_options(/bigobj)
endif()

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
# dryad : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( dryad INTERFACE )
add_library( njoy::dryad ALIAS dryad )

target_include_directories( dryad INTERFACE ${prefix} )

target_link_libraries( dryad
  INTERFACE
    pugixml
    eigen
    njoy::tools
    njoy::scion
    njoy::ACEtk
    njoy::ENDFtk
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# dryad : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if ( dryad.python )
  add_subdirectory( python )
endif()

if( dryad.tests )
  add_subdirectory( test )
endif()

#######################################################################
# Installation
#######################################################################

if(dryad.installation)
    include(CMakePackageConfigHelpers)

    install(TARGETS dryad EXPORT dryad-targets
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )

    install(EXPORT dryad-targets
      FILE "dryad-targets.cmake"
      NAMESPACE njoy::
      DESTINATION share/cmake/dryad
    )

    install(DIRECTORY src/
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
      FILES_MATCHING PATTERN "*.hpp"
      PATTERN "*test*" EXCLUDE
    )

    string(TOLOWER dryad lowercasePackageName)

    write_basic_package_version_file("${lowercasePackageName}-config-version.cmake"
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY AnyNewerVersion)

    configure_package_config_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${lowercasePackageName}-config.cmake.in
      ${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake
      INSTALL_DESTINATION share/cmake/dryad
    )

    install(FILES
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake"
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config-version.cmake"
      DESTINATION share/cmake/dryad
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
