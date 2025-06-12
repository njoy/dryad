if(dryad.python)

    pybind11_add_module( dryad.python
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dryad.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ToleranceConvergence.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/id.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/id/ElectronSubshellID.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/id/ElementID.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/id/LevelID.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/id/ParticleID.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/id/ReactionType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/atomic.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/atomic/TransitionType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/atomic/RadiativeTransitionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/atomic/NonRadiativeTransitionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/atomic/ElectronSubshellConfiguration.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resonances.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resonances/ResonanceParameters.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/covariance.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/covariance/ScalingType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/covariance/matrix.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/covariance/CrossSectionMetadata.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/covariance/VarianceScaling.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/covariance/LinearCombinationCovariance.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/covariance/CrossSectionCovarianceBlock.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/InterpolationType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DistributionDataType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/InteractionType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ReactionCategory.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ReferenceFrame.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/UniformDistributionType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedCrossSection.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/PolynomialMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedMultiplicity.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedAverageCosine.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedAverageEnergy.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/IsotropicAngularDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/LegendreAngularDistributionFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/LegendreAngularDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/LegendreAngularDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/MultiEnergyDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedAngularDistributionFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedAngularDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedAngularDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/UniformAngularDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/UniformAngularDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedEnergyDistributionFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedEnergyDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedEnergyDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/UniformEnergyDistribution.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/UniformEnergyDistributions.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedFormFactor.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TabulatedScatteringFunction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/TwoBodyDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/UncorrelatedDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/CoherentDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/IncoherentDistributionData.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ReactionProduct.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Reaction.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ProjectileTarget.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/AtomicRelaxation.python.cpp
    )

    target_link_libraries(dryad.python PRIVATE njoy::dryad)
    target_include_directories( dryad.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src )
    set_target_properties( dryad.python PROPERTIES CXX_VISIBILITY_PRESET hidden)
    set_target_properties( dryad.python PROPERTIES OUTPUT_NAME dryad )
    set_target_properties( dryad.python PROPERTIES LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR})
    set_target_properties( dryad.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
    set_target_properties( dryad.python PROPERTIES POSITION_INDEPENDENT_CODE ON )
    # add all .so's that are installed with mcatk to the installed library rpath
    set_target_properties( dryad.python PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
    # add all .so's that are linked to at build time to the installed library rpath
    set_target_properties( dryad.python PROPERTIES INSTALL_RPATH_USE_LINK_PATH ON)

    set(PyVersion "${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}")
    set( py_library_install_prefix ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/python${PyVersion}/site-packages )

    if (dryad.installation)
        install( TARGETS dryad.python LIBRARY DESTINATION ${py_library_install_prefix} )
    endif()

    message( STATUS "Building dryad's python API" )

    # Append potential installation and build paths for tools python module
    set(dryad_PYTHONPATH "$<TARGET_FILE_DIR:dryad.python>")

    # Windows and unix have different delimiter for paths
    if (WIN32)
	    set(PATH_DELIM "\;")
    else()
	    set(PATH_DELIM ":")
    endif()

    if( dryad.tests )
        include( ${PROJECT_SOURCE_DIR}/cmake/unit_testing_python.cmake )
    endif()

    # generate python stubs if possible
    find_program(pybind11stubgen_exe pybind11-stubgen)

    set(PYTHONPATH_PARTS ${dryad_PYTHONPATH} $ENV{PYTHONPATH})
    string( JOIN "${PATH_DELIM}" PYTHONPATH_VALUE ${PYTHONPATH_PARTS})

    set(stubdir "${CMAKE_CURRENT_SOURCE_DIR}/stubs/dryad")
    if (pybind11stubgen_exe)
        # the following command executes the pybind11-stubgen executable found via find_program
        # and puts its terminal output into pybind11-stubgen.log in the build tree.
        # The stubs get generated in the source tree so users can determine what changes if any were made to the stubs.
        # The stubs are then copied into the build tree so developers get the stubs when using the build tree's python bindings.
        # If the stubs fail to generate then this command exits gracefully and allows the build to continue.
        add_custom_command(
            TARGET dryad.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH_VALUE}" ${pybind11stubgen_exe} dryad -o ${CMAKE_CURRENT_SOURCE_DIR}/stubs &> ${CMAKE_CURRENT_BINARY_DIR}/pybind11-stubgen.log || true
            COMMAND ${CMAKE_COMMAND} -E rename ${stubdir}/__init__.pyi ${stubdir}/dryad.pyi &> /dev/null || true
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Building dryad's python stub files via pybind11-stubgen. See pybind11-stubgen.log for details."
            VERBATIM
        )

    else()
        # copy stub files to build tree even if pybind11stubgen isn't available.
        add_custom_command(
            TARGET dryad.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
        )
    endif()

    # install stubs so the installed binaries play nice with IDEs
    if (dryad.installation)
        install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/stubs/dryad/ DESTINATION ${py_library_install_prefix} )
    endif()

endif() # end dryad.python check
