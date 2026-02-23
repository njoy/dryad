if(njoy.python)

    find_package( Python3 REQUIRED )
    pybind11_add_module( njoy.python
        ${CMAKE_CURRENT_SOURCE_DIR}/src/njoy.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/id.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/id/EnergyGroup.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/id/ElectronSubshellID.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/id/ElementID.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/id/LevelID.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/id/ParticleID.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/id/ReactionType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/id/ReactionID.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/id/ChannelID.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/atomic.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/atomic/TransitionType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/atomic/RadiativeTransitionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/atomic/NonRadiativeTransitionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/atomic/ElectronSubshellConfiguration.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/ResonanceParameters.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/BoundaryCondition.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/Formalism.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/Kinematics.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/Particle.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/ParticlePair.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/ChannelQuantumNumbers.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/TabulatedRadius.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/ChannelRadii.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/HardSpherePenetrability.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/HardSphereShiftFactor.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/HardSpherePhaseShift.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/CoulombPenetrability.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/CoulombShiftFactor.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/CoulombPhaseShift.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/CoulombPhaseShiftDifference.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/TabulatedWaveFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/FrohnerBackground.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/SammyBackground.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/TabulatedBackground.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/Channel.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/ResonanceTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/SpinGroup.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/resonances/CompoundSystem.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/thermal.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/thermal/TabulatedDebyeWallerIntegral.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/thermal/TabulatedEffectiveTemperature.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/thermal/TabulatedScatteringFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/thermal/IncoherentElasticScattering.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/covariance.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/covariance/ScalingType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/covariance/VarianceScaling.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/covariance/CrossSectionMetadata.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/covariance/CrossSectionCovarianceMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/covariance/ProductMultiplicityMetadata.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/covariance/ProductMultiplicityCovarianceMatrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/covariance/LinearCombinationCovariance.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/covariance/CrossSectionCovarianceData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/covariance/CovarianceData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/Documentation.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/InterpolationType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/DistributionDataType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/InteractionType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/ReactionCategory.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/ReferenceFrame.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/UniformDistributionType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedCrossSection.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/PolynomialMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedAverageCosine.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedAverageEnergy.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/IsotropicAngularDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/LegendreAngularDistributionFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/LegendreAngularDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/LegendreAngularDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/MultiEnergyDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedAngularDistributionFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedAngularDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedAngularDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedComptonProfileFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedComptonProfile.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/UniformAngularDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/UniformAngularDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedEnergyDistributionFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedEnergyDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedEnergyDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/UniformEnergyDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/UniformEnergyDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedFormFactor.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TabulatedScatteringFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/TwoBodyDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/UncorrelatedDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/CoherentDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/IncoherentDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/ReactionProduct.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/Reaction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/ProjectileTarget.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/AtomicRelaxation.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/ThermalScattering.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/external.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad/external/ComptonProfiles.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/reconr.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/reconr/wrapUnioniseCrossSections.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/reconr/wrapCalculateSummationCrossSections.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/medic.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/medic/pruneCrossSection.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/medic/pruneCrossSections.python.cpp
    )

    target_link_libraries(njoy.python PRIVATE njoy)
    target_include_directories( njoy.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src )
    set_target_properties( njoy.python PROPERTIES CXX_VISIBILITY_PRESET hidden)
    set_target_properties( njoy.python PROPERTIES OUTPUT_NAME njoy )
    set_target_properties( njoy.python PROPERTIES LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR})
    set_target_properties( njoy.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
    set_target_properties( njoy.python PROPERTIES POSITION_INDEPENDENT_CODE ON )
    # add all .so's that are installed with mcatk to the installed library rpath
    set_target_properties( njoy.python PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
    # add all .so's that are linked to at build time to the installed library rpath
    set_target_properties( njoy.python PROPERTIES INSTALL_RPATH_USE_LINK_PATH ON)

    set(PyVersion "${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}")
    set( py_library_install_prefix ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/python${PyVersion}/site-packages )

    if (njoy.installation)
        install( TARGETS njoy.python LIBRARY DESTINATION ${py_library_install_prefix} )
    endif()

    message( STATUS "Building njoy's python API" )

    # Append potential installation and build paths for tools python module
    set(njoy_PYTHONPATH "$<TARGET_FILE_DIR:njoy.python>")

    # Windows and unix have different delimiter for paths
    if (WIN32)
	    set(PATH_DELIM "\;")
    else()
	    set(PATH_DELIM ":")
    endif()

    if( njoy.tests )
        include( ${PROJECT_SOURCE_DIR}/cmake/unit_testing_python.cmake )
    endif()

    # generate python stubs if possible
    find_program(pybind11stubgen_exe pybind11-stubgen)

    set(PYTHONPATH_PARTS ${njoy_PYTHONPATH} $ENV{PYTHONPATH})
    string( JOIN "${PATH_DELIM}" PYTHONPATH_VALUE ${PYTHONPATH_PARTS})

    set(stubdir "${CMAKE_CURRENT_SOURCE_DIR}/stubs/njoy")
    if (pybind11stubgen_exe)
        # the following command executes the pybind11-stubgen executable found via find_program
        # and puts its terminal output into pybind11-stubgen.log in the build tree.
        # The stubs get generated in the source tree so users can determine what changes if any were made to the stubs.
        # The stubs are then copied into the build tree so developers get the stubs when using the build tree's python bindings.
        # If the stubs fail to generate then this command exits gracefully and allows the build to continue.
        add_custom_command(
            TARGET njoy.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH_VALUE}" ${pybind11stubgen_exe} njoy -o ${CMAKE_CURRENT_SOURCE_DIR}/stubs &> ${CMAKE_CURRENT_BINARY_DIR}/pybind11-stubgen.log || true
            COMMAND ${CMAKE_COMMAND} -E rename ${stubdir}/__init__.pyi ${stubdir}/njoy.pyi &> /dev/null || true
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Building njoy's python stub files via pybind11-stubgen. See pybind11-stubgen.log for details."
            VERBATIM
        )

    else()
        # copy stub files to build tree even if pybind11stubgen isn't available.
        add_custom_command(
            TARGET njoy.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
        )
    endif()

    # install stubs so the installed binaries play nice with IDEs
    if (njoy.installation)
        install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/stubs/njoy/ DESTINATION ${py_library_install_prefix} )
    endif()

endif() # end njoy.python check
