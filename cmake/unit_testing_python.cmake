#######################################################################
# Setup
#######################################################################

enable_testing()

function( add_python_test name source )

  set(PYTHONPATH_PARTS ${njoy_PYTHONPATH} $ENV{PYTHONPATH})
  string( JOIN "${PATH_DELIM}" PYTHONPATH_VALUE ${PYTHONPATH_PARTS})

  set( test_name "njoy.python.${name}.test" )
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

message( STATUS "Adding njoy Python unit testing" )

add_python_test( matrix                                                Test_matrix.py )

add_python_test( dryad.id.EnergyGroup                                  dryad/id/Test_EnergyGroup.py )
add_python_test( dryad.id.ElectronSubshellID                           dryad/id/Test_ElectronSubshellID.py )
add_python_test( dryad.id.ElementID                                    dryad/id/Test_ElementID.py )
add_python_test( dryad.id.LevelID                                      dryad/id/Test_LevelID.py )
add_python_test( dryad.id.ParticleID                                   dryad/id/Test_ParticleID.py )
add_python_test( dryad.id.ReactionType                                 dryad/id/Test_ReactionType.py )
add_python_test( dryad.id.ReactionID                                   dryad/id/Test_ReactionID.py )
add_python_test( dryad.id.ChannelID                                    dryad/id/Test_ChannelID.py )

add_python_test( dryad.atomic.RadiativeTransitionData                  dryad/atomic/Test_RadiativeTransitionData.py )
add_python_test( dryad.atomic.NonRadiativeTransitionData               dryad/atomic/Test_NonRadiativeTransitionData.py )
add_python_test( dryad.atomic.ElectronSubshellConfiguration            dryad/atomic/Test_ElectronSubshellConfiguration.py )

add_python_test( dryad.covariance.VarianceScaling                      dryad/covariance/Test_VarianceScaling.py )
add_python_test( dryad.covariance.CrossSectionMetadata                 dryad/covariance/Test_CrossSectionMetadata.py )
add_python_test( dryad.covariance.CrossSectionCovarianceMatrix         dryad/covariance/Test_CrossSectionCovarianceMatrix.py )
add_python_test( dryad.covariance.AngularDistributionMetadata          dryad/covariance/Test_AngularDistributionMetadata.py )
add_python_test( dryad.covariance.AngularDistributionCovarianceMatrix  dryad/covariance/Test_AngularDistributionCovarianceMatrix.py )
add_python_test( dryad.covariance.ProductMultiplicityMetadata          dryad/covariance/Test_ProductMultiplicityMetadata.py )
add_python_test( dryad.covariance.ProductMultiplicityCovarianceMatrix  dryad/covariance/Test_ProductMultiplicityCovarianceMatrix.py )
add_python_test( dryad.covariance.LinearCombinationCovariance          dryad/covariance/Test_LinearCombinationCovariance.py )
add_python_test( dryad.covariance.CrossSectionCovarianceData           dryad/covariance/Test_CrossSectionCovarianceData.py )
add_python_test( dryad.covariance.AngularDistributionCovarianceData    dryad/covariance/Test_AngularDistributionCovarianceData.py )
add_python_test( dryad.covariance.CovarianceData                       dryad/covariance/Test_CovarianceData.py )

add_python_test( dryad.resonances.ParticlePair                         dryad/resonances/Test_ParticlePair.py )
add_python_test( dryad.resonances.ChannelQuantumNumbers                dryad/resonances/Test_ChannelQuantumNumbers.py )
add_python_test( dryad.resonances.TabulatedRadius                      dryad/resonances/Test_TabulatedRadius.py )
add_python_test( dryad.resonances.ChannelRadii                         dryad/resonances/Test_ChannelRadii.py )
add_python_test( dryad.resonances.HardSpherePenetrability              dryad/resonances/Test_HardSpherePenetrability.py )
add_python_test( dryad.resonances.HardSphereShiftFactor                dryad/resonances/Test_HardSphereShiftFactor.py )
add_python_test( dryad.resonances.HardSpherePhaseShift                 dryad/resonances/Test_HardSpherePhaseShift.py )
add_python_test( dryad.resonances.CoulombPenetrability                 dryad/resonances/Test_CoulombPenetrability.py )
add_python_test( dryad.resonances.CoulombShiftFactor                   dryad/resonances/Test_CoulombShiftFactor.py )
add_python_test( dryad.resonances.CoulombPhaseShift                    dryad/resonances/Test_CoulombPhaseShift.py )
add_python_test( dryad.resonances.CoulombPhaseShiftDifference          dryad/resonances/Test_CoulombPhaseShiftDifference.py )
add_python_test( dryad.resonances.TabulatedWaveFunction                dryad/resonances/Test_TabulatedWaveFunction.py )
add_python_test( dryad.resonances.FrohnerBackground                    dryad/resonances/Test_FrohnerBackground.py )
add_python_test( dryad.resonances.SammyBackground                      dryad/resonances/Test_SammyBackground.py )
add_python_test( dryad.resonances.TabulatedBackground                  dryad/resonances/Test_TabulatedBackground.py )
add_python_test( dryad.resonances.TabulatedLevelSpacing                dryad/resonances/Test_TabulatedLevelSpacing.py )

add_python_test( dryad.resonances.Channel                              dryad/resonances/Test_Channel.py )
add_python_test( dryad.resonances.ResonanceTable                       dryad/resonances/Test_ResonanceTable.py )
add_python_test( dryad.resonances.SpinGroup                            dryad/resonances/Test_SpinGroup.py )
add_python_test( dryad.resonances.CompoundSystem                       dryad/resonances/Test_CompoundSystem.py )

