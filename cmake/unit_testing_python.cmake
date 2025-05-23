#######################################################################
# Setup
#######################################################################

enable_testing()

function( add_python_test name source )

  set(PYTHONPATH_PARTS ${dryad_PYTHONPATH} $ENV{PYTHONPATH})
  string( JOIN "${PATH_DELIM}" PYTHONPATH_VALUE ${PYTHONPATH_PARTS})

  set( test_name "dryad.python.${name}.test" )
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

message( STATUS "Adding dryad Python unit testing" )

add_python_test( id.ElectronSubshellID                   id/Test_dryad_id_ElectronSubshellID.py )
add_python_test( id.ElementID                            id/Test_dryad_id_ElementID.py )
add_python_test( id.LevelID                              id/Test_dryad_id_LevelID.py )
add_python_test( id.ParticleID                           id/Test_dryad_id_ParticleID.py )
add_python_test( id.ReactionType                         id/Test_dryad_id_ReactionType.py )

add_python_test( atomic.RadiativeTransitionData          atomic/Test_dryad_atomic_RadiativeTransitionData.py )
add_python_test( atomic.NonRadiativeTransitionData       atomic/Test_dryad_atomic_NonRadiativeTransitionData.py )
add_python_test( atomic.ElectronSubshellConfiguration    atomic/Test_dryad_atomic_ElectronSubshellConfiguration.py )

add_python_test( covariance.matrix                       covariance/Test_dryad_covariance_matrix.py )
add_python_test( covariance.VarianceScaling              covariance/Test_dryad_covariance_VarianceScaling.py )
add_python_test( covariance.LinearCombinationCovariance  covariance/Test_dryad_covariance_LinearCombinationCovariance.py )
add_python_test( covariance.CrossSectionMetadata         covariance/Test_dryad_covariance_CrossSectionMetadata.py )
add_python_test( covariance.CrossSectionCovarianceBlock  covariance/Test_dryad_covariance_CrossSectionCovarianceBlock.py )

add_python_test( TabulatedMultiplicity                   Test_dryad_TabulatedMultiplicity.py )
add_python_test( TabulatedAverageEnergy                  Test_dryad_TabulatedAverageEnergy.py )
add_python_test( TabulatedAverageCosine                  Test_dryad_TabulatedAverageCosine.py )
add_python_test( LegendreAngularDistributionFunction     Test_dryad_LegendreAngularDistributionFunction.py )
add_python_test( LegendreAngularDistribution             Test_dryad_LegendreAngularDistribution.py )
add_python_test( LegendreAngularDistributions            Test_dryad_LegendreAngularDistributions.py )
add_python_test( TabulatedAngularDistributionFunction    Test_dryad_TabulatedAngularDistributionFunction.py )
add_python_test( TabulatedAngularDistribution            Test_dryad_TabulatedAngularDistribution.py )
add_python_test( TabulatedAngularDistributions           Test_dryad_TabulatedAngularDistributions.py )
add_python_test( UniformAngularDistribution              Test_dryad_UniformAngularDistribution.py )
add_python_test( UniformAngularDistributions             Test_dryad_UniformAngularDistributions.py )
add_python_test( TabulatedEnergyDistributionFunction     Test_dryad_TabulatedEnergyDistributionFunction.py )
add_python_test( TabulatedEnergyDistribution             Test_dryad_TabulatedEnergyDistribution.py )
add_python_test( TabulatedEnergyDistributions            Test_dryad_TabulatedEnergyDistributions.py )
add_python_test( UniformEnergyDistribution               Test_dryad_UniformEnergyDistribution.py )
add_python_test( UniformEnergyDistributions              Test_dryad_UniformEnergyDistributions.py )
add_python_test( TabulatedFormFactor                     Test_dryad_TabulatedFormFactor.py )
add_python_test( TabulatedScatteringFunction             Test_dryad_TabulatedScatteringFunction.py )
add_python_test( TwoBodyDistributionData                 Test_dryad_TwoBodyDistributionData.py )
add_python_test( UncorrelatedDistributionData            Test_dryad_UncorrelatedDistributionData.py )
add_python_test( CoherentDistributionData                Test_dryad_CoherentDistributionData.py )
add_python_test( IncoherentDistributionData              Test_dryad_IncoherentDistributionData.py )
add_python_test( ReactionProduct                         Test_dryad_ReactionProduct.py )

add_python_test( TabulatedCrossSection                   Test_dryad_TabulatedCrossSection.py )
add_python_test( Reaction                                Test_dryad_Reaction.py )

add_python_test( ProjectileTarget                        Test_dryad_ProjectileTarget.py )
add_python_test( AtomicRelaxation                        Test_dryad_AtomicRelaxation.py )
