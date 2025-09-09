namespace neutron {

// test functions based on n-093_Np_236m1.endf
namespace np236m1 {

  void verifyDocumentation( const Documentation& documentation ) {

    std::string description =
        " 93-Np-236M LANL      EVAL-JAN17 T. Kawano, P.Talou               \n"
        " NDS 148, 1 (2018)    DIST-AUG24 REV1-NOV19            20240830   \n"
        "---- ENDF/B-VIII.1    MATERIAL 9344         REVISION 1            \n"
        "----- INCIDENT-NEUTRON DATA                                       \n"
        "------ ENDF-6                                                     \n"
        "                                                                  \n"
        "******************************************************************\n"
        " Np-236m Evaluation                                               \n"
        "                                              T. Kawano, P. Talou \n"
        "                                                        Jan. 2012 \n"
        "******************************************************************\n"
        " Evaluation based on:                                             \n"
        "    ENDF/B-VII.1 (JENDL-4.0) Np236 ground state data              \n"
        "    CoH3 calculation to the ground and 60keV levels               \n"
        "                                                                  \n"
        " The coupled-channels calculation in JENDL-4.0 assumes            \n"
        " the following level scheme, where all the excited levels         \n"
        " except for 60keV meta state are postulated.                      \n"
        "                                                                  \n"
        "    -------------------                                           \n"
        "    No.  Ex(MeV)   J PI                                           \n"
        "    -------------------                                           \n"
        "     0  0.00000   6  -  *                                         \n"
        "     1  0.05600   7  -  *                                         \n"
        "     2  0.06000   1  +                                            \n"
        "     3  0.07600   2  +                                            \n"
        "     4  0.10000   3  +                                            \n"
        "     5  0.12000   8  -  *                                         \n"
        "     6  0.13200   4  +                                            \n"
        "                                                                  \n"
        " First we followed the same g.s. calculation as JENDL to try to   \n"
        " reproduce all the g.s. cross sections. Then the same parameters  \n"
        " are employed to calculate cross sections on the excited state,   \n"
        " with the coupling of 1+, 2+, 3+, and 4+ states.                  \n"
        "                                                                  \n"
        " MF1 MT452, 455, 456                                              \n"
        "    same as ground state                                          \n"
        "                                                                  \n"
        " MF2                                                              \n"
        "    the same resonance parameters for the ground state,           \n"
        "    but spins were changed.                                       \n"
        "                                                                  \n"
        " MF3                                                              \n"
        "    The following cross sections were evaluated by applying       \n"
        "    a scaling factor of F to the ground state cross sections,     \n"
        "    where F = CoH(meta) / CoH(ground).                            \n"
        "                                                                  \n"
        "    MT  16 (n,2n)                                                 \n"
        "    MT  17 (n,3n)                                                 \n"
        "    MT  18 fission                                                \n"
        "    MT  37 (n,4n)                                                 \n"
        "                                                                  \n"
        "    These sections below were replaced by the CoH excited state   \n"
        "    calculations.                                                 \n"
        "                                                                  \n"
        "    MT   1 total                                                  \n"
        "    MT   2 elastic = total - sum of partials                      \n"
        "    MT  51 - 56 discrete level inelastic scattering               \n"
        "    MT  91 continuum inelastic scattering                         \n"
        "    MT 102 radiative capture                                      \n"
        "                                                                  \n"
        " MF4                                                              \n"
        "    MT   2, 51 - 56, new CoH calculations                         \n"
        "                                                                  \n"
        " MF5                                                              \n"
        "    same as g.s.                                                  \n"
        "                                                                  \n"
        " MF6                                                              \n"
        "    MT  51 - 56                                                   \n"
        "    the angular distributions for the disrete levels removed,     \n"
        "    and given in new evaluations in MF4                           \n"
        "                                                                  \n"
        "    MT  16, 17, 37, 91, 102                                       \n"
        "    same as g.s.                                                  \n"
        "                                                                  \n"
        " MF12 MT18                                                        \n"
        "    same as g.s.                                                  \n"
        "                                                                  \n"
        " MF14 MT18                                                        \n"
        "    same as g.s.                                                  \n"
        "                                                                  \n"
        " MF15 MT18                                                        \n"
        "    same as g.s.                                                  \n"
        "                                                                  \n"
        "******************************************************************\n"
        "                                                                  \n"
        " ***************** Program LINEAR (VERSION 2017-1) ***************\n"
        " For All Data Greater than 1.0000E-10 barns in Absolute Value     \n"
        " Data Linearized to Within an Accuracy of .100000000 per-cent     \n"
        " ***************** Program FIXUP (Version 2017-1) ****************\n"
        " Corrected ZA/AWR in All Sections-----------------------------Yes \n"
        " Corrected Thresholds-----------------------------------------No  \n"
        " Extended Cross Sections to 20 MeV----------------------------No  \n"
        " Allow Cross Section Deletion---------------------------------No  \n"
        " Allow Cross Section Reconstruction---------------------------Yes \n"
        " Make All Cross Sections Non-Negative-------------------------Yes \n"
        " Delete Energies Not in Ascending Order-----------------------Yes \n"
        " Deleted Duplicate Points-------------------------------------Yes \n"
        " Check for Ascending MAT/MF/MT Order--------------------------Yes \n"
        " Check for Legal MF/MT Numbers--------------------------------Yes \n"
        " Allow Creation of Missing Sections---------------------------No  \n"
        " Allow Insertion of Energy Points-----------------------------No  \n"
        " Uniform Energy Grid for ALL MT-------------------------------No  \n"
        " Delete Section if Cross Section =0 at All Energies-----------Yes \n";

    CHECK( std::nullopt == documentation.awr() );
    CHECK( std::nullopt == documentation.library() );
    CHECK( std::nullopt == documentation.version() );
    CHECK( std::nullopt == documentation.description() );
  }

  void verifyTotalReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->total" ) == reaction.identifier() );
    CHECK( 1 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 13 == partials.size() );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e2" ) == partials[0] );
    CHECK( id::ReactionID( "n,Np236_e2->2n,Np235[all]" ) == partials[1] );
    CHECK( id::ReactionID( "n,Np236_e2->3n,Np234[all]" ) == partials[2] );
    CHECK( id::ReactionID( "n,Np236_e2->fission" ) == partials[3] );
    CHECK( id::ReactionID( "n,Np236_e2->4n,Np233[all]" ) == partials[4] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236" ) == partials[5] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e1" ) == partials[6] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e3" ) == partials[7] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e4" ) == partials[8] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e5" ) == partials[9] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e6" ) == partials[10] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236[continuum]" ) == partials[11] );
    CHECK( id::ReactionID( "n,Np236_e2->g,Np237[all]" ) == partials[12] );
    CHECK(  52 == partials[0].reactionType().mt() );
    CHECK(  16 == partials[1].reactionType().mt() );
    CHECK(  17 == partials[2].reactionType().mt() );
    CHECK(  18 == partials[3].reactionType().mt() );
    CHECK(  37 == partials[4].reactionType().mt() );
    CHECK(  50 == partials[5].reactionType().mt() );
    CHECK(  51 == partials[6].reactionType().mt() );
    CHECK(  53 == partials[7].reactionType().mt() );
    CHECK(  54 == partials[8].reactionType().mt() );
    CHECK(  55 == partials[9].reactionType().mt() );
    CHECK(  56 == partials[10].reactionType().mt() );
    CHECK(  91 == partials[11].reactionType().mt() );
    CHECK( 102 == partials[12].reactionType().mt() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 255 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 255 == reaction.crossSection().energies().size() );
    CHECK( 255 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK(   2 == reaction.crossSection().boundaries()[0] );
    CHECK( 254 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 21.5, WithinRel( reaction.crossSection().energies()[2] ) );
    CHECK_THAT( 21.5, WithinRel( reaction.crossSection().energies()[3] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[254] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[2] ) );
    CHECK_THAT( 97.9899276, WithinRel( reaction.crossSection().values()[3] ) );
    CHECK_THAT( 6.24239181, WithinRel( reaction.crossSection().values()[254] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyElasticReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e2" ) == reaction.identifier() );
    CHECK( 52 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 0, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 91 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 91 == reaction.crossSection().energies().size() );
    CHECK( 91 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK( 2 == reaction.crossSection().boundaries()[0] );
    CHECK( 90 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 21.5, WithinRel( reaction.crossSection().energies()[2] ) );
    CHECK_THAT( 21.5, WithinRel( reaction.crossSection().energies()[3] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[90] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[2] ) );
    CHECK_THAT( 21.7398100, WithinRel( reaction.crossSection().values()[3] ) );
    CHECK_THAT( 3.16616600, WithinRel( reaction.crossSection().values()[90] ) );

    CHECK( 1 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( true == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt != neutron.distributionData() );
    CHECK( true == std::holds_alternative< TwoBodyDistributionData >( neutron.distributionData().value() ) );
    auto data = std::get< TwoBodyDistributionData >( neutron.distributionData().value() );
    CHECK( DistributionDataType::TwoBody == data.type() );
    CHECK( true == std::holds_alternative< LegendreAngularDistributions >( data.angle() ) );
    auto angle = std::get< LegendreAngularDistributions >( data.angle() );
    CHECK( 74 == angle.numberPoints() );
    CHECK( 1 == angle.numberRegions() );
    CHECK( 74 == angle.grid().size() );
    CHECK( 74 == angle.distributions().size() );
    CHECK( 1 == angle.boundaries().size() );
    CHECK( 1 == angle.interpolants().size() );
    CHECK_THAT( 1e-5   , WithinRel( angle.grid()[0] ) );
    CHECK_THAT( 700.   , WithinRel( angle.grid()[1] ) );
    CHECK_THAT( 1.95e+7, WithinRel( angle.grid()[72] ) );
    CHECK_THAT( 2e+7   , WithinRel( angle.grid()[73] ) );
    CHECK(  1 == angle.distributions()[0].pdf().coefficients().size() );
    CHECK(  1 == angle.distributions()[1].pdf().coefficients().size() );
    CHECK( 27 == angle.distributions()[72].pdf().coefficients().size() );
    CHECK( 27 == angle.distributions()[73].pdf().coefficients().size() );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].pdf().coefficients()[0] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[1].pdf().coefficients()[0] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[72].pdf().coefficients()[0] ) );
    CHECK_THAT( 9.487146e-1 *  3. / 2., WithinRel( angle.distributions()[72].pdf().coefficients()[1] ) );
    CHECK_THAT( 8.682816e-6 * 51. / 2., WithinRel( angle.distributions()[72].pdf().coefficients()[25] ) );
    CHECK_THAT( 2.464549e-6 * 53. / 2., WithinRel( angle.distributions()[72].pdf().coefficients()[26] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[73].pdf().coefficients()[0] ) );
    CHECK_THAT( 9.503846e-1 *  3. / 2., WithinRel( angle.distributions()[73].pdf().coefficients()[1] ) );
    CHECK_THAT( 1.203251e-5 * 51. / 2., WithinRel( angle.distributions()[73].pdf().coefficients()[25] ) );
    CHECK_THAT( 3.526347e-6 * 53. / 2., WithinRel( angle.distributions()[73].pdf().coefficients()[26] ) );
    CHECK(  2 == angle.distributions()[0].cdf().coefficients().size() );
    CHECK(  2 == angle.distributions()[1].cdf().coefficients().size() );
    CHECK( 28 == angle.distributions()[72].cdf().coefficients().size() );
    CHECK( 28 == angle.distributions()[73].cdf().coefficients().size() );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].cdf().coefficients()[1] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[1].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[1].cdf().coefficients()[1] ) );
    CHECK_THAT( 0.0256427       , WithinRel( angle.distributions()[72].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.0591044       , WithinRel( angle.distributions()[72].cdf().coefficients()[1] ) );
    CHECK_THAT( 4.341408e-6     , WithinRel( angle.distributions()[72].cdf().coefficients()[26] ) );
    CHECK_THAT( 1.2322745e-6    , WithinRel( angle.distributions()[72].cdf().coefficients()[27] ) );
    CHECK_THAT( 0.0248077       , WithinRel( angle.distributions()[73].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.05699955      , WithinRel( angle.distributions()[73].cdf().coefficients()[1] ) );
    CHECK_THAT( 6.016255e-6     , WithinRel( angle.distributions()[73].cdf().coefficients()[26] ) );
    CHECK_THAT( 1.7631735e-6    , WithinRel( angle.distributions()[73].cdf().coefficients()[27] ) );
    CHECK( 73 == angle.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );
  }

  void verifyN2NReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->2n,Np235[all]" ) == reaction.identifier() );
    CHECK( 16 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -5676680, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 30 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 30 == reaction.crossSection().energies().size() );
    CHECK( 30 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 29 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 5700940, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(    2e+7, WithinRel( reaction.crossSection().energies()[29] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .110849100, WithinRel( reaction.crossSection().values()[29] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "g" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( false == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 2 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt == neutron.distributionData() );

    auto gamma = reaction.product( id::ParticleID( "g" ) );
    CHECK( id::ParticleID( "g" ) == gamma.identifier() );
    CHECK( false == gamma.hasAverageEnergy() );
    CHECK( false == gamma.hasDistributionData() );
    CHECK( true == std::holds_alternative< TabulatedMultiplicity >( gamma.multiplicity() ) );
    auto table_multiplicity = std::get< TabulatedMultiplicity >( gamma.multiplicity() );
    CHECK( true == table_multiplicity.isLinearised() );
    CHECK( 30 == table_multiplicity.numberPoints() );
    CHECK( 1 == table_multiplicity.numberRegions() );
    CHECK( 30 == table_multiplicity.energies().size() );
    CHECK( 30 == table_multiplicity.values().size() );
    CHECK( 1 == table_multiplicity.boundaries().size() );
    CHECK( 1 == table_multiplicity.interpolants().size() );
    CHECK( 29 == table_multiplicity.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == table_multiplicity.interpolants()[0] );
    CHECK_THAT(  5.700940e+6, WithinRel( table_multiplicity.energies()[0] ) );
    CHECK_THAT(         2e+7, WithinRel( table_multiplicity.energies()[29] ) );
    CHECK_THAT( 1.007610, WithinRel( table_multiplicity.values()[0] ) );
    CHECK_THAT( 5.810220, WithinRel( table_multiplicity.values()[29] ) );
    CHECK( std::nullopt == gamma.averageEnergy() );
    CHECK( std::nullopt == gamma.distributionData() );
  }

  void verifyN3NReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->3n,Np234[all]" ) == reaction.identifier() );
    CHECK( 17 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -12659800, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 15 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 15 == reaction.crossSection().energies().size() );
    CHECK( 15 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 14 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 12713900, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(     2e+7, WithinRel( reaction.crossSection().energies()[14] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .080226890, WithinRel( reaction.crossSection().values()[14] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "g" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( false == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 3 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt == neutron.distributionData() );

    auto gamma = reaction.product( id::ParticleID( "g" ) );
    CHECK( id::ParticleID( "g" ) == gamma.identifier() );
    CHECK( false == gamma.hasAverageEnergy() );
    CHECK( false == gamma.hasDistributionData() );
    CHECK( true == std::holds_alternative< TabulatedMultiplicity >( gamma.multiplicity() ) );
    auto table_multiplicity = std::get< TabulatedMultiplicity >( gamma.multiplicity() );
    CHECK( true == table_multiplicity.isLinearised() );
    CHECK( 15 == table_multiplicity.numberPoints() );
    CHECK( 1 == table_multiplicity.numberRegions() );
    CHECK( 15 == table_multiplicity.energies().size() );
    CHECK( 15 == table_multiplicity.values().size() );
    CHECK( 1 == table_multiplicity.boundaries().size() );
    CHECK( 1 == table_multiplicity.interpolants().size() );
    CHECK( 14 == table_multiplicity.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == table_multiplicity.interpolants()[0] );
    CHECK_THAT( 1.271390e+7, WithinRel( table_multiplicity.energies()[0] ) );
    CHECK_THAT(        2e+7, WithinRel( table_multiplicity.energies()[14] ) );
    CHECK_THAT( 2.863370, WithinRel( table_multiplicity.values()[0] ) );
    CHECK_THAT( 6.273080, WithinRel( table_multiplicity.values()[14] ) );
    CHECK( std::nullopt == gamma.averageEnergy() );
    CHECK( std::nullopt == gamma.distributionData() );
  }

  void verifyFissionReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->fission" ) == reaction.identifier() );
    CHECK( 18 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 159 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 159 == reaction.crossSection().energies().size() );
    CHECK( 159 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK(   2 == reaction.crossSection().boundaries()[0] );
    CHECK( 158 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 21.5, WithinRel( reaction.crossSection().energies()[2] ) );
    CHECK_THAT( 21.5, WithinRel( reaction.crossSection().energies()[3] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[158] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[2] ) );
    CHECK_THAT( 70.55598, WithinRel( reaction.crossSection().values()[3] ) );
    CHECK_THAT( 2.549846, WithinRel( reaction.crossSection().values()[158] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyN4NReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->4n,Np233[all]" ) == reaction.identifier() );
    CHECK( 37 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -18724200, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 3 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 3 == reaction.crossSection().energies().size() );
    CHECK( 3 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 2 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 18804200, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(     2e+7, WithinRel( reaction.crossSection().energies()[2] ) );
    CHECK_THAT(           0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 5.265795E-6, WithinRel( reaction.crossSection().values()[2] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "g" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( false == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 4 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt == neutron.distributionData() );

    auto gamma = reaction.product( id::ParticleID( "g" ) );
    CHECK( id::ParticleID( "g" ) == gamma.identifier() );
    CHECK( false == gamma.hasAverageEnergy() );
    CHECK( false == gamma.hasDistributionData() );
    CHECK( true == std::holds_alternative< TabulatedMultiplicity >( gamma.multiplicity() ) );
    auto table_multiplicity = std::get< TabulatedMultiplicity >( gamma.multiplicity() );
    CHECK( true == table_multiplicity.isLinearised() );
    CHECK( 3 == table_multiplicity.numberPoints() );
    CHECK( 1 == table_multiplicity.numberRegions() );
    CHECK( 3 == table_multiplicity.energies().size() );
    CHECK( 3 == table_multiplicity.values().size() );
    CHECK( 1 == table_multiplicity.boundaries().size() );
    CHECK( 1 == table_multiplicity.interpolants().size() );
    CHECK( 2 == table_multiplicity.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == table_multiplicity.interpolants()[0] );
    CHECK_THAT( 1.880420e+7, WithinRel( table_multiplicity.energies()[0] ) );
    CHECK_THAT(        2e+7, WithinRel( table_multiplicity.energies()[2] ) );
    CHECK_THAT( .3181690, WithinRel( table_multiplicity.values()[0] ) );
    CHECK_THAT( 1.294600, WithinRel( table_multiplicity.values()[2] ) );
    CHECK( std::nullopt == gamma.averageEnergy() );
    CHECK( std::nullopt == gamma.distributionData() );
  }

  void verifyInelasticReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->n,Np236[all]" ) == reaction.identifier() );
    CHECK( 4 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 7 == partials.size() );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236" ) == partials[0] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e1" ) == partials[1] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e3" ) == partials[2] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e4" ) == partials[3] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e5" ) == partials[4] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e6" ) == partials[5] );
    CHECK( id::ReactionID( "n,Np236_e2->n,Np236[continuum]" ) == partials[6] );
    CHECK(  50 == partials[0].reactionType().mt() );
    CHECK(  51 == partials[1].reactionType().mt() );
    CHECK(  53 == partials[2].reactionType().mt() );
    CHECK(  54 == partials[3].reactionType().mt() );
    CHECK(  55 == partials[4].reactionType().mt() );
    CHECK(  56 == partials[5].reactionType().mt() );
    CHECK(  91 == partials[6].reactionType().mt() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 88 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 88 == reaction.crossSection().energies().size() );
    CHECK( 88 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK( 2 == reaction.crossSection().boundaries()[0] );
    CHECK( 87 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 21.5, WithinRel( reaction.crossSection().energies()[2] ) );
    CHECK_THAT( 21.5, WithinRel( reaction.crossSection().energies()[3] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[87] ) );
    CHECK_THAT(           0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT(           0, WithinRel( reaction.crossSection().values()[2] ) );
    CHECK_THAT( 2.587731E-6, WithinRel( reaction.crossSection().values()[3] ) );
    CHECK_THAT( 0.335078297, WithinRel( reaction.crossSection().values()[87] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyInelasticReactionLevel0( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->n,Np236" ) == reaction.identifier() );
    CHECK( 50 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 60000, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 56 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 56 == reaction.crossSection().energies().size() );
    CHECK( 56 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 55 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[55] ) );
    CHECK_THAT( 0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 0, WithinRel( reaction.crossSection().values()[55] ) );

    CHECK( 1 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( false == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt == neutron.distributionData() );
  }

  void verifyInelasticReactionLevel1( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e1" ) == reaction.identifier() );
    CHECK( 51 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 4000, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 84 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 84 == reaction.crossSection().energies().size() );
    CHECK( 84 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK(  2 == reaction.crossSection().boundaries()[0] );
    CHECK( 83 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[83] ) );
    CHECK_THAT( 0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 2.703236E-6, WithinRel( reaction.crossSection().values()[83] ) );

    CHECK( 1 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( false == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt == neutron.distributionData() );
  }

  void verifyInelasticReactionLevel3( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e3" ) == reaction.identifier() );
    CHECK( 53 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -16000, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 67 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 67 == reaction.crossSection().energies().size() );
    CHECK( 67 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 66 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 16068.36, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(     2e+7, WithinRel( reaction.crossSection().energies()[66] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .070010070, WithinRel( reaction.crossSection().values()[66] ) );

    CHECK( 1 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( false == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt == neutron.distributionData() );
  }

  void verifyInelasticReactionLevel4( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e4" ) == reaction.identifier() );
    CHECK( 54 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -40000, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 65 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 65 == reaction.crossSection().energies().size() );
    CHECK( 65 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 64 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 40170.89, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(     2e+7, WithinRel( reaction.crossSection().energies()[64] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .066339170, WithinRel( reaction.crossSection().values()[64] ) );

    CHECK( 1 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( false == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt == neutron.distributionData() );
  }

  void verifyInelasticReactionLevel5( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e5" ) == reaction.identifier() );
    CHECK( 55 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -60000, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 64 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 64 == reaction.crossSection().energies().size() );
    CHECK( 64 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 63 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 60256.34, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(     2e+7, WithinRel( reaction.crossSection().energies()[63] ) );
    CHECK_THAT(           0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 2.703376E-6, WithinRel( reaction.crossSection().values()[63] ) );

    CHECK( 1 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( false == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt == neutron.distributionData() );
  }

  void verifyInelasticReactionLevel6( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->n,Np236_e6" ) == reaction.identifier() );
    CHECK( 56 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -72000, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 63 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 63 == reaction.crossSection().energies().size() );
    CHECK( 63 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 62 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 72307.61, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(     2e+7, WithinRel( reaction.crossSection().energies()[62] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .011412050, WithinRel( reaction.crossSection().values()[62] ) );

    CHECK( 1 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( false == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt == neutron.distributionData() );
  }

  void verifyInelasticReactionContinuum( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->n,Np236[continuum]" ) == reaction.identifier() );
    CHECK( 91 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( -72000, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 63 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 63 == reaction.crossSection().energies().size() );
    CHECK( 63 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 62 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 72307.61, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT(     2e+7, WithinRel( reaction.crossSection().energies()[62] ) );
    CHECK_THAT(          0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( .187311600, WithinRel( reaction.crossSection().values()[62] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "g" ) ) );

    auto neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.identifier() );
    CHECK( false == neutron.hasAverageEnergy() );
    CHECK( false == neutron.hasDistributionData() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    auto multiplicity = std::get< int >( neutron.multiplicity() );
    CHECK( 1 == multiplicity );
    CHECK( std::nullopt == neutron.averageEnergy() );
    CHECK( std::nullopt == neutron.distributionData() );

    auto gamma = reaction.product( id::ParticleID( "g" ) );
    CHECK( id::ParticleID( "g" ) == gamma.identifier() );
    CHECK( false == gamma.hasAverageEnergy() );
    CHECK( false == gamma.hasDistributionData() );
    CHECK( true == std::holds_alternative< TabulatedMultiplicity >( gamma.multiplicity() ) );
    auto table_multiplicity = std::get< TabulatedMultiplicity >( gamma.multiplicity() );
    CHECK( true == table_multiplicity.isLinearised() );
    CHECK( 64 == table_multiplicity.numberPoints() );
    CHECK( 1 == table_multiplicity.numberRegions() );
    CHECK( 64 == table_multiplicity.energies().size() );
    CHECK( 64 == table_multiplicity.values().size() );
    CHECK( 1 == table_multiplicity.boundaries().size() );
    CHECK( 1 == table_multiplicity.interpolants().size() );
    CHECK( 63 == table_multiplicity.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == table_multiplicity.interpolants()[0] );
    CHECK_THAT( 72307.61, WithinRel( table_multiplicity.energies()[0] ) );
    CHECK_THAT(     2e+7, WithinRel( table_multiplicity.energies()[63] ) );
    CHECK_THAT(          1, WithinRel( table_multiplicity.values()[0] ) );
    CHECK_THAT( 5.982620+0, WithinRel( table_multiplicity.values()[63] ) );
    CHECK( std::nullopt == gamma.averageEnergy() );
    CHECK( std::nullopt == gamma.distributionData() );
  }

  void verifyCaptureReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->g,Np237[all]" ) == reaction.identifier() );
    CHECK( 102 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 6637350, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 239 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 239 == reaction.crossSection().energies().size() );
    CHECK( 239 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK(   2 == reaction.crossSection().boundaries()[0] );
    CHECK( 238 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 21.5, WithinRel( reaction.crossSection().energies()[2] ) );
    CHECK_THAT( 21.5, WithinRel( reaction.crossSection().energies()[3] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[238] ) );
    CHECK_THAT(           0, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT(           0, WithinRel( reaction.crossSection().values()[2] ) );
    CHECK_THAT(  5.69413500, WithinRel( reaction.crossSection().values()[3] ) );
    CHECK_THAT( 2.202558E-4, WithinRel( reaction.crossSection().values()[238] ) );

    CHECK( 1 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "g" ) ) );

    auto gamma = reaction.product( id::ParticleID( "g" ) );
    CHECK( id::ParticleID( "g" ) == gamma.identifier() );
  }

  void verifyNp236m1( const ProjectileTarget& Np236m1, bool normalise ) {

    verifyDocumentation( Np236m1.documentation() );

    CHECK( id::ParticleID( "n" ) == Np236m1.projectileIdentifier() );
    CHECK( id::ParticleID( "Np236_e2" ) == Np236m1.targetIdentifier() );

    CHECK( InteractionType::Nuclear == Np236m1.interactionType() );

    CHECK( std::nullopt == Np236m1.resonances() );

    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->total" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->n,Np236_e2" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->2n,Np235[all]" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->3n,Np234[all]" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->fission" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->4n,Np233[all]" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->n,Np236[all]" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->n,Np236" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->n,Np236_e1" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->n,Np236_e2" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->n,Np236_e3" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->n,Np236_e4" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->n,Np236_e5" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->n,Np236_e6" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->n,Np236[continuum]" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->g,Np237[all]" ) ) );
    CHECK( false == Np236m1.hasReaction( id::ReactionID( "n,H1->n,H1" ) ) );

    CHECK( 15 == Np236m1.reactions().size() );

    auto total = Np236m1.reactions()[0];
    verifyTotalReaction( total );

    auto elastic = Np236m1.reactions()[1];
    verifyElasticReaction( elastic );

    auto inelastic = Np236m1.reactions()[2];
    verifyInelasticReaction( inelastic );

    auto n2n = Np236m1.reactions()[3];
    verifyN2NReaction( n2n );

    auto n3n = Np236m1.reactions()[4];
    verifyN3NReaction( n3n );

    auto fission = Np236m1.reactions()[5];
    verifyFissionReaction( fission );

    auto n4n = Np236m1.reactions()[6];
    verifyN4NReaction( n4n );

    auto inelastic0 = Np236m1.reactions()[7];
    verifyInelasticReactionLevel0( inelastic0 );

    auto inelastic1 = Np236m1.reactions()[8];
    verifyInelasticReactionLevel1( inelastic1 );

    auto inelastic3 = Np236m1.reactions()[9];
    verifyInelasticReactionLevel3( inelastic3 );

    auto inelastic4 = Np236m1.reactions()[10];
    verifyInelasticReactionLevel4( inelastic4 );

    auto inelastic5 = Np236m1.reactions()[11];
    verifyInelasticReactionLevel5( inelastic5 );

    auto inelastic6 = Np236m1.reactions()[12];
    verifyInelasticReactionLevel6( inelastic6 );

    auto inelastic_cont = Np236m1.reactions()[13];
    verifyInelasticReactionContinuum( inelastic_cont );

    auto capture = Np236m1.reactions()[14];
    verifyCaptureReaction( capture );

    total = Np236m1.reaction( id::ReactionID( "n,Np236_e2->total" ) );
    verifyTotalReaction( total );

    elastic = Np236m1.reaction( id::ReactionID( "n,Np236_e2->n,Np236_e2" ) );
    verifyElasticReaction( elastic );

    n2n = Np236m1.reaction( id::ReactionID( "n,Np236_e2->2n,Np235[all]" ) );
    verifyN2NReaction( n2n );

    n3n = Np236m1.reaction( id::ReactionID( "n,Np236_e2->3n,Np234[all]" ) );
    verifyN3NReaction( n3n );

    fission = Np236m1.reaction( id::ReactionID( "n,Np236_e2->fission" ) );
    verifyFissionReaction( fission );

    n4n = Np236m1.reaction( id::ReactionID( "n,Np236_e2->4n,Np233[all]" ) );
    verifyN4NReaction( n4n );

    inelastic = Np236m1.reaction( id::ReactionID( "n,Np236_e2->n,Np236[all]" ) );
    verifyInelasticReaction( inelastic );

    inelastic0 = Np236m1.reaction( id::ReactionID( "n,Np236_e2->n,Np236" ) );
    verifyInelasticReactionLevel0( inelastic0 );

    inelastic1 = Np236m1.reaction( id::ReactionID( "n,Np236_e2->n,Np236_e1" ) );
    verifyInelasticReactionLevel1( inelastic1 );

    inelastic3 = Np236m1.reaction( id::ReactionID( "n,Np236_e2->n,Np236_e3" ) );
    verifyInelasticReactionLevel3( inelastic3 );

    inelastic4 = Np236m1.reaction( id::ReactionID( "n,Np236_e2->n,Np236_e4" ) );
    verifyInelasticReactionLevel4( inelastic4 );

    inelastic5 = Np236m1.reaction( id::ReactionID( "n,Np236_e2->n,Np236_e5" ) );
    verifyInelasticReactionLevel5( inelastic5 );

    inelastic6 = Np236m1.reaction( id::ReactionID( "n,Np236_e2->n,Np236_e6" ) );
    verifyInelasticReactionLevel6( inelastic6 );

    inelastic_cont = Np236m1.reaction( id::ReactionID( "n,Np236_e2->n,Np236[continuum]" ) );
    verifyInelasticReactionContinuum( inelastic_cont );

    capture = Np236m1.reaction( id::ReactionID( "n,Np236_e2->g,Np237[all]" ) );
    verifyCaptureReaction( capture );
  }

} // namespace h1
} // namespace neutron
