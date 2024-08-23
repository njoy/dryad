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
                        PYTHONPATH=${SCION_PYTHONPATH}:${DRYAD_PYTHONPATH}:$ENV{PYTHONPATH})

endfunction()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding dryad Python unit testing" )

add_python_test( id.ElementID                          id/Test_dryad_id_ElementID.py )

add_python_test( TabulatedMultiplicity                 Test_dryad_TabulatedMultiplicity.py )
add_python_test( TabulatedAverageEnergy                Test_dryad_TabulatedAverageEnergy.py )
add_python_test( LegendreAngularDistributionFunction   Test_dryad_LegendreAngularDistributionFunction.py )
add_python_test( LegendreAngularDistribution           Test_dryad_LegendreAngularDistribution.py )
add_python_test( LegendreAngularDistributions          Test_dryad_LegendreAngularDistributions.py )
add_python_test( TabulatedAngularDistributionFunction  Test_dryad_TabulatedAngularDistributionFunction.py )
#add_python_test( TabulatedAngularDistribution          Test_dryad_TabulatedAngularDistribution.py )
add_python_test( TabulatedAngularDistributions         Test_dryad_TabulatedAngularDistributions.py )
add_python_test( TabulatedEnergyDistributionFunction   Test_dryad_TabulatedEnergyDistributionFunction.py )
#add_python_test( TabulatedEnergyDistribution           Test_dryad_TabulatedEnergyDistribution.py )
add_python_test( TabulatedEnergyDistributions          Test_dryad_TabulatedEnergyDistributions.py )
add_python_test( TabulatedFormFactor                   Test_dryad_TabulatedFormFactor.py )
add_python_test( TabulatedScatteringFunction           Test_dryad_TabulatedScatteringFunction.py )
add_python_test( TwoBodyDistributionData               Test_dryad_TwoBodyDistributionData.py )
add_python_test( UncorrelatedDistributionData          Test_dryad_UncorrelatedDistributionData.py )
add_python_test( CoherentDistributionData              Test_dryad_CoherentDistributionData.py )
add_python_test( IncoherentDistributionData            Test_dryad_IncoherentDistributionData.py )
add_python_test( ReactionProduct                       Test_dryad_ReactionProduct.py )

add_python_test( TabulatedCrossSection                 Test_dryad_TabulatedCrossSection.py )
add_python_test( Reaction                              Test_dryad_Reaction.py )

add_python_test( ProjectileTarget                      Test_dryad_ProjectileTarget.py )
