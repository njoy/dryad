namespace neutron {

// test functions based on n-001_H_001.endf
namespace h1 {

  void verifyDocumentation( const Documentation& documentation ) {

    std::string description =
      "  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                         \n"
      " NDS 148, 1 (2018)    DIST-FEB18                       20170124   \n"
      "----ENDF/B-VIII.0     MATERIAL  125                               \n"
      "-----INCIDENT NEUTRON DATA                                        \n"
      "------ENDF-6 FORMAT                                               \n"
      "                                                                  \n"
      " **************************************************************** \n"
      "The new R-matrix analysis of the N-N system on which the ENDF/B-  \n"
      "VII evaluation for 1H is based differs from the previous one use  \n"
      "for ENDF/B-VI in several respects. Firstly, the n-p capture       \n"
      "reaction (MT=102), and its inverse, deuteron photo-               \n"
      "disintegration, were a part of the analysis, rather than added    \n"
      "later as before. The analysis used a new method for including     \n"
      "photon channels in R-matrix theory [1], which gave a better       \n"
      "description of the E1 transitions, in particular.  The data for   \n"
      "these reactions are mostly integrated and differential cross      \n"
      "sections, but some information about polarizations was also       \n"
      "included.  The thermal capture cross section was taken to be      \n"
      "332.0 mb, as was the recommendation from preliminary data         \n"
      "testing. Good agreement was obtained with recent cross-section    \n"
      "measurements [2,3] by astrophysical groups in the 20-550 keV      \n"
      "range, as well as with earlier measurements that had been done    \n"
      "mostly as photo-disintegration experiments at energies below 14   \n"
      "MeV.                                                              \n"
      "The new analysis includes several additional measurements of the  \n"
      "total cross section (MT=1).  The evaluated cross section          \n"
      "deviates at most by about -0.5% around 10 MeV from that of        \n"
      "ENDF/B-VI.  The estimated uncertainty of the MT=1 cross section   \n"
      "is given at 2 MeV steps in the following table:                   \n"
      "           En             Uncert. (%)                             \n"
      "            0                0.20                                 \n"
      "            2                0.22                                 \n"
      "            4                0.30                                 \n"
      "            6                0.36                                 \n"
      "            8                0.44                                 \n"
      "           10                0.50                                 \n"
      "           12                0.49                                 \n"
      "           14                0.46                                 \n"
      "           16                0.40                                 \n"
      "           18                0.35                                 \n"
      "           20                0.30                                 \n"
      "                                                                  \n"
      "For n-p scattering (MT=2), new information was included about the \n"
      "low-energy cross sections (MF=3) and about the angular            \n"
      "distributions (MF=4).  A new measurement of the angular           \n"
      "distribution at 10 MeV [4], plus corrections to earlier data at   \n"
      "14 MeV, moved the back-angle asymmetry in the 10-14 MeV range to  \n"
      "values that lie between those obtained for ENDF/B-V and ENDF/B-   \n"
      "VI.  The addition of the latest value of the thermal coherent     \n"
      "scattering length [5] had the interesting effect of reducing the  \n"
      "\"zero-energy\" scattering cross section somewhat to agree          \n"
      "perfectly with an earlier measurement by Houk [6], and disagree   \n"
      "with the later, more precise, value of Dilg [7].  The             \n"
      "covariances for MT=2 will be added later, but the uncertainties   \n"
      "on the integrated cross section should be similar to those        \n"
      "listed above for the total cross section.                         \n"
      "                                                                  \n"
      "REFERENCES                                                        \n"
      "                                                                  \n"
      "[1] G. M. Hale and A. S. Johnson, Proc. 17th Int. IUPAP Conf. on  \n"
      "    Few-Body Problems in Physics, 5-10 June 2003, Durham NC, W.   \n"
      "    Gloeckle and W. Tornow,  eds., Elsevier B.V., pp. S120-S122   \n"
      "   (2004).                                                        \n"
      "[2] T. S. Suzuki et al., Astrophys. Lett. 449, L59 (1995).        \n"
      "[3] Y. Nagai et al., Phys. Rev. C 56, 3173 (1997).                \n"
      "[4] N. Boukharouba et al., Phys. Rev. C 65, 014004 (2002).        \n"
      "[5] K. Schoen et al., Phys. Rev. C 67, 044005 (2003).             \n"
      "[6] T. L. Houk, Phys. Rev. C 3, 1886 (1971).                      \n"
      "[7] W. Dilg, Phys. Rev. C 11, 103 (1975).                         \n"
      " **************************************************************** \n"
      "                                                                  \n"
      "Covariances were adopted from COMMARA-2.0 library in July 2011.   \n"
      "These covariances were obtained at LANL by full scale R-matrix    \n"
      "analysis of more than 5000 experimental data (chi-square/degree   \n"
      "of freedom of 0.83). [1] The major channel in this case is elastic\n"
      "scattering, often labeled also as ''n-p'' scattering. Elastic     \n"
      "scattering serves as neutron cross section standard from 1 keV to \n"
      "20 MeV, with cross sections well determined. Uncertainties for    \n"
      "elastic scattering rise from values well below 1%, reach maximum  \n"
      "at about 8 MeV, then gradually decrease with increasing energy.   \n"
      "In addition to elastic scattering, covariances are supplied for   \n"
      "radiative capture.                                                \n"
      "                                                                  \n"
      "REFERENCES                                                        \n"
      "[1] G. M. Hale, \"Covariances from light-element R-matrix          \n"
      "analyses,\" Nuclear Data Sheets, 109, 2812 (2008).                 \n"
      " **************************************************************** \n";

    CHECK( std::nullopt == documentation.awr() );
    CHECK( std::nullopt == documentation.library() );
    CHECK( std::nullopt == documentation.version() );
    CHECK( std::nullopt == documentation.description() );
  }

  void verifyTotalReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,H1->total" ) == reaction.identifier() );
    CHECK( 1 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    auto partials = reaction.partialReactionIdentifiers().value();
    CHECK( 2 == partials.size() );
    CHECK( id::ReactionID( "n,H1->n,H1" ) == partials[0] );
    CHECK( id::ReactionID( "n,H1->g,H2[all]" ) == partials[1] );
    CHECK(  50 == partials[0].reactionType().mt() );
    CHECK( 102 == partials[1].reactionType().mt() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( false == reaction.crossSection().isLinearised() );
    CHECK( 153 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 153 == reaction.crossSection().energies().size() );
    CHECK( 153 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK( 8 == reaction.crossSection().boundaries()[0] );
    CHECK( 152 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LogLog == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 5e-3, WithinRel( reaction.crossSection().energies()[8] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[152] ) );
    CHECK_THAT( 3.716477e+1, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 2.118421e+1, WithinRel( reaction.crossSection().values()[8] ) );
    CHECK_THAT( 4.818679e-1, WithinRel( reaction.crossSection().values()[152] ) );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyElasticReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,H1->n,H1" ) == reaction.identifier() );
    CHECK( 50 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 0, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( true == reaction.crossSection().isLinearised() );
    CHECK( 153 == reaction.crossSection().numberPoints() );
    CHECK( 1 == reaction.crossSection().numberRegions() );
    CHECK( 153 == reaction.crossSection().energies().size() );
    CHECK( 153 == reaction.crossSection().values().size() );
    CHECK( 1 == reaction.crossSection().boundaries().size() );
    CHECK( 1 == reaction.crossSection().interpolants().size() );
    CHECK( 152 == reaction.crossSection().boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[0] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[152] ) );
    CHECK_THAT( 2.043608e+1, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 4.818408e-1, WithinRel( reaction.crossSection().values()[152] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "H1" ) ) );

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
    CHECK( 153 == angle.numberPoints() );
    CHECK( 1 == angle.numberRegions() );
    CHECK( 153 == angle.grid().size() );
    CHECK( 153 == angle.distributions().size() );
    CHECK( 1 == angle.boundaries().size() );
    CHECK( 1 == angle.interpolants().size() );
    CHECK_THAT( 1e-5   , WithinRel( angle.grid()[0] ) );
    CHECK_THAT( 2e-5   , WithinRel( angle.grid()[1] ) );
    CHECK_THAT( 1.95e+7, WithinRel( angle.grid()[151] ) );
    CHECK_THAT( 2e+7   , WithinRel( angle.grid()[152] ) );
    CHECK( 7 == angle.distributions()[0].pdf().coefficients().size() );
    CHECK( 7 == angle.distributions()[1].pdf().coefficients().size() );
    CHECK( 7 == angle.distributions()[151].pdf().coefficients().size() );
    CHECK( 7 == angle.distributions()[152].pdf().coefficients().size() );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].pdf().coefficients()[0] ) );
    CHECK_THAT( -1.7511000E-14  , WithinRel( angle.distributions()[0].pdf().coefficients()[1] ) );
    CHECK_THAT( -2.5280750E-16  , WithinRel( angle.distributions()[0].pdf().coefficients()[2] ) );
    CHECK_THAT( -6.4002050E-17  , WithinRel( angle.distributions()[0].pdf().coefficients()[3] ) );
    CHECK_THAT(  1.3653765E-16  , WithinRel( angle.distributions()[0].pdf().coefficients()[4] ) );
    CHECK_THAT( -1.7067215E-17  , WithinRel( angle.distributions()[0].pdf().coefficients()[5] ) );
    CHECK_THAT(  2.5600835E-17  , WithinRel( angle.distributions()[0].pdf().coefficients()[6] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[1].pdf().coefficients()[0] ) );
    CHECK_THAT( -3.4846950E-14  , WithinRel( angle.distributions()[1].pdf().coefficients()[1] ) );
    CHECK_THAT( -1.7387225E-16  , WithinRel( angle.distributions()[1].pdf().coefficients()[2] ) );
    CHECK_THAT( -9.1736400E-17  , WithinRel( angle.distributions()[1].pdf().coefficients()[3] ) );
    CHECK_THAT( -2.9867625E-17  , WithinRel( angle.distributions()[1].pdf().coefficients()[4] ) );
    CHECK_THAT( -3.4134430E-17  , WithinRel( angle.distributions()[1].pdf().coefficients()[5] ) );
    CHECK_THAT(  1.8773950E-16  , WithinRel( angle.distributions()[1].pdf().coefficients()[6] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[151].pdf().coefficients()[0] ) );
    CHECK_THAT( -2.4240045E-02  , WithinRel( angle.distributions()[151].pdf().coefficients()[1] ) );
    CHECK_THAT(  1.7942750E-02  , WithinRel( angle.distributions()[151].pdf().coefficients()[2] ) );
    CHECK_THAT( -2.54685165E-03 , WithinRel( angle.distributions()[151].pdf().coefficients()[3] ) );
    CHECK_THAT(  1.54781595E-03 , WithinRel( angle.distributions()[151].pdf().coefficients()[4] ) );
    CHECK_THAT(  4.91773975E-05 , WithinRel( angle.distributions()[151].pdf().coefficients()[5] ) );
    CHECK_THAT(  3.82748535E-05 , WithinRel( angle.distributions()[151].pdf().coefficients()[6] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[152].pdf().coefficients()[0] ) );
    CHECK_THAT( -2.41945200E-02 , WithinRel( angle.distributions()[152].pdf().coefficients()[1] ) );
    CHECK_THAT(  1.95173075E-02 , WithinRel( angle.distributions()[152].pdf().coefficients()[2] ) );
    CHECK_THAT( -2.71943700E-03 , WithinRel( angle.distributions()[152].pdf().coefficients()[3] ) );
    CHECK_THAT(  1.69449750E-03 , WithinRel( angle.distributions()[152].pdf().coefficients()[4] ) );
    CHECK_THAT(  5.25219970E-05 , WithinRel( angle.distributions()[152].pdf().coefficients()[5] ) );
    CHECK_THAT(  4.48370065E-05 , WithinRel( angle.distributions()[152].pdf().coefficients()[6] ) );
    CHECK( 8 == angle.distributions()[0].cdf().coefficients().size() );
    CHECK( 8 == angle.distributions()[1].cdf().coefficients().size() );
    CHECK( 8 == angle.distributions()[151].cdf().coefficients().size() );
    CHECK( 8 == angle.distributions()[152].cdf().coefficients().size() );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[0].cdf().coefficients()[1] ) );
    CHECK_THAT( -5.82785685e-15 , WithinRel( angle.distributions()[0].cdf().coefficients()[2] ) );
    CHECK_THAT( -6.57323500e-17 , WithinRel( angle.distributions()[0].cdf().coefficients()[3] ) );
    CHECK_THAT( -7.59158500e-18 , WithinRel( angle.distributions()[0].cdf().coefficients()[4] ) );
    CHECK_THAT(  1.32015550e-17 , WithinRel( angle.distributions()[0].cdf().coefficients()[5] ) );
    CHECK_THAT( -1.55156500e-18 , WithinRel( angle.distributions()[0].cdf().coefficients()[6] ) );
    CHECK_THAT(  1.96929500e-18 , WithinRel( angle.distributions()[0].cdf().coefficients()[7] ) );
    CHECK_THAT( 0.50000000000001, WithinRel( angle.distributions()[1].cdf().coefficients()[0] ) );
    CHECK_THAT( 0.5             , WithinRel( angle.distributions()[1].cdf().coefficients()[1] ) );
    CHECK_THAT( -1.16025448e-14 , WithinRel( angle.distributions()[1].cdf().coefficients()[2] ) );
    CHECK_THAT( -3.14558250e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[3] ) );
    CHECK_THAT( -1.00020700e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[4] ) );
    CHECK_THAT( -1.77601250e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[5] ) );
    CHECK_THAT( -3.10313000e-18 , WithinRel( angle.distributions()[1].cdf().coefficients()[6] ) );
    CHECK_THAT(  1.44415000e-17 , WithinRel( angle.distributions()[1].cdf().coefficients()[7] ) );
    CHECK_THAT(  5.08080015e-01 , WithinRel( angle.distributions()[151].cdf().coefficients()[0] ) );
    CHECK_THAT(  4.96411450e-01 , WithinRel( angle.distributions()[151].cdf().coefficients()[1] ) );
    CHECK_THAT( -7.71617905e-03 , WithinRel( angle.distributions()[151].cdf().coefficients()[2] ) );
    CHECK_THAT(  3.41657045e-03 , WithinRel( angle.distributions()[151].cdf().coefficients()[3] ) );
    CHECK_THAT( -3.683066225e-04, WithinRel( angle.distributions()[151].cdf().coefficients()[4] ) );
    CHECK_THAT(  1.690353305e-04, WithinRel( angle.distributions()[151].cdf().coefficients()[5] ) );
    CHECK_THAT(  4.47067250e-06 , WithinRel( angle.distributions()[151].cdf().coefficients()[6] ) );
    CHECK_THAT(  2.94421950e-06 , WithinRel( angle.distributions()[151].cdf().coefficients()[7] ) );
    CHECK_THAT(  5.08064840e-01 , WithinRel( angle.distributions()[152].cdf().coefficients()[0] ) );
    CHECK_THAT(  4.960965385e-01, WithinRel( angle.distributions()[152].cdf().coefficients()[1] ) );
    CHECK_THAT( -7.67634900e-03 , WithinRel( angle.distributions()[152].cdf().coefficients()[2] ) );
    CHECK_THAT(  3.71518400e-03 , WithinRel( angle.distributions()[152].cdf().coefficients()[3] ) );
    CHECK_THAT( -3.93265727e-04 , WithinRel( angle.distributions()[152].cdf().coefficients()[4] ) );
    CHECK_THAT(  1.848284995e-04, WithinRel( angle.distributions()[152].cdf().coefficients()[5] ) );
    CHECK_THAT(  4.77472700e-06 , WithinRel( angle.distributions()[152].cdf().coefficients()[6] ) );
    CHECK_THAT(  3.44900050e-06 , WithinRel( angle.distributions()[152].cdf().coefficients()[7] ) );
    CHECK( 152 == angle.boundaries()[0] );
    CHECK( InterpolationType::LinearLinear == angle.interpolants()[0] );

    auto h1 = reaction.product( id::ParticleID( "H1" ) );
    CHECK( id::ParticleID( "H1" ) == h1.identifier() );
  }

  void verifyCaptureReaction( const Reaction& reaction ) {

    CHECK( id::ReactionID( "n,H1->g,H2[all]" ) == reaction.identifier() );
    CHECK( 102 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt != reaction.reactionQValue() );
    CHECK_THAT( 2.224648e+6, WithinRel( reaction.reactionQValue().value() ) );

    CHECK( false == reaction.crossSection().isLinearised() );
    CHECK( 153 == reaction.crossSection().numberPoints() );
    CHECK( 2 == reaction.crossSection().numberRegions() );
    CHECK( 153 == reaction.crossSection().energies().size() );
    CHECK( 153 == reaction.crossSection().values().size() );
    CHECK( 2 == reaction.crossSection().boundaries().size() );
    CHECK( 2 == reaction.crossSection().interpolants().size() );
    CHECK( 32 == reaction.crossSection().boundaries()[0] );
    CHECK( 152 == reaction.crossSection().boundaries()[1] );
    CHECK( InterpolationType::LogLog == reaction.crossSection().interpolants()[0] );
    CHECK( InterpolationType::LinearLinear == reaction.crossSection().interpolants()[1] );
    CHECK_THAT( 1e-5, WithinRel( reaction.crossSection().energies()[0] ) );
    CHECK_THAT( 1e+4, WithinRel( reaction.crossSection().energies()[32] ) );
    CHECK_THAT( 2e+7, WithinRel( reaction.crossSection().energies()[152] ) );
    CHECK_THAT( 1.672869e+1, WithinRel( reaction.crossSection().values()[0] ) );
    CHECK_THAT( 4.950573e-4, WithinRel( reaction.crossSection().values()[32] ) );
    CHECK_THAT( 2.710792e-5, WithinRel( reaction.crossSection().values()[152] ) );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "g" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "H2" ) ) );

    auto gamma = reaction.product( id::ParticleID( "g" ) );
    CHECK( id::ParticleID( "g" ) == gamma.identifier() );

    auto deuterium = reaction.product( id::ParticleID( "H2" ) );
    CHECK( id::ParticleID( "H2" ) == deuterium.identifier() );
  }

  void verifyH1( const ProjectileTarget& H1, bool normalise ) {

    verifyDocumentation( H1.documentation() );

    CHECK( id::ParticleID( "n" ) == H1.projectileIdentifier() );
    CHECK( id::ParticleID( "H1" ) == H1.targetIdentifier() );

    CHECK( InteractionType::Nuclear == H1.interactionType() );

    CHECK( std::nullopt == H1.resonances() );

    CHECK( true == H1.hasReaction( id::ReactionID( "n,H1->total" ) ) );
    CHECK( true == H1.hasReaction( id::ReactionID( "n,H1->n,H1" ) ) );
    CHECK( true == H1.hasReaction( id::ReactionID( "n,H1->g,H2[all]" ) ) );
//    CHECK( false == H1.hasReaction( id::ReactionID( "some unknown reaction" ) ) );

    CHECK( 3 == H1.reactions().size() );

    auto total = H1.reactions()[0];
    verifyTotalReaction( total );

    auto elastic = H1.reactions()[1];
    verifyElasticReaction( elastic );

    auto capture = H1.reactions()[2];
    verifyCaptureReaction( capture );

    total = H1.reaction( id::ReactionID( "n,H1->total" ) );
    verifyTotalReaction( total );

    elastic = H1.reaction( id::ReactionID( "n,H1->n,H1" ) );
    verifyElasticReaction( elastic );

    capture = H1.reaction( id::ReactionID( "n,H1->g,H2[all]" ) );
    verifyCaptureReaction( capture );
  }

} // namespace h1
} // namespace neutron
