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

    CHECK( 234.0190 == documentation.awr() );
    CHECK( 0 == documentation.library() );
    CHECK( std::make_pair( 8, 1 ) == documentation.version() );
    CHECK( description == documentation.description() );
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

    CHECK( std::nullopt != reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 0, WithinRel( reaction.massDifferenceQValue().value() ) );
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

  void verifyCaptureReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,Np236_e2->g,Np237[all]" ) == reaction.identifier() );
    CHECK( 102 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 6637350, WithinRel( reaction.massDifferenceQValue().value() ) );
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
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->n,Np236[all]" ) ) );
    CHECK( true == Np236m1.hasReaction( id::ReactionID( "n,Np236_e2->g,Np237[all]" ) ) );
//    CHECK( false == Np236m1.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

    CHECK( 15 == Np236m1.reactions().size() );

    auto total = Np236m1.reactions()[0];
    verifyTotalReaction( total );

    auto elastic = Np236m1.reactions()[1];
    verifyElasticReaction( elastic );

    auto inelastic = Np236m1.reactions()[2];
    verifyInelasticReaction( inelastic );

    auto capture = Np236m1.reactions()[14];
    verifyCaptureReaction( capture );

    total = Np236m1.reaction( id::ReactionID( "n,Np236_e2->total" ) );
    verifyTotalReaction( total );

    elastic = Np236m1.reaction( id::ReactionID( "n,Np236_e2->n,Np236_e2" ) );
    verifyElasticReaction( elastic );

    inelastic = Np236m1.reaction( id::ReactionID( "n,Np236_e2->n,Np236[all]" ) );
    verifyInelasticReaction( inelastic );

    capture = Np236m1.reaction( id::ReactionID( "n,Np236_e2->g,Np237[all]" ) );
    verifyCaptureReaction( capture );
  }

} // namespace h1
} // namespace neutron
