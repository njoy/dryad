add_cpp_test( format.gnds.convertEnergy          convertEnergy.test.cpp )
add_cpp_test( format.gnds.convertCrossSections   convertEnergies.test.cpp )
add_cpp_test( format.gnds.convertEnergies        convertEnergies.test.cpp )

add_cpp_test( format.gnds.createInterpolationType   createInterpolationType.test.cpp )
add_cpp_test( format.gnds.createReferenceFrame      createReferenceFrame.test.cpp )

add_cpp_test( format.gnds.readAxes         readAxes.test.cpp )
add_cpp_test( format.gnds.readValues       readValues.test.cpp )
add_cpp_test( format.gnds.readConstant1d   readLegendre.test.cpp )
add_cpp_test( format.gnds.readXYs1d        readXYs1d.test.cpp )
add_cpp_test( format.gnds.readLegendre     readLegendre.test.cpp )

add_cpp_test( format.gnds.createTabulatedCrossSection   createTabulatedCrossSection.test.cpp )
add_cpp_test( format.gnds.createReaction                createReaction.test.cpp )
add_cpp_test( format.gnds.createReactions               createReactions.test.cpp )

#add_cpp_test( format.gnds.atomic.createElectronSubshellID              atomic/createElectronSubshellID.test.cpp )
add_cpp_test( format.gnds.atomic.createElectronSubshellConfiguration   atomic/createElectronSubshellConfiguration.test.cpp )

add_cpp_test( format.gnds.createAtomicRelaxation           createAtomicRelaxation.test.cpp )
add_cpp_test( format.gnds.createAtomicRelaxationFromFile   createAtomicRelaxationFromFile.test.cpp )
