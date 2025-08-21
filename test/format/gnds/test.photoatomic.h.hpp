namespace photoatomic {

// test functions based on photoat-001_H_000.endf
namespace h0 {

  void verifyDocumentation( const Documentation& documentation ) {

    std::string description =
      "  1-H -  0 NDS,IAEA   Eval-Aug23 D.E.Cullen, et al.               \n"
      " NDS-IAEA-225         DIST-AUG24 REV1-NOV23            20240830   \n"
      "---- ENDF/B-VIII.1    MATERIAL  100         REVISION 1            \n"
      "----- PHOTO-ATOMIC INTERACTION DATA                               \n"
      "------ ENDF-6                                                     \n"
      " =================================================================\n"
      " The Livermore Evaluated Photon Data Library (EPDL97) in the      \n"
      " ENDF-6 Format.                                                   \n"
      " =================================================================\n"
      "  Contents                                                        \n"
      " =================================================================\n"
      "  MF/MT     Description                                           \n"
      " =================================================================\n"
      "  23/501   Total cross sections                                   \n"
      "  23/502   Coherent scattering cross sections                     \n"
      "  23/504   Incoherent scattering cross sections                   \n"
      "  23/515   Pair production cross sections, Electron field         \n"
      "  23/516   Pair production cross sections, Total                  \n"
      "  23/517   Pair production cross sections, Nuclear field          \n"
      "  23/522   Total photoionization cross section                    \n"
      "  23/534   K (1S1/2)    Photoionization subshell cross section    \n"
      " =================================================================\n"
      "  27/502   Coherent scattering form factors                       \n"
      "  27/504   Incoherent scattering functions                        \n"
      "  27/505   Imaginary anomalous scattering factor                  \n"
      "  27/506   Real anomalous scattering factor                       \n"
      " =================================================================\n"
      "  Warning                                                         \n"
      " =================================================================\n"
      "  MF/MT combinations used to define photoionization subshell cross\n"
      "  sections (MF=23, MT=534-572) and coherent anomalous scattering  \n"
      "  factors (MF=27, MT=505 AND 506) are newly defined MF/MT numbers \n"
      "  for ENDF/B-VI that did not exist in earlier versions of ENDF/B. \n"
      "  If you are not prepared to use this data you need merely delete \n"
      "  it and all of the remaining data will still be consistent and   \n"
      "  equivalent to the types of data in earlier versions of ENDF/B.  \n"
      "  However, this will limit the range of problems to which this    \n"
      "  data can be applied (see: ref. 1 for details).                  \n"
      " =================================================================\n"
      "  Definition of new types of data                                 \n"
      " =================================================================\n"
      "  1) The total photoionization cross section is equal to the sum  \n"
      "     of the photoionization subshell cross sections.              \n"
      "                                                                  \n"
      "     For each subshell on the second line of a section the C1 and \n"
      "     C2 fields are defined as,                                    \n"
      "                                                                  \n"
      "     EPE = The photoionization edge energy (similar to Q-value)   \n"
      "     EFL = The fluorescence yield (eV/photoionization)            \n"
      "                                                                  \n"
      "  2) The angular distribution of coherently scattered photons is, \n"
      "                                                                  \n"
      "     S(E,MU) = 3*T/8*(1 + MU**2)*((FF(M)+F1(E))**2+(F2(E))**2)    \n"
      "                                                                  \n"
      "     S(E,MU) = Angular distributions (barns per unit cosine)      \n"
      "     T       = The Thomson cross section                          \n"
      "     MU      = The cosine of the scattering angle                 \n"
      "     FF(M)   = The atomic form factor                             \n"
      "     M       = Momentum transfer = SIN(THETA/2)/LAMBDA/4*PI       \n"
      "     F1(E)   = The real anomalous scattering factor               \n"
      "     F2(E)   = The imaginary anomalous scattering factor          \n"
      "                                                                  \n"
      "     F1(E) and F2(E) are isotropic.                               \n"
      "                                                                  \n"
      "     When F1(E) = F2(E) = 0 this reduces to the result obtained   \n"
      "     using only form factors (the older ENDF/B convention).       \n"
      " =================================================================\n"
      " Differences between EPDL97 and the data base presented here      \n"
      " =================================================================\n"
      " 1) Energy range - EPDL97 - 1 eV to 100 GeV                       \n"
      "                   Here   - 1 eV TO 100 GeV (previously 100 MeV)  \n"
      " 2) Type of Data - EPDL97 - Photon interaction including          \n"
      "                            photoexcitation                       \n"
      "                   Here   - Photon interaction  - ENDF/B-VI has   \n"
      "                            no provision for photoexcitation      \n"
      " 3) Secondary E  - EPDL97 - Average energy of each secondary      \n"
      "                            (photons, electrons, positrons)       \n"
      "                   HERE   - No secondary energy data              \n"
      " 4) Interpolation- EPDL97 - Cross sections are Log X vs. Log Y    \n"
      "                            interpolable - the total cross        \n"
      "                            section is not included               \n"
      "                          - Form factors and scattering functions \n"
      "                            are Log X vs. Log y, except first     \n"
      "                            interval.                             \n"
      "                          - Anomalous scattering factors linearly \n"
      "                            interpolable (they can be negative)   \n"
      "                   Here   - Up through ENDF/B-V photon interaction\n"
      "                            cross sections were Log X vs. Log Y.  \n"
      "                          - For the first two Mods. of ENDF/B-VI  \n"
      "                            in order to consistently define the   \n"
      "                            total cross sections at ALL energies  \n"
      "                            all cross sections were linearized.   \n"
      "                            This was NOT a good idea.             \n"
      "                          - Starting with Mod. 3, cross sections  \n"
      "                            are left in Log X vs. Log. Y form so  \n"
      "                            that they are IDENTICAL to what's in  \n"
      "                            EPDL97.                               \n"
      "                            The total is defined ONLY at the      \n"
      "                            energies tabulated in any other cross \n"
      "                            section.                              \n"
      "                 WARNING  - As a result the total cross section   \n"
      "                            MUST NOT be interpolated to define the\n"
      "                            total between tabulated energies. The \n"
      "                            ONLY consist way to define the total  \n"
      "                            between tabulated energies is to      \n"
      "                            interpolate all of the partials and   \n"
      "                            add them up.                          \n"
      " =================================================================\n"
      "  References                                                      \n"
      " =================================================================\n"
      "  1) D.E. Cullen, M.H. Chen, J.H. Hubbell, S.T. Perkins,          \n"
      "  E.F. Plechaty, J.A. Rathkopf and J.H. Scofield, Tables and      \n"
      "  graphs of photon interaction cross sections from 10 eV to 100   \n"
      "  GeV derived from the LLNL Evaluated Photon data library (EPDL), \n"
      "  UCRL-50400, Vol. 6, Rev. 4, Part A: Z = 1 to 50 and Part B:     \n"
      "  Z = 51 to 100, Lawrence Livermore National Laboratory (1989)    \n"
      "  2) D.E. Cullen, J.H. Hubbell and L.D. Kissel, EPDL97: the       \n"
      "  Evaluated Photon Data Library, '97 Version, UCRL-50400, Vol. 6, \n"
      "  Rev. 5, Lawrence Livermore National Laboratory (1997)           \n"
      "  3) D.E. Cullen \"A Survey of Atomic Binding Energies for use     \n"
      "  in EPICS2017\" ,IAEA-NDS-224, (2017), Nuclear Data Section,      \n"
      "  IAEA, Vienna, Austria                                           \n"
      "  4) D.E. Cullen \"A Survey of Photon Cross Section Data for use   \n"
      "  in EPICS2017\" ,IAEA-NDS-225, (2017), Nuclear Data Section,      \n"
      "  IAEA, Vienna, Austria                                           \n"
      "  5) D.E. Cullen,\"EPICS2017: April 2019 Status Report\",           \n"
      "  IAEA-NDS-228, April 2019, Nuclear Data Section,                 \n"
      "  IAEA, Vienna, Austria.                                          \n"
      "  6) D.E. Cullen,\"EPICS2023: August 2023 Status Report\",          \n"
      "  IAEA-NDS-242, August 2023, Nuclear Data Section,                \n"
      "  IAEA, Vienna, Austria.                                          \n"
      "                                                                  \n"
      "  These are the primary references to the contents of this library\n"
      "  and they contain a complete list of references to the sources   \n"
      "  of data used in this library, methods of evaluation, accuracy   \n"
      "  of the data, etc.                                               \n"
      " =================================================================\n"
      "  History                                                         \n"
      " =================================================================\n"
      " 1) Oct. 1989 - Initial Release                                   \n"
      " 2) Aug. 1990 - Updated Photoelectic (total+shellS)               \n"
      " 3) July 1997 - Complete re-evaluation                            \n"
      " 4) Sept.2014 - Updated based on recently published data.         \n"
      "              - Insured Standard C, C++, FORTRAN format           \n"
      " 5) Nov. 2017 - New Binding Energies (see, ref. 3)                \n"
      "              - New Photoelectric and Coherent Cross Sections     \n"
      "              - New Anomalous Scattering Factors (see, ref. 4)    \n"
      "              - ALL Cross Sections Lin-Lin Interpolable           \n"
      " 6) Aug. 2023 - Delete repeated points. Threshold start with XC=0.\n"
      " =================================================================\n"
      " ***************** Program FIXUP (Version 2023-2) ****************\n"
      " **************** Program DICTIN (VERSION 2023-1) ****************\n";

    CHECK( std::nullopt == documentation.awr() );
    CHECK( std::nullopt == documentation.library() );
    CHECK( std::nullopt == documentation.version() );
    CHECK( std::nullopt == documentation.description() );
  }

  void verifyTotalReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->total[atomic]" ) == reaction.identifier() );
    CHECK( 501 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 5 == partials.size() );
    CHECK( id::ReactionID( "g,H->g,H[coherent]" ) == partials[0] );
    CHECK( id::ReactionID( "g,H->g,H[incoherent]" ) == partials[1] );
    CHECK( id::ReactionID( "g,H->2e-,e+,H[pair-production-electron]" ) == partials[2] );
    CHECK( id::ReactionID( "g,H->e-,e+,H[pair-production-nuclear]" ) == partials[3] );
    CHECK( id::ReactionID( "g,H->e-,H{1s1/2}" ) == partials[4] );
    CHECK( 502 == partials[0].reactionType().mt() );
    CHECK( 504 == partials[1].reactionType().mt() );
    CHECK( 515 == partials[2].reactionType().mt() );
    CHECK( 517 == partials[3].reactionType().mt() );
    CHECK( 534 == partials[4].reactionType().mt() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 2021 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 2021 == reaction.crossSection().energies().size() );
    CHECK( 2021 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK(  137 == reaction.crossSection().boundaries()[0] );
    CHECK( 2020 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1.   , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().energies()[2020] ) );
    CHECK_THAT( 4.62084E-6, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .020718042, WithinRel( reaction.crossSection().values()[2020] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyCoherentReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->g,H[coherent]" ) == reaction.identifier() );
    CHECK( 502 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 0., WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 361 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 361 == reaction.crossSection().energies().size() );
    CHECK( 361 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 360 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1.   , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().energies()[360] ) );
    CHECK_THAT( 4.52522E-6, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 4.6282E-16, WithinRel( reaction.crossSection().values()[360] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "g" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "H" ) ) );

    auto gamma = reaction.product( id::ParticleID( "g" ) );
    CHECK( id::ParticleID( "g" ) == gamma.identifier() );
    CHECK( false == gamma.hasAverageEnergy() );
    CHECK( true == gamma.hasDistributionData() );

    CHECK( true == std::holds_alternative< int >( gamma.multiplicity() ) );
    auto multiplicity = std::get< int >( gamma.multiplicity() );
    CHECK( 1 == multiplicity );

    CHECK( std::nullopt == gamma.averageEnergy() );

    CHECK( std::nullopt != gamma.distributionData() );
    CHECK( true == std::holds_alternative< CoherentDistributionData >( gamma.distributionData().value() ) );
    auto data = std::get< CoherentDistributionData >( gamma.distributionData().value() );

    CHECK( DistributionDataType::Coherent == data.type() );
    CHECK( ReferenceFrame::Laboratory == data.frame() );

    CHECK_THAT( 0.  , WithinRel( data.scatteringFunction().lowerInverseLengthLimit() ) );
    CHECK_THAT( 1e+9, WithinRel( data.scatteringFunction().upperInverseLengthLimit() ) );
    CHECK( 1253 == data.scatteringFunction().inverseLengths().size() );
    CHECK( 1253 == data.scatteringFunction().values().size() );
    CHECK( 1 == data.scatteringFunction().boundaries().size() );
    CHECK( 1 == data.scatteringFunction().interpolants().size() );
    CHECK_THAT( 0.       , WithinRel( data.scatteringFunction().inverseLengths()[0] ) );
    CHECK_THAT( 0.001    , WithinRel( data.scatteringFunction().inverseLengths()[1] ) );
    CHECK_THAT( 512000000, WithinRel( data.scatteringFunction().inverseLengths()[1251] ) );
    CHECK_THAT( 1e+9     , WithinRel( data.scatteringFunction().inverseLengths()[1252] ) );
    CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[0] ) );
    CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[1] ) );
    CHECK_THAT( 1.1908E-37, WithinRel( data.scatteringFunction().values()[1251] ) );
    CHECK_THAT( 8.1829e-39, WithinRel( data.scatteringFunction().values()[1252] ) );
    CHECK( 1252 == data.scatteringFunction().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == data.scatteringFunction().interpolants()[0] );
    CHECK( true == data.scatteringFunction().isLinearised() );

    CHECK( std::nullopt != data.realAnomolousFormFactor() );
    auto factor = data.realAnomolousFormFactor().value();
    CHECK_THAT( 1.  , WithinRel( factor.lowerEnergyLimit() ) );
    CHECK_THAT( 1e+7, WithinRel( factor.upperEnergyLimit() ) );
    CHECK( 297 == factor.energies().size() );
    CHECK( 297 == factor.values().size() );
    CHECK( 1 == factor.boundaries().size() );
    CHECK( 1 == factor.interpolants().size() );
    CHECK_THAT( 1.        , WithinRel( factor.energies()[0] ) );
    CHECK_THAT( 2.        , WithinRel( factor.energies()[1] ) );
    CHECK_THAT( 9549925.86, WithinRel( factor.energies()[295] ) );
    CHECK_THAT( 1e+7      , WithinRel( factor.energies()[296] ) );
    CHECK_THAT( -1.00260813, WithinRel( factor.values()[0] ) );
    CHECK_THAT( -1.01054501, WithinRel( factor.values()[1] ) );
    CHECK_THAT( 2.8024E-11, WithinRel( factor.values()[295] ) );
    CHECK_THAT( 0.        , WithinRel( factor.values()[296] ) );
    CHECK( 296 == factor.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == factor.interpolants()[0] );
    CHECK( true == factor.isLinearised() );

    CHECK( std::nullopt != data.imaginaryAnomolousFormFactor() );
    factor = data.imaginaryAnomolousFormFactor().value();
    CHECK_THAT( 1.  , WithinRel( factor.lowerEnergyLimit() ) );
    CHECK_THAT( 1e+7, WithinRel( factor.upperEnergyLimit() ) );
    CHECK( 297 == factor.energies().size() );
    CHECK( 297 == factor.values().size() );
    CHECK( 1 == factor.boundaries().size() );
    CHECK( 1 == factor.interpolants().size() );
    CHECK_THAT( 1.        , WithinRel( factor.energies()[0] ) );
    CHECK_THAT( 2.        , WithinRel( factor.energies()[1] ) );
    CHECK_THAT( 9549925.86, WithinRel( factor.energies()[295] ) );
    CHECK_THAT( 1e+7      , WithinRel( factor.energies()[296] ) );
    CHECK_THAT( 0.        , WithinRel( factor.values()[0] ) );
    CHECK_THAT( 0.        , WithinRel( factor.values()[1] ) );
    CHECK_THAT( 8.9767E-15, WithinRel( factor.values()[295] ) );
    CHECK_THAT( 0.        , WithinRel( factor.values()[296] ) );
    CHECK( 296 == factor.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == factor.interpolants()[0] );
    CHECK( true == factor.isLinearised() );

    auto hydrogen = reaction.product( id::ParticleID( "H" ) );
    CHECK( id::ParticleID( "H" ) == hydrogen.identifier() );
  }

  void verifyIncoherentReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->g,H[incoherent]" ) == reaction.identifier() );
    CHECK( 504 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 0., WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 396 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 396 == reaction.crossSection().energies().size() );
    CHECK( 396 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 395 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1.   , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11, WithinRel( reaction.crossSection().energies()[395] ) );
    CHECK_THAT( 9.56230E-8, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 1.70420E-5, WithinRel( reaction.crossSection().values()[395] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "g" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "H" ) ) );

    auto gamma = reaction.product( id::ParticleID( "g" ) );
    CHECK( id::ParticleID( "g" ) == gamma.identifier() );
    CHECK( false == gamma.hasAverageEnergy() );
    CHECK( true == gamma.hasDistributionData() );

    CHECK( true == std::holds_alternative< int >( gamma.multiplicity() ) );
    auto multiplicity = std::get< int >( gamma.multiplicity() );
    CHECK( 1 == multiplicity );

    CHECK( std::nullopt == gamma.averageEnergy() );

    CHECK( std::nullopt != gamma.distributionData() );
    CHECK( true == std::holds_alternative< IncoherentDistributionData >( gamma.distributionData().value() ) );
    auto data = std::get< IncoherentDistributionData >( gamma.distributionData().value() );

    CHECK( DistributionDataType::Incoherent == data.type() );
    CHECK( ReferenceFrame::Laboratory == data.frame() );

    CHECK_THAT( 0.  , WithinRel( data.scatteringFunction().lowerInverseLengthLimit() ) );
    CHECK_THAT( 1e+9, WithinRel( data.scatteringFunction().upperInverseLengthLimit() ) );
    CHECK( 398 == data.scatteringFunction().inverseLengths().size() );
    CHECK( 398 == data.scatteringFunction().values().size() );
    CHECK( 1 == data.scatteringFunction().boundaries().size() );
    CHECK( 1 == data.scatteringFunction().interpolants().size() );
    CHECK_THAT( 0.       , WithinRel( data.scatteringFunction().inverseLengths()[0] ) );
    CHECK_THAT( 1e-7     , WithinRel( data.scatteringFunction().inverseLengths()[1] ) );
    CHECK_THAT( 512000000, WithinRel( data.scatteringFunction().inverseLengths()[396] ) );
    CHECK_THAT( 1e+9     , WithinRel( data.scatteringFunction().inverseLengths()[397] ) );
    CHECK_THAT( 0.        , WithinRel( data.scatteringFunction().values()[0] ) );
    CHECK_THAT( 4.4097E-13, WithinRel( data.scatteringFunction().values()[1] ) );
    CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[396] ) );
    CHECK_THAT( 1.        , WithinRel( data.scatteringFunction().values()[397] ) );
    CHECK( 397 == data.scatteringFunction().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == data.scatteringFunction().interpolants()[0] );
    CHECK( true == data.scatteringFunction().isLinearised() );

    auto hydrogen = reaction.product( id::ParticleID( "H" ) );
    CHECK( id::ParticleID( "H" ) == hydrogen.identifier() );
  }

  void verifyElectronFieldPairProductionReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->2e-,e+,H[pair-production-electron]" ) == reaction.identifier() );
    CHECK( 515 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -1.022e+6, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 217 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 217 == reaction.crossSection().energies().size() );
    CHECK( 217 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 216 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 2044000., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( reaction.crossSection().energies()[216] ) );
    CHECK_THAT( 0.      , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .0111   , WithinRel( reaction.crossSection().values()[216] ) );

    CHECK( 4 == reaction.numberProducts() );
    CHECK( 2 == reaction.numberProducts( id::ParticleID( "e-" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "e+" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "H" ) ) );

    auto electron = reaction.product( id::ParticleID( "e-" ) );
    CHECK( id::ParticleID( "e-" ) == electron.identifier() );

    electron = reaction.product( id::ParticleID( "e-" ), 1 );
    CHECK( id::ParticleID( "e-" ) == electron.identifier() );

    auto positron = reaction.product( id::ParticleID( "e+" ) );
    CHECK( id::ParticleID( "e+" ) == positron.identifier() );

    auto hydrogen = reaction.product( id::ParticleID( "H" ) );;
    CHECK( id::ParticleID( "H" ) == hydrogen.identifier() );
  }

  void verifyNuclearFieldPairProductionReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->e-,e+,H[pair-production-nuclear]" ) == reaction.identifier() );
    CHECK( 517 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -1.022e+6, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 308 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 308 == reaction.crossSection().energies().size() );
    CHECK( 308 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 307 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1022000., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( reaction.crossSection().energies()[307] ) );
    CHECK_THAT( 0.      , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .009601 , WithinRel( reaction.crossSection().values()[307] ) );

    CHECK( 3 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "e-" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "e+" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "H" ) ) );

    auto electron = reaction.product( id::ParticleID( "e-" ) );
    CHECK( id::ParticleID( "e-" ) == electron.identifier() );

    auto positron = reaction.product( id::ParticleID( "e+" ) );
    CHECK( id::ParticleID( "e+" ) == positron.identifier() );

    auto hydrogen = reaction.product( id::ParticleID( "H" ) );
    CHECK( id::ParticleID( "H" ) == hydrogen.identifier() );
  }

  void verifyTotalPairProductionReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->pair-production" ) == reaction.identifier() );
    CHECK( 516 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 2 == partials.size() );
    CHECK( id::ReactionID( "g,H->2e-,e+,H[pair-production-electron]" ) == partials[0] );
    CHECK( id::ReactionID( "g,H->e-,e+,H[pair-production-nuclear]" ) == partials[1] );
    CHECK( 515 == partials[0].reactionType().mt() );
    CHECK( 517 == partials[1].reactionType().mt() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 466 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 466 == reaction.crossSection().energies().size() );
    CHECK( 466 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 465 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1022000., WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( reaction.crossSection().energies()[465] ) );
    CHECK_THAT( 0.      , WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .020701 , WithinRel( reaction.crossSection().values()[465] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyIonisationReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->e-,H{1s1/2}" ) == reaction.identifier() );
    CHECK( 534 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -13.6, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 904 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 904 == reaction.crossSection().energies().size() );
    CHECK( 904 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 903 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 13.6    , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( reaction.crossSection().energies()[903] ) );
    CHECK_THAT( 6318358.25, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 7.7360E-15, WithinRel( reaction.crossSection().values()[903] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "e-" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "H{1s1/2}" ) ) );

    auto electron = reaction.product( id::ParticleID( "e-" ) );
    CHECK( id::ParticleID( "e-" ) == electron.identifier() );

    auto ion = reaction.product( id::ParticleID( "H{1s1/2}" ) );
    CHECK( id::ParticleID( "H{1s1/2}" ) == ion.identifier() );
  }

  void verifyTotalIonisationReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "g,H->e-,H" ) == reaction.identifier() );
    CHECK( 522 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 1 == partials.size() );
    CHECK( id::ReactionID( "g,H->e-,H{1s1/2}" ) == partials[0] );
    CHECK( 534 == partials[0].reactionType().mt() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 904 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 904 == reaction.crossSection().energies().size() );
    CHECK( 904 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 903 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 13.6    , WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+11   , WithinRel( reaction.crossSection().energies()[903] ) );
    CHECK_THAT( 6318358.25, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 7.7360E-15, WithinRel( reaction.crossSection().values()[903] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyH0( const ProjectileTarget& H0, bool normalise ) {

    verifyDocumentation( H0.documentation() );

    CHECK( id::ParticleID( "g" ) == H0.projectileIdentifier() );
    CHECK( id::ParticleID( "H" ) == H0.targetIdentifier() );

    CHECK( InteractionType::Atomic == H0.interactionType() );

    CHECK( std::nullopt == H0.resonances() );

    CHECK( true == H0.hasReaction( id::ReactionID(  "g,H->total[atomic]" ) ) );
    CHECK( true == H0.hasReaction( id::ReactionID(  "g,H->g,H[coherent]" ) ) );
    CHECK( true == H0.hasReaction( id::ReactionID(  "g,H->g,H[incoherent]" ) ) );
    CHECK( true == H0.hasReaction( id::ReactionID(  "g,H->2e-,e+,H[pair-production-electron]" ) ) );
    CHECK( true == H0.hasReaction( id::ReactionID(  "g,H->pair-production" ) ) );
    CHECK( true == H0.hasReaction( id::ReactionID(  "g,H->e-,e+,H[pair-production-nuclear]" ) ) );
    CHECK( true == H0.hasReaction( id::ReactionID(  "g,H->e-,H" ) ) );
    CHECK( true == H0.hasReaction( id::ReactionID(  "g,H->e-,H{1s1/2}" ) ) );
//    CHECK( false == H0.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

    CHECK( 8 == H0.reactions().size() );

    auto total = H0.reactions()[0];
    verifyTotalReaction( total );

    auto coherent = H0.reactions()[1];
    verifyCoherentReaction( coherent );

    auto incoherent = H0.reactions()[2];
    verifyIncoherentReaction( incoherent );

    auto epairproduction = H0.reactions()[3];
    verifyElectronFieldPairProductionReaction( epairproduction );

    auto tpairproduction = H0.reactions()[4];
    verifyTotalPairProductionReaction( tpairproduction );

    auto npairproduction = H0.reactions()[5];
    verifyNuclearFieldPairProductionReaction( npairproduction );

    auto tionisation = H0.reactions()[6];
    verifyTotalIonisationReaction( tionisation );

    auto ionisation = H0.reactions()[7];
    verifyIonisationReaction( ionisation );

    total = H0.reaction( id::ReactionID( "g,H->total[atomic]" ) );
    verifyTotalReaction( total );

    coherent = H0.reaction( id::ReactionID( "g,H->g,H[coherent]" ) );
    verifyCoherentReaction( coherent );

    incoherent = H0.reaction( id::ReactionID( "g,H->g,H[incoherent]" ) );
    verifyIncoherentReaction( incoherent );

    epairproduction = H0.reaction( id::ReactionID( "g,H->2e-,e+,H[pair-production-electron]" ) );
    verifyElectronFieldPairProductionReaction( epairproduction );

    tpairproduction = H0.reaction( id::ReactionID( "g,H->pair-production" ) );
    verifyTotalPairProductionReaction( tpairproduction );

    npairproduction = H0.reaction( id::ReactionID( "g,H->e-,e+,H[pair-production-nuclear]" ) );
    verifyNuclearFieldPairProductionReaction( npairproduction );

    tionisation = H0.reaction( id::ReactionID( "g,H->e-,H" ) );
    verifyTotalIonisationReaction( tionisation );

    ionisation = H0.reaction( id::ReactionID( "g,H->e-,H{1s1/2}" ) );
    verifyIonisationReaction( ionisation );
  }

} // namespace h1
} // namespace neutron
