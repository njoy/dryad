#######################################################################
# Setup
#######################################################################

enable_testing()

FetchContent_MakeAvailable( Catch2 )

function( add_cpp_test name source )

  set( test_name "dryad.${name}.test" )
  add_executable( ${test_name} ${source} )
  add_test( NAME ${test_name} COMMAND ${test_name} )
  target_link_libraries( ${test_name} PRIVATE dryad )
  target_link_libraries( ${test_name} PRIVATE Catch2::Catch2WithMain )

  file( GLOB resources "resources/*" )
  foreach( resource ${resources} )
    file( COPY "${resource}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
  endforeach()

endfunction()

#######################################################################
# Unit testing directories
#######################################################################

message( STATUS "Adding dryad C++ unit testing" )

add_subdirectory( src/dryad/id/ElementID/test )

add_subdirectory( src/dryad/atomic/ElectronSubshellConfiguration/test )
add_subdirectory( src/dryad/atomic/RadiativeTransitionData/test )
add_subdirectory( src/dryad/atomic/NonRadiativeTransitionData/test )

add_subdirectory( src/dryad/AtomicRelaxation/test )

add_subdirectory( src/dryad/TabulatedFormFactor/test )
add_subdirectory( src/dryad/TabulatedScatteringFunction/test )
add_subdirectory( src/dryad/TabulatedMultiplicity/test )
add_subdirectory( src/dryad/TabulatedAverageCosine/test )
add_subdirectory( src/dryad/TabulatedAverageEnergy/test )
add_subdirectory( src/dryad/LegendreAngularDistributionFunction/test )
add_subdirectory( src/dryad/LegendreAngularDistribution/test )
add_subdirectory( src/dryad/LegendreAngularDistributions/test )
add_subdirectory( src/dryad/TabulatedAngularDistributionFunction/test )
#add_subdirectory( src/dryad/TabulatedAngularDistribution/test )
add_subdirectory( src/dryad/TabulatedAngularDistributions/test )
add_subdirectory( src/dryad/TabulatedEnergyDistributionFunction/test )
#add_subdirectory( src/dryad/TabulatedEnergyDistribution/test )
add_subdirectory( src/dryad/TabulatedEnergyDistributions/test )
add_subdirectory( src/dryad/TwoBodyDistributionData/test )
add_subdirectory( src/dryad/UncorrelatedDistributionData/test )
add_subdirectory( src/dryad/CoherentDistributionData/test )
add_subdirectory( src/dryad/IncoherentDistributionData/test )
add_subdirectory( src/dryad/ReactionProduct/test )

add_subdirectory( src/dryad/TabulatedCrossSection/test )
add_subdirectory( src/dryad/Reaction/test )

add_subdirectory( src/dryad/ProjectileTarget/test )

add_subdirectory( src/dryad/format/test )
add_subdirectory( src/dryad/format/ace/test )
add_subdirectory( src/dryad/format/endf/test )