add_python_test( dryad.thermal.BraggEdgeData                           dryad/thermal/Test_BraggEdgeData.py )
add_python_test( dryad.thermal.DebyeWallerIntegralData                 dryad/thermal/Test_DebyeWallerIntegralData.py )
add_python_test( dryad.thermal.TabulatedScatteringKernelFunction       dryad/thermal/Test_TabulatedScatteringKernelFunction.py )
add_python_test( dryad.thermal.TabulatedScatteringFunctions            dryad/thermal/Test_TabulatedScatteringKernel.py )
add_python_test( dryad.thermal.CoherentElasticScattering               dryad/thermal/Test_CoherentElasticScattering.py )
add_python_test( dryad.thermal.IncoherentElasticScattering             dryad/thermal/Test_IncoherentElasticScattering.py )

add_python_test( dryad.Documentation                                   dryad/Test_Documentation.py )

add_python_test( dryad.Particle                                        dryad/Test_Particle.py )
add_python_test( dryad.ParticleDatabase                                dryad/Test_ParticleDatabase.py )

add_python_test( dryad.TabulatedMultiplicity                           dryad/Test_TabulatedMultiplicity.py )
add_python_test( dryad.TabulatedAverageEnergy                          dryad/Test_TabulatedAverageEnergy.py )
add_python_test( dryad.TabulatedAverageCosine                          dryad/Test_TabulatedAverageCosine.py )
add_python_test( dryad.LegendreAngularDistributionFunction             dryad/Test_LegendreAngularDistributionFunction.py )
add_python_test( dryad.LegendreAngularDistribution                     dryad/Test_LegendreAngularDistribution.py )
add_python_test( dryad.LegendreAngularDistributions                    dryad/Test_LegendreAngularDistributions.py )
add_python_test( dryad.TabulatedAngularDistributionFunction            dryad/Test_TabulatedAngularDistributionFunction.py )
add_python_test( dryad.TabulatedAngularDistribution                    dryad/Test_TabulatedAngularDistribution.py )
add_python_test( dryad.TabulatedAngularDistributions                   dryad/Test_TabulatedAngularDistributions.py )
add_python_test( dryad.TabulatedComptonProfileFunction                 dryad/Test_TabulatedComptonProfileFunction.py )
add_python_test( dryad.TabulatedComptonProfile                         dryad/Test_TabulatedComptonProfile.py )
add_python_test( dryad.UniformAngularDistribution                      dryad/Test_UniformAngularDistribution.py )
add_python_test( dryad.UniformAngularDistributions                     dryad/Test_UniformAngularDistributions.py )
add_python_test( dryad.TabulatedEnergyDistributionFunction             dryad/Test_TabulatedEnergyDistributionFunction.py )
add_python_test( dryad.TabulatedEnergyDistribution                     dryad/Test_TabulatedEnergyDistribution.py )
add_python_test( dryad.TabulatedEnergyDistributions                    dryad/Test_TabulatedEnergyDistributions.py )
add_python_test( dryad.UniformEnergyDistribution                       dryad/Test_UniformEnergyDistribution.py )
add_python_test( dryad.UniformEnergyDistributions                      dryad/Test_UniformEnergyDistributions.py )
add_python_test( dryad.TabulatedFormFactor                             dryad/Test_TabulatedFormFactor.py )
add_python_test( dryad.TabulatedScatteringFunction                     dryad/Test_TabulatedScatteringFunction.py )
add_python_test( dryad.TwoBodyDistributionData                         dryad/Test_TwoBodyDistributionData.py )
add_python_test( dryad.UncorrelatedDistributionData                    dryad/Test_UncorrelatedDistributionData.py )
add_python_test( dryad.CoherentDistributionData                        dryad/Test_CoherentDistributionData.py )
add_python_test( dryad.IncoherentDistributionData                      dryad/Test_IncoherentDistributionData.py )
add_python_test( dryad.ReactionProduct                                 dryad/Test_ReactionProduct.py )

add_python_test( dryad.TabulatedCrossSection                           dryad/Test_TabulatedCrossSection.py )
add_python_test( dryad.Reaction                                        dryad/Test_Reaction.py )

add_python_test( dryad.ProjectileTarget                                dryad/Test_ProjectileTarget.py )
add_python_test( dryad.AtomicRelaxation                                dryad/Test_AtomicRelaxation.py )
add_python_test( dryad.ThermalScattering                               dryad/Test_ThermalScattering.py )

add_python_test( dryad.external.ComptonProfiles                        dryad/external/Test_ComptonProfiles.py )

add_python_test( psychic.covariance.PositiveVariances                  psychic/covariance/Test_PositiveVariances.py )
add_python_test( psychic.covariance.PositiveSemiDefinite               psychic/covariance/Test_PositiveSemiDefinite.py )
add_python_test( psychic.covariance.EigenvalueRatio                    psychic/covariance/Test_EigenvalueRatio.py )
add_python_test( psychic.covariance.BoundedCorrelations                psychic/covariance/Test_BoundedCorrelations.py )
add_python_test( psychic.covariance.DiagonalCorrelations               psychic/covariance/Test_DiagonalCorrelations.py )
add_python_test( psychic.covariance.TestSuite                          psychic/covariance/Test_TestSuite.py )

add_python_test( reconr.unionise_cross_sections                        reconr/Test_unionise_cross_sections.py )
add_python_test( reconr.calculate_summation_cross_sections             reconr/Test_calculate_summation_cross_sections.py )

add_python_test( medic.prune_cross_section                             medic/Test_prune_cross_section.py )
add_python_test( medic.prune_cross_sections                            medic/Test_prune_cross_sections.py )
add_python_test( medic.covariance.prune_small_eigenvalues              medic/covariance/Test_prune_small_eigenvalues.py )
