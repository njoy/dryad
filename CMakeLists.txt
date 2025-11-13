########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.27 )

set( subproject OFF )
if( DEFINED PROJECT_NAME )
  set( subproject ON )
endif()

project( njoy
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
  njoy.tests
  "Build the njoy unit tests and integrate with ctest" ON
  "BUILD_TESTING AND NOT ${subproject}" OFF
)

cmake_dependent_option(
  njoy.python
  "Build njoy python bindings" ON
  "NOT ${subproject} OR DEFINED require.njoy.python " OFF
)

option( njoy.installation "Install njoy" ON )

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
# njoy : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( njoy INTERFACE )

target_include_directories( njoy INTERFACE ${prefix} )

target_link_libraries( njoy
  INTERFACE
    pugixml
    eigen
    njoy::tools
    njoy::scion
    njoy::ACEtk
    njoy::ENDFtk
)

if(MSVC)
  add_compile_options(/bigobj)
  target_link_options(njoy INTERFACE "/STACK:8388608")
endif()


# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# njoy : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if ( njoy.python )
  add_subdirectory( python )
endif()

if( njoy.tests )
  add_subdirectory( test )
endif()

#######################################################################
# Installation
#######################################################################

if(njoy.installation)
    include(CMakePackageConfigHelpers)

    install(TARGETS njoy EXPORT njoy-targets
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )

    install(EXPORT njoy-targets
      FILE "njoy-targets.cmake"
      DESTINATION share/cmake/njoy
    )

    install(DIRECTORY src/
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
      FILES_MATCHING PATTERN "*.hpp"
      PATTERN "*test*" EXCLUDE
    )

    string(TOLOWER njoy lowercasePackageName)

    write_basic_package_version_file("${lowercasePackageName}-config-version.cmake"
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY AnyNewerVersion)

    configure_package_config_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${lowercasePackageName}-config.cmake.in
      ${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake
      INSTALL_DESTINATION share/cmake/njoy
    )

    install(FILES
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake"
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config-version.cmake"
      DESTINATION share/cmake/njoy
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
