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

if ( dryad.python )
  set( require.scion.python CACHE BOOL ON )
endif()

option( dryad.installation "Install dryad" ON )

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
    njoy::ACEtk
    njoy::ENDFtk
    njoy::scion
    njoy::tools
    pugixml
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# dryad : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if (dryad.python AND NOT TARGET njoy::scion.python)
  message(WARNING "njoy::scion was not built with python enabled.  Disabling build of dryad's python API.")
  set(dryad.python OFF)
endif()

if( dryad.python )

  FetchContent_MakeAvailable( pybind11 )

  pybind11_add_module( dryad.python
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/dryad.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/id.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/id/ElementID.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/atomic.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/atomic/TransitionType.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/atomic/RadiativeTransitionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/atomic/NonRadiativeTransitionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/atomic/ElectronSubshellConfiguration.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/DistributionDataType.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/InteractionType.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/ReactionType.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/ReferenceFrame.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedCrossSection.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedMultiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedAverageCosine.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedAverageEnergy.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/IsotropicAngularDistributions.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/LegendreAngularDistributionFunction.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/LegendreAngularDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/LegendreAngularDistributions.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedAngularDistributionFunction.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedAngularDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedAngularDistributions.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedEnergyDistributionFunction.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedEnergyDistribution.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedEnergyDistributions.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedFormFactor.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TabulatedScatteringFunction.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/TwoBodyDistributionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/UncorrelatedDistributionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/CoherentDistributionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/IncoherentDistributionData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/ReactionProduct.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/Reaction.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/ProjectileTarget.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/AtomicRelaxation.python.cpp
      )
  add_library( njoy::dryad.python ALIAS dryad.python )

  target_link_libraries( dryad.python PRIVATE njoy::dryad )
  add_dependencies( dryad.python njoy::scion.python )
  target_include_directories( dryad.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( dryad.python PRIVATE -fvisibility=hidden )
  set_target_properties( dryad.python PROPERTIES OUTPUT_NAME dryad )
  set_target_properties( dryad.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( dryad.python PROPERTIES POSITION_INDEPENDENT_CODE ON )

  message( STATUS "Building dryad's python API" )

  set( DRYAD_PYTHONPATH "${CMAKE_CURRENT_BINARY_DIR}" )
  # Append potential installation and build paths for scion python module
  set( SCION_PYTHONPATH "${CMAKE_CURRENT_BINARY_DIR}/_deps/scion-build" )
  if (scion_DIR)
    set( SCION_PYTHONPATH "${SCION_PYTHONPATH}:${scion_DIR}/../../../lib64" )
  endif()

  if( dryad.tests )
    include( cmake/unit_testing_python.cmake )
  endif()

endif()

if( dryad.tests )
  include( cmake/unit_testing.cmake )
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
