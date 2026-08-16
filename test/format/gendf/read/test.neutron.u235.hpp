namespace neutron {

// test functions based on n-092_U_235.gendf and n-092_U_235.covariances.gendf
namespace u235 {

  static const std::vector< double > boundaries = {

    1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000e+0, 3.060000e+0,
    8.320000e+0, 2.260000e+1, 6.140000e+1, 1.670000e+2, 4.540000e+2,
    1.235000e+3, 3.350000e+3, 9.120000e+3, 2.480000e+4, 6.760000e+4,
    1.840000e+5, 3.030000e+5, 5.000000e+5, 8.230000e+5, 1.353000e+6,
    1.738000e+6, 2.232000e+6, 2.865000e+6, 3.680000e+6, 6.070000e+6,
    7.790000e+6, 1.000000e+7, 1.200000e+7, 1.350000e+7, 1.500000e+7,
    1.700000e+7
  };

  // compare two vectors of identifiers
  void checkPartials( const std::vector< id::ReactionID >& expected,
                      const std::vector< id::ReactionID >& values ) {

    CHECK( expected.size() == values.size() );
    for ( std::size_t i = 0; i < expected.size(); ++i ) {

      CHECK( values[i] == expected[i] );
    }
  }

  // compare two vectors of values
  void checkGroups( const std::vector< double >& expected,
                     const std::vector< double >& values ) {

    CHECK( expected.size() == values.size() );
    for ( std::size_t i = 0; i < expected.size(); ++i ) {

      CHECK_THAT( values[i], WithinRel( expected[i] ) );
    }
  }

  // compare boundaries
  void checkBoundaries( const std::vector< double >& values ) {

    checkGroups( boundaries, values );
  }

  void verifyTotalReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      536.7046, 220.2761, 95.71743, 38.79649, 55.25322, 112.356, 84.29812,
      47.16981, 35.49166, 26.59377, 20.29375, 17.12288, 14.96041, 13.39889,
      11.76493, 10.30321, 8.994543, 7.724532, 6.866099, 6.841653, 7.226625,
      7.693402, 7.979821, 7.647424, 6.661945, 6.031144, 5.747069, 5.746542,
      5.827871, 6.020082
    };
    static const std::vector< id::ReactionID > partials = {

      id::ReactionID( "n,U235->n(0)" ), id::ReactionID( "n,U235->anything" ),
      id::ReactionID( "n,U235->2n(t)" ), id::ReactionID( "n,U235->3n(t)" ),
      id::ReactionID( "n,U235->fission" ), id::ReactionID( "n,U235->n(1)" ),
      id::ReactionID( "n,U235->n(2)" ), id::ReactionID( "n,U235->n(3)" ),
      id::ReactionID( "n,U235->n(4)" ), id::ReactionID( "n,U235->n(5)" ),
      id::ReactionID( "n,U235->n(6)" ), id::ReactionID( "n,U235->n(7)" ),
      id::ReactionID( "n,U235->n(8)" ), id::ReactionID( "n,U235->n(9)" ),
      id::ReactionID( "n,U235->n(10)" ), id::ReactionID( "n,U235->n(11)" ),
      id::ReactionID( "n,U235->n(12)" ), id::ReactionID( "n,U235->n(13)" ),
      id::ReactionID( "n,U235->n(14)" ), id::ReactionID( "n,U235->n(15)" ),
      id::ReactionID( "n,U235->n(16)" ), id::ReactionID( "n,U235->n(17)" ),
      id::ReactionID( "n,U235->n(18)" ), id::ReactionID( "n,U235->n(19)" ),
      id::ReactionID( "n,U235->n(20)" ), id::ReactionID( "n,U235->n(21)" ),
      id::ReactionID( "n,U235->n(22)" ), id::ReactionID( "n,U235->n(23)" ),
      id::ReactionID( "n,U235->n(24)" ), id::ReactionID( "n,U235->n(25)" ),
      id::ReactionID( "n,U235->n(26)" ), id::ReactionID( "n,U235->n(27)" ),
      id::ReactionID( "n,U235->n(28)" ), id::ReactionID( "n,U235->n(29)" ),
      id::ReactionID( "n,U235->n(30)" ), id::ReactionID( "n,U235->n(31)" ),
      id::ReactionID( "n,U235->n(32)" ), id::ReactionID( "n,U235->n(33)" ),
      id::ReactionID( "n,U235->n(34)" ), id::ReactionID( "n,U235->n(35)" ),
      id::ReactionID( "n,U235->n(36)" ), id::ReactionID( "n,U235->n(37)" ),
      id::ReactionID( "n,U235->n(38)" ), id::ReactionID( "n,U235->n(39)" ),
      id::ReactionID( "n,U235->n(c)" ), id::ReactionID( "n,U235->g(t)" ),
      id::ReactionID( "n,U235->p(0)" ), id::ReactionID( "n,U235->p(1)" ),
      id::ReactionID( "n,U235->p(2)" ), id::ReactionID( "n,U235->p(3)" ),
      id::ReactionID( "n,U235->p(4)" ), id::ReactionID( "n,U235->p(5)" ),
      id::ReactionID( "n,U235->p(6)" ), id::ReactionID( "n,U235->p(7)" ),
      id::ReactionID( "n,U235->p(8)" ), id::ReactionID( "n,U235->p(9)" ),
      id::ReactionID( "n,U235->p(c)" ), id::ReactionID( "n,U235->a(0)" ),
      id::ReactionID( "n,U235->a(1)" ), id::ReactionID( "n,U235->a(2)" ),
      id::ReactionID( "n,U235->a(3)" ), id::ReactionID( "n,U235->a(4)" ),
      id::ReactionID( "n,U235->a(5)" ), id::ReactionID( "n,U235->a(6)" ),
      id::ReactionID( "n,U235->a(7)" ), id::ReactionID( "n,U235->a(8)" ),
      id::ReactionID( "n,U235->a(9)" ), id::ReactionID( "n,U235->a(10)" ),
      id::ReactionID( "n,U235->a(11)" ), id::ReactionID( "n,U235->a(12)" ),
      id::ReactionID( "n,U235->a(13)" ), id::ReactionID( "n,U235->a(14)" ),
      id::ReactionID( "n,U235->a(15)" ), id::ReactionID( "n,U235->a(16)" ),
      id::ReactionID( "n,U235->a(17)" ), id::ReactionID( "n,U235->a(18)" ),
      id::ReactionID( "n,U235->a(19)" ), id::ReactionID( "n,U235->a(20)" ),
      id::ReactionID( "n,U235->a(21)" ), id::ReactionID( "n,U235->a(22)" ),
      id::ReactionID( "n,U235->a(23)" ), id::ReactionID( "n,U235->a(24)" ),
      id::ReactionID( "n,U235->a(25)" ), id::ReactionID( "n,U235->a(26)" ),
      id::ReactionID( "n,U235->a(27)" ), id::ReactionID( "n,U235->a(28)" ),
      id::ReactionID( "n,U235->a(29)" ), id::ReactionID( "n,U235->a(30)" ),
      id::ReactionID( "n,U235->a(31)" ), id::ReactionID( "n,U235->a(32)" ),
      id::ReactionID( "n,U235->a(33)" ), id::ReactionID( "n,U235->a(34)" ),
      id::ReactionID( "n,U235->a(35)" )
    };

    CHECK( id::ReactionID( "n,U235->total" ) == reaction.identifier() );
    CHECK( 1 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    checkPartials( partials, reaction.partialReactionIdentifiers().value() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyElasticReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      13.93506, 13.49537, 12.91475, 12.1238, 10.88551, 11.91146, 11.60821,
      11.3331, 11.61043, 11.96796, 12.32671, 12.03487, 11.57104, 10.85064,
      9.402231, 7.765998, 6.275956, 4.83385, 3.806535, 3.573489, 3.780874,
      4.176016, 4.50378, 4.315437, 3.541666, 2.917763, 2.641818, 2.681111,
      2.81791, 2.995613
    };
    static const std::vector< double > mu = {

      0.002934899, 0.0029349, 0.002934966, 0.002935169, 0.002935712,
      0.00293724, 0.002941352, 0.002993257, 0.003220448, 0.003870717,
      0.00568632, 0.0108574, 0.02542495, 0.06409677, 0.1522569, 0.2536881,
      0.3455274, 0.4358658, 0.5052062, 0.5550757, 0.6216212, 0.7075352,
      0.7821745, 0.8442532, 0.8548909, 0.8476798, 0.8598718, 0.8832812,
      0.9042772, 0.9240258
    };

    CHECK( id::ReactionID( "n,U235->n,U235" ) == reaction.identifier() );
    CHECK( 50 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 2 == reaction.numberProducts() );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "n" ) ) );
    CHECK( 1 == reaction.numberProducts( id::ParticleID( "U235" ) ) );

    CHECK( 2 == reaction.numberProducts() );

    const auto& neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.productIdentifier() );
    CHECK( 0 == neutron.chainIndex() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    CHECK( 1 == std::get< int >( neutron.multiplicity() ) );

    const auto& residual = reaction.product( id::ParticleID( "U235" ) );
    CHECK( id::ParticleID( "U235" ) == residual.productIdentifier() );
    CHECK( true == std::holds_alternative< int >( residual.multiplicity() ) );
    CHECK( 1 == std::get< int >( residual.multiplicity() ) );
    CHECK( false == residual.hasAverageCosine() );

    CHECK( true == neutron.hasAverageCosine() );
    CHECK( std::nullopt != neutron.averageCosine() );

    CHECK( 30 == neutron.averageCosine()->numberGroups() );
    checkBoundaries( neutron.averageCosine()->boundaries() );
    checkGroups( mu, neutron.averageCosine()->values() );
  }

  void verifyInelasticReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      0, 0, 0, 0, 0, 0, 0, 2.858604e-08, 1.369093e-07, 4.235682e-07,
      1.534526e-06, 7.486603e-06, 0.002773635, 0.04480505, 0.4478261,
      0.9790408, 1.348968, 1.632857, 1.768018, 1.941328, 2.103842, 2.22012,
      2.25993, 2.210047, 1.240204, 0.6642126, 0.5140451, 0.41111, 0.3428301,
      0.3353763
    };
    static const std::vector< id::ReactionID > partials = {

      id::ReactionID( "n,U235->n(1)" ),
      id::ReactionID( "n,U235->n(2)" ), id::ReactionID( "n,U235->n(3)" ),
      id::ReactionID( "n,U235->n(4)" ), id::ReactionID( "n,U235->n(5)" ),
      id::ReactionID( "n,U235->n(6)" ), id::ReactionID( "n,U235->n(7)" ),
      id::ReactionID( "n,U235->n(8)" ), id::ReactionID( "n,U235->n(9)" ),
      id::ReactionID( "n,U235->n(10)" ), id::ReactionID( "n,U235->n(11)" ),
      id::ReactionID( "n,U235->n(12)" ), id::ReactionID( "n,U235->n(13)" ),
      id::ReactionID( "n,U235->n(14)" ), id::ReactionID( "n,U235->n(15)" ),
      id::ReactionID( "n,U235->n(16)" ), id::ReactionID( "n,U235->n(17)" ),
      id::ReactionID( "n,U235->n(18)" ), id::ReactionID( "n,U235->n(19)" ),
      id::ReactionID( "n,U235->n(20)" ), id::ReactionID( "n,U235->n(21)" ),
      id::ReactionID( "n,U235->n(22)" ), id::ReactionID( "n,U235->n(23)" ),
      id::ReactionID( "n,U235->n(24)" ), id::ReactionID( "n,U235->n(25)" ),
      id::ReactionID( "n,U235->n(26)" ), id::ReactionID( "n,U235->n(27)" ),
      id::ReactionID( "n,U235->n(28)" ), id::ReactionID( "n,U235->n(29)" ),
      id::ReactionID( "n,U235->n(30)" ), id::ReactionID( "n,U235->n(31)" ),
      id::ReactionID( "n,U235->n(32)" ), id::ReactionID( "n,U235->n(33)" ),
      id::ReactionID( "n,U235->n(34)" ), id::ReactionID( "n,U235->n(35)" ),
      id::ReactionID( "n,U235->n(36)" ), id::ReactionID( "n,U235->n(37)" ),
      id::ReactionID( "n,U235->n(38)" ), id::ReactionID( "n,U235->n(39)" ),
      id::ReactionID( "n,U235->n(c)" )
    };

    CHECK( id::ReactionID( "n,U235->n,U235[all]" ) == reaction.identifier() );
    CHECK( 4 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    checkPartials( partials, reaction.partialReactionIdentifiers().value() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyAnythingReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      0.000181785, 7.065633e-05, 4.27852e-05, 2.596018e-05, 1.575565e-05,
      9.557948e-06, 5.798942e-06, 3.642172e-06, 2.172062e-06, 1.27667e-06,
      7.511973e-07, 4.606619e-07, 3.294004e-07, 2.711888e-07, 1.7627e-07,
      1.15338e-07, 9.354424e-08, 9.729689e-08, 9.864676e-08, 1.273916e-07,
      1.98534e-07, 3.371773e-07, 5.58589e-07, 1.155836e-06, 2.975712e-05,
      0.001667221, 0.007625441, 0.01362114, 0.01561902, 0.01826954
    };

    CHECK( id::ReactionID( "n,U235->anything" ) == reaction.identifier() );
    CHECK( 5 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyN2NReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0.02268994, 0.3911464, 0.6683329, 0.8498895, 0.7897065, 0.5222739,
      0.3591681
    };

    CHECK( id::ReactionID( "n,U235->2n,U234[all]" ) == reaction.identifier() );
    CHECK( 16 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 2 == reaction.numberProducts() );

    const auto& neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.productIdentifier() );
    CHECK( 0 == neutron.chainIndex() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    CHECK( 2 == std::get< int >( neutron.multiplicity() ) );

    const auto& residual = reaction.product( id::ParticleID( "U234[all]" ) );
    CHECK( id::ParticleID( "U234[all]" ) == residual.productIdentifier() );
    CHECK( true == std::holds_alternative< int >( residual.multiplicity() ) );
    CHECK( 1 == std::get< int >( residual.multiplicity() ) );
    CHECK( false == residual.hasAverageCosine() );
  }

  void verifyN3NReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0.00207962, 0.05275775, 0.1743108
    };

    CHECK( id::ReactionID( "n,U235->3n,U233[all]" ) == reaction.identifier() );
    CHECK( 17 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 2 == reaction.numberProducts() );

    const auto& neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.productIdentifier() );
    CHECK( 0 == neutron.chainIndex() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    CHECK( 3 == std::get< int >( neutron.multiplicity() ) );

    const auto& residual = reaction.product( id::ParticleID( "U233[all]" ) );
    CHECK( id::ParticleID( "U233[all]" ) == residual.productIdentifier() );
    CHECK( true == std::holds_alternative< int >( residual.multiplicity() ) );
    CHECK( 1 == std::get< int >( residual.multiplicity() ) );
    CHECK( false == residual.hasAverageCosine() );
  }

  void verifyFissionReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      445.8921, 170.7274, 71.28727, 18.60638, 19.59203, 59.40528, 47.37674,
      22.53216, 16.72795, 10.23652, 5.792585, 3.681852, 2.484802, 1.894573,
      1.509857, 1.292385, 1.193227, 1.12288, 1.189525, 1.246405, 1.280639,
      1.257589, 1.193774, 1.092166, 1.486495, 1.777089, 1.731687, 1.847183,
      2.0745, 2.13315
    };

    CHECK( id::ReactionID( "n,U235->fission(t)" ) == reaction.identifier() );
    CHECK( 18 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyFirstInelasticReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      0, 0, 0, 0, 0, 0, 0, 2.858604e-08, 1.369093e-07, 4.235682e-07,
      1.534526e-06, 7.486603e-06, 5.977564e-05, 0.0006885752, 0.00436461,
      0.01027762, 0.0164764, 0.01948597, 0.01342329, 0.005938933,
      0.002357908, 0.0006926999, 0.0001575986, 1.243853e-05, 1.57598e-07,
      6.07301e-09, 2.17906e-10, 1.54243e-11, 2.3371e-12, 2.82368e-13
    };

    CHECK( id::ReactionID( "n,U235->n(1)" ) == reaction.identifier() );
    CHECK( 51 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 2 == reaction.numberProducts() );

    const auto& neutron = reaction.product( id::ParticleID( "n" ) );
    CHECK( id::ParticleID( "n" ) == neutron.productIdentifier() );
    CHECK( 0 == neutron.chainIndex() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    CHECK( 1 == std::get< int >( neutron.multiplicity() ) );

    const auto& residual = reaction.product( id::ParticleID( "U235_e1" ) );
    CHECK( id::ParticleID( "U235_e1" ) == residual.productIdentifier() );
    CHECK( true == std::holds_alternative< int >( residual.multiplicity() ) );
    CHECK( 1 == std::get< int >( residual.multiplicity() ) );
    CHECK( false == residual.hasAverageCosine() );
  }

  void verifyCaptureReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      76.87701, 36.05318, 11.51531, 8.066256, 24.77564, 41.0392, 25.31315,
      13.30455, 7.15328, 4.389288, 2.174457, 1.406147, 0.901787, 0.6088796,
      0.4050187, 0.2657828, 0.1763918, 0.1349453, 0.102021, 0.08043076,
      0.06126882, 0.03967621, 0.02233695, 0.007082919, 0.002403593,
      0.002075671, 0.00194236, 0.001397452, 0.0009108511, 0.0007355848
    };

    CHECK( id::ReactionID( "n,U235->g(t)" ) == reaction.identifier() );
    CHECK( 102 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( true == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 2 == reaction.numberProducts() );

    const auto& neutron = reaction.product( id::ParticleID( "g" ) );
    CHECK( id::ParticleID( "g" ) == neutron.productIdentifier() );
    CHECK( 0 == neutron.chainIndex() );
    CHECK( true == std::holds_alternative< int >( neutron.multiplicity() ) );
    CHECK( 1 == std::get< int >( neutron.multiplicity() ) );

    const auto& residual = reaction.product( id::ParticleID( "U236[all]" ) );
    CHECK( id::ParticleID( "U236[all]" ) == residual.productIdentifier() );
    CHECK( true == std::holds_alternative< int >( residual.multiplicity() ) );
    CHECK( 1 == std::get< int >( residual.multiplicity() ) );
    CHECK( false == residual.hasAverageCosine() );
  }

  void verifyProtonReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      5.67397e-18, 2.97221e-14, 7.71293e-11, 1.583832e-08, 2.67375e-06,
      6.047389e-05, 0.0003330362, 0.001068946, 0.003459174
    };
    static const std::vector< id::ReactionID > partials = {

      id::ReactionID( "n,U235->p(0)" ), id::ReactionID( "n,U235->p(1)" ),
      id::ReactionID( "n,U235->p(2)" ), id::ReactionID( "n,U235->p(3)" ),
      id::ReactionID( "n,U235->p(4)" ), id::ReactionID( "n,U235->p(5)" ),
      id::ReactionID( "n,U235->p(6)" ), id::ReactionID( "n,U235->p(7)" ),
      id::ReactionID( "n,U235->p(8)" ), id::ReactionID( "n,U235->p(9)" ),
      id::ReactionID( "n,U235->p(c)" )
    };

    CHECK( id::ReactionID( "n,U235->p,Pa235[all]" ) == reaction.identifier() );
    CHECK( 103 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    checkPartials( partials, reaction.partialReactionIdentifiers().value() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyAlphaReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      0.0002256184, 8.769351e-05, 5.31019e-05, 3.221989e-05, 1.955477e-05,
      1.186263e-05, 7.197228e-06, 4.352318e-06, 2.572433e-06, 1.526149e-06,
      8.858165e-07, 5.371698e-07, 3.797739e-07, 3.066018e-07, 2.052391e-07,
      1.389072e-07, 1.136692e-07, 1.115096e-07, 9.250064e-08, 7.883878e-08,
      7.359324e-08, 6.647335e-08, 5.581399e-08, 3.316757e-08, 1.353869e-08,
      5.912407e-09, 2.081477e-09, 5.4174e-10, 1.30071e-10, 1.98905e-11
    };
    static const std::vector< id::ReactionID > partials = {

      id::ReactionID( "n,U235->a(0)" ),
      id::ReactionID( "n,U235->a(1)" ), id::ReactionID( "n,U235->a(2)" ),
      id::ReactionID( "n,U235->a(3)" ), id::ReactionID( "n,U235->a(4)" ),
      id::ReactionID( "n,U235->a(5)" ), id::ReactionID( "n,U235->a(6)" ),
      id::ReactionID( "n,U235->a(7)" ), id::ReactionID( "n,U235->a(8)" ),
      id::ReactionID( "n,U235->a(9)" ), id::ReactionID( "n,U235->a(10)" ),
      id::ReactionID( "n,U235->a(11)" ), id::ReactionID( "n,U235->a(12)" ),
      id::ReactionID( "n,U235->a(13)" ), id::ReactionID( "n,U235->a(14)" ),
      id::ReactionID( "n,U235->a(15)" ), id::ReactionID( "n,U235->a(16)" ),
      id::ReactionID( "n,U235->a(17)" ), id::ReactionID( "n,U235->a(18)" ),
      id::ReactionID( "n,U235->a(19)" ), id::ReactionID( "n,U235->a(20)" ),
      id::ReactionID( "n,U235->a(21)" ), id::ReactionID( "n,U235->a(22)" ),
      id::ReactionID( "n,U235->a(23)" ), id::ReactionID( "n,U235->a(24)" ),
      id::ReactionID( "n,U235->a(25)" ), id::ReactionID( "n,U235->a(26)" ),
      id::ReactionID( "n,U235->a(27)" ), id::ReactionID( "n,U235->a(28)" ),
      id::ReactionID( "n,U235->a(29)" ), id::ReactionID( "n,U235->a(30)" ),
      id::ReactionID( "n,U235->a(31)" ), id::ReactionID( "n,U235->a(32)" ),
      id::ReactionID( "n,U235->a(33)" ), id::ReactionID( "n,U235->a(34)" ),
      id::ReactionID( "n,U235->a(35)" )
    };

    CHECK( id::ReactionID( "n,U235->a(t)" ) == reaction.identifier() );
    CHECK( 107 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    checkPartials( partials, reaction.partialReactionIdentifiers().value() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyLumped1Reaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      0., 0., 0., 0., 0., 0., 0.,
      0., 0., 0., 0., 0., 2.713859e-3, 4.411648e-2,
      0.44346154, 0.96876308, 1.33249177, 1.61337072, 1.75459441, 1.93538854, 2.10148415,
      2.21942734, 2.25977244, 2.21003447, 1.24020290, 0.66421263, 0.51404512, 0.41110993,
      3.428301e-1, 0.33537626
    };
    static const std::vector< id::ReactionID > partials = {

      id::ReactionID( "n,U235->n(2)" ), id::ReactionID( "n,U235->n(3)" ),
      id::ReactionID( "n,U235->n(4)" ), id::ReactionID( "n,U235->n(5)" ),
      id::ReactionID( "n,U235->n(6)" ), id::ReactionID( "n,U235->n(7)" ),
      id::ReactionID( "n,U235->n(8)" ), id::ReactionID( "n,U235->n(9)" ),
      id::ReactionID( "n,U235->n(10)" ), id::ReactionID( "n,U235->n(11)" ),
      id::ReactionID( "n,U235->n(12)" ), id::ReactionID( "n,U235->n(13)" ),
      id::ReactionID( "n,U235->n(14)" ), id::ReactionID( "n,U235->n(15)" ),
      id::ReactionID( "n,U235->n(16)" ), id::ReactionID( "n,U235->n(17)" ),
      id::ReactionID( "n,U235->n(18)" ), id::ReactionID( "n,U235->n(19)" ),
      id::ReactionID( "n,U235->n(20)" ), id::ReactionID( "n,U235->n(21)" ),
      id::ReactionID( "n,U235->n(22)" ), id::ReactionID( "n,U235->n(23)" ),
      id::ReactionID( "n,U235->n(24)" ), id::ReactionID( "n,U235->n(25)" ),
      id::ReactionID( "n,U235->n(26)" ), id::ReactionID( "n,U235->n(27)" ),
      id::ReactionID( "n,U235->n(28)" ), id::ReactionID( "n,U235->n(29)" ),
      id::ReactionID( "n,U235->n(30)" ), id::ReactionID( "n,U235->n(31)" ),
      id::ReactionID( "n,U235->n(32)" ), id::ReactionID( "n,U235->n(33)" ),
      id::ReactionID( "n,U235->n(34)" ), id::ReactionID( "n,U235->n(35)" ),
      id::ReactionID( "n,U235->n(36)" ), id::ReactionID( "n,U235->n(37)" ),
      id::ReactionID( "n,U235->n(38)" ), id::ReactionID( "n,U235->n(39)" ),
      id::ReactionID( "n,U235->n(c)" )
    };

    CHECK( id::ReactionID( "n,U235->lumped1" ) == reaction.identifier() );
    CHECK( 851 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Summation == reaction.category() );
    CHECK( true == reaction.isSummationReaction() );
    CHECK( false == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt != reaction.partialReactionIdentifiers() );
    checkPartials( partials, reaction.partialReactionIdentifiers().value() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( std::nullopt == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyCrossSectionCovariances( const covariance::CrossSectionCovarianceData& xs ) {

    //! @todo add covariance verification

    id::ReactionID mt1( "n,U235->total" );
    id::ReactionID mt2( "n,U235->n(0)" );
    id::ReactionID mt4( "n,U235->n(t)" );
    id::ReactionID mt5( "n,U235->anything" );
    id::ReactionID mt16( "n,U235->2n(t)" );
    id::ReactionID mt17( "n,U235->3n(t)" );
    id::ReactionID mt18( "n,U235->fission" );
    id::ReactionID mt51( "n,U235->n(1)" );
    id::ReactionID mt102( "n,U235->g(t)" );
    id::ReactionID lumped1( "n,U235->lumped1" );
    id::ReactionID lumped2( "n,U235->lumped2" );

    CHECK( 11 == xs.numberReactions() );
    CHECK( 11 == xs.reactionIdentifiers().size() );
    CHECK( mt102 == xs.reactionIdentifiers()[0] );
    CHECK( mt2 == xs.reactionIdentifiers()[1] );
    CHECK( mt51 == xs.reactionIdentifiers()[2] );
    CHECK( mt4 == xs.reactionIdentifiers()[3] );
    CHECK( mt16 == xs.reactionIdentifiers()[4] );
    CHECK( mt17 == xs.reactionIdentifiers()[5] );
    CHECK( mt1 == xs.reactionIdentifiers()[6] );
    CHECK( mt5 == xs.reactionIdentifiers()[7] );
    CHECK( mt18 == xs.reactionIdentifiers()[8] );
    CHECK( lumped1 == xs.reactionIdentifiers()[9] );
    CHECK( lumped2 == xs.reactionIdentifiers()[10] );

    CHECK( 66 == xs.numberCovarianceMatrices() );
    CHECK( 66 == xs.covariances().size() );

    CHECK( true == xs.hasCovarianceMatrix( mt1 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt1, mt2 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt1, mt4 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt1, mt5 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt1, mt16 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt1, mt17 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt1, mt18 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt1, mt51 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt1, mt102 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt1, lumped1 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt1, lumped2 ) );

    CHECK( true == xs.hasCovarianceMatrix( mt2 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt2, mt4 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt2, mt5 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt2, mt16 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt2, mt17 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt2, mt18 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt2, mt51 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt2, mt102 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt2, lumped1 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt2, lumped2 ) );

    CHECK( true == xs.hasCovarianceMatrix( mt4 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt4, mt5 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt4, mt16 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt4, mt17 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt4, mt18 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt4, mt51 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt4, mt102 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt4, lumped1 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt4, lumped2 ) );

    CHECK( true == xs.hasCovarianceMatrix( mt5 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt5, mt16 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt5, mt17 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt5, mt18 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt5, mt51 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt5, mt102 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt5, lumped1 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt5, lumped2 ) );

    CHECK( true == xs.hasCovarianceMatrix( mt16 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt16, mt17 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt16, mt18 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt16, mt51 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt16, mt102 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt16, lumped1 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt16, lumped2 ) );

    CHECK( true == xs.hasCovarianceMatrix( mt17 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt17, mt18 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt17, mt51 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt17, mt102 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt17, lumped1 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt17, lumped2 ) );

    CHECK( true == xs.hasCovarianceMatrix( mt18 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt18, mt51 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt18, mt102 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt18, lumped1 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt18, lumped2 ) );

    CHECK( true == xs.hasCovarianceMatrix( mt51 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt51, mt102 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt51, lumped1 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt51, lumped2 ) );

    CHECK( true == xs.hasCovarianceMatrix( mt102 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt102, lumped1 ) );
    CHECK( true == xs.hasCovarianceMatrix( mt102, lumped2 ) );

    CHECK( true == xs.hasCovarianceMatrix( lumped1 ) );
    CHECK( true == xs.hasCovarianceMatrix( lumped1, lumped2 ) );

    CHECK( true == xs.hasCovarianceMatrix( lumped2 ) );
  }

  void verifyAngularDistributionCovariances( const covariance::AngularDistributionCovarianceData& angular ) {

    //! @todo add covariance verification

    id::ReactionID mt2( "n,U235->n(0)" );

    CHECK( 1 == angular.numberReactions() );
    CHECK( 1 == angular.reactionIdentifiers().size() );
    CHECK( mt2 == angular.reactionIdentifiers()[0] );

    CHECK( 1 == angular.numberCovarianceMatrices() );
    CHECK( 1 == angular.covariances().size() );
    CHECK( true == angular.hasCovarianceMatrix( mt2 ) );
  }

  // n-092_U_235.gendf : 97 reactions, no covariance data
  // n-092_U_235.covariances.xs.gendf : 2 reactions, xs covariance data
  // n-092_U_235.covariances.angular.gendf : no reactions, angular covariance data
  void verifyU235( const MultigroupProjectileTarget& chunk,
                   bool xs_cov, bool angular_cov ) {

    static const std::vector< id::ReactionID > reactions = {

      id::ReactionID( "n,U235->total" ), id::ReactionID( "n,U235->n(t)" ),
      id::ReactionID( "n,U235->p(t)" ), id::ReactionID( "n,U235->a(t)" ),
      id::ReactionID( "n,U235->n(0)" ), id::ReactionID( "n,U235->anything" ),
      id::ReactionID( "n,U235->2n(t)" ), id::ReactionID( "n,U235->3n(t)" ),
      id::ReactionID( "n,U235->fission" ), id::ReactionID( "n,U235->n(1)" ),
      id::ReactionID( "n,U235->n(2)" ), id::ReactionID( "n,U235->n(3)" ),
      id::ReactionID( "n,U235->n(4)" ), id::ReactionID( "n,U235->n(5)" ),
      id::ReactionID( "n,U235->n(6)" ), id::ReactionID( "n,U235->n(7)" ),
      id::ReactionID( "n,U235->n(8)" ), id::ReactionID( "n,U235->n(9)" ),
      id::ReactionID( "n,U235->n(10)" ), id::ReactionID( "n,U235->n(11)" ),
      id::ReactionID( "n,U235->n(12)" ), id::ReactionID( "n,U235->n(13)" ),
      id::ReactionID( "n,U235->n(14)" ), id::ReactionID( "n,U235->n(15)" ),
      id::ReactionID( "n,U235->n(16)" ), id::ReactionID( "n,U235->n(17)" ),
      id::ReactionID( "n,U235->n(18)" ), id::ReactionID( "n,U235->n(19)" ),
      id::ReactionID( "n,U235->n(20)" ), id::ReactionID( "n,U235->n(21)" ),
      id::ReactionID( "n,U235->n(22)" ), id::ReactionID( "n,U235->n(23)" ),
      id::ReactionID( "n,U235->n(24)" ), id::ReactionID( "n,U235->n(25)" ),
      id::ReactionID( "n,U235->n(26)" ), id::ReactionID( "n,U235->n(27)" ),
      id::ReactionID( "n,U235->n(28)" ), id::ReactionID( "n,U235->n(29)" ),
      id::ReactionID( "n,U235->n(30)" ), id::ReactionID( "n,U235->n(31)" ),
      id::ReactionID( "n,U235->n(32)" ), id::ReactionID( "n,U235->n(33)" ),
      id::ReactionID( "n,U235->n(34)" ), id::ReactionID( "n,U235->n(35)" ),
      id::ReactionID( "n,U235->n(36)" ), id::ReactionID( "n,U235->n(37)" ),
      id::ReactionID( "n,U235->n(38)" ), id::ReactionID( "n,U235->n(39)" ),
      id::ReactionID( "n,U235->n(c)" ), id::ReactionID( "n,U235->g(t)" ),
      id::ReactionID( "n,U235->p(0)" ), id::ReactionID( "n,U235->p(1)" ),
      id::ReactionID( "n,U235->p(2)" ), id::ReactionID( "n,U235->p(3)" ),
      id::ReactionID( "n,U235->p(4)" ), id::ReactionID( "n,U235->p(5)" ),
      id::ReactionID( "n,U235->p(6)" ), id::ReactionID( "n,U235->p(7)" ),
      id::ReactionID( "n,U235->p(8)" ), id::ReactionID( "n,U235->p(9)" ),
      id::ReactionID( "n,U235->p(c)" ), id::ReactionID( "n,U235->a(0)" ),
      id::ReactionID( "n,U235->a(1)" ), id::ReactionID( "n,U235->a(2)" ),
      id::ReactionID( "n,U235->a(3)" ), id::ReactionID( "n,U235->a(4)" ),
      id::ReactionID( "n,U235->a(5)" ), id::ReactionID( "n,U235->a(6)" ),
      id::ReactionID( "n,U235->a(7)" ), id::ReactionID( "n,U235->a(8)" ),
      id::ReactionID( "n,U235->a(9)" ), id::ReactionID( "n,U235->a(10)" ),
      id::ReactionID( "n,U235->a(11)" ), id::ReactionID( "n,U235->a(12)" ),
      id::ReactionID( "n,U235->a(13)" ), id::ReactionID( "n,U235->a(14)" ),
      id::ReactionID( "n,U235->a(15)" ), id::ReactionID( "n,U235->a(16)" ),
      id::ReactionID( "n,U235->a(17)" ), id::ReactionID( "n,U235->a(18)" ),
      id::ReactionID( "n,U235->a(19)" ), id::ReactionID( "n,U235->a(20)" ),
      id::ReactionID( "n,U235->a(21)" ), id::ReactionID( "n,U235->a(22)" ),
      id::ReactionID( "n,U235->a(23)" ), id::ReactionID( "n,U235->a(24)" ),
      id::ReactionID( "n,U235->a(25)" ), id::ReactionID( "n,U235->a(26)" ),
      id::ReactionID( "n,U235->a(27)" ), id::ReactionID( "n,U235->a(28)" ),
      id::ReactionID( "n,U235->a(29)" ), id::ReactionID( "n,U235->a(30)" ),
      id::ReactionID( "n,U235->a(31)" ), id::ReactionID( "n,U235->a(32)" ),
      id::ReactionID( "n,U235->a(33)" ), id::ReactionID( "n,U235->a(34)" ),
      id::ReactionID( "n,U235->a(35)" )
    };

    CHECK( id::ParticleID( "n" ) == chunk.projectileIdentifier() );
    CHECK( id::ParticleID( "U235" ) == chunk.targetIdentifier() );

    CHECK( InteractionType::Nuclear == chunk.interactionType() );

    if ( ! xs_cov ) {

      CHECK( 97 == chunk.numberReactions() );
      for ( const id::ReactionID& id : reactions ) {

        CHECK( true == chunk.hasReaction( id ) );
      }
    }
    else {

      CHECK( 99 == chunk.numberReactions() );
      for ( const id::ReactionID& id : reactions ) {

        CHECK( true == chunk.hasReaction( id ) );
      }
      CHECK( true == chunk.hasReaction( id::ReactionID( "n,U235->lumped1" ) ) );
      CHECK( true == chunk.hasReaction( id::ReactionID( "n,U235->lumped2" ) ) );
    }

    verifyTotalReaction( chunk.reaction( id::ReactionID( "n,U235->total" ) ) );
    verifyElasticReaction( chunk.reaction( id::ReactionID( "n,U235->n,U235" ) ) );
    verifyInelasticReaction( chunk.reaction( id::ReactionID( "n,U235->n,U235[all]" ) ) );
    verifyAnythingReaction( chunk.reaction( id::ReactionID( "n,U235->anything" ) ) );
    verifyN2NReaction( chunk.reaction( id::ReactionID( "n,U235->2n,U234[all]" ) ) );
    verifyN3NReaction( chunk.reaction( id::ReactionID( "n,U235->3n,U233[all]" ) ) );
    verifyFissionReaction( chunk.reaction( id::ReactionID( "n,U235->fission(t)" ) ) );
    verifyFirstInelasticReaction( chunk.reaction( id::ReactionID( "n,U235->n,U235_e1" ) ) );
    verifyCaptureReaction( chunk.reaction( id::ReactionID( "n,U235->g,U236[all]" ) ) );
    verifyProtonReaction( chunk.reaction( id::ReactionID( "n,U235->p,Pa235[all]" ) ) );
    verifyAlphaReaction( chunk.reaction( id::ReactionID( "n,U235->a,Th232[all]" ) ) );
    if ( xs_cov ) {

      verifyLumped1Reaction( chunk.reaction( id::ReactionID( "n,U235->a,Th232[all]" ) ) );
    }

    if ( xs_cov || angular_cov ) {

      CHECK( std::nullopt != chunk.covarianceData() );

      if ( xs_cov ) {

        CHECK( std::nullopt != chunk.covarianceData()->crossSection() );
        verifyCrossSectionCovariances( chunk.covarianceData()->crossSection().value() );
      }

      if ( angular_cov ) {

        CHECK( std::nullopt != chunk.covarianceData()->angularDistribution() );
        verifyAngularDistributionCovariances( chunk.covarianceData()->angularDistribution().value() );
      }
    }
    else {

      CHECK( std::nullopt == chunk.covarianceData() );
    }
  }

} // namespace u235
} // namespace neutron
