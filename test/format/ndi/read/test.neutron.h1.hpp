namespace neutron {

// test functions based on 1001.831nm
namespace h1 {

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

      29.32150766956950, 21.61693393875450, 20.89541207945840, 20.62012802257230, 20.51266149169490,
      20.46827473963340, 20.44685141515090, 20.42985288694520, 20.40174151859570, 20.33402388644090,
      20.15707750942530, 19.69623198839820, 18.56439230911150, 16.15193306661810, 12.24380954569480,
       8.94169268479905,  6.92888165102905,  5.36179172490167,  4.14180627574431,  3.38399872580098,
       2.94318929152132,  2.55094838583866,  2.19028335341669,  1.75604860794844,  1.29523919063075,
       1.05774431185885,  0.86073908041403,  0.74390350182312,  0.68465344564727,  0.61438017081722
    };
    static const std::vector< id::ReactionID > partials = {

      id::ReactionID( "n,H1->n(0)" ), id::ReactionID( "n,H1->g(t)" )
    };

    CHECK( id::ReactionID( "n,H1->total" ) == reaction.identifier() );
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

      29.02387193247870, 21.51024435650740, 20.83073697603060, 20.58091403055380, 20.48885439312890,
      20.45383300294320, 20.43809211539920, 20.42454178467770, 20.39852384311520, 20.33208244565180,
      20.15591085157790, 19.69553919314670, 18.56399610527600, 16.15172519963870, 12.24371078269810,
       8.94163902976473,  6.92884234312335,  5.36175758386261,  4.14177215022087,  3.38396312330490,
       2.94315268770038,  2.55091138583866,  2.19024635341669,  1.75601275074314,  1.29520561542145,
       1.05771215685360,  0.86070817430621,  0.74387347428809,  0.68462385383360,  0.61435136208940
    };

    CHECK( id::ReactionID( "n,H1->n,H1" ) == reaction.identifier() );
    CHECK( 50 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( 0. == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 0 == reaction.numberProducts() );
  }

  void verifyCaptureReaction( const MultigroupReaction& reaction ) {

    static const std::vector< double > xs = {

      2.97634536251123E-01, 1.06689951442789E-01, 6.46737197873134E-02, 3.92150743546718E-02,
      2.38064899666136E-02, 1.44418493270847E-02, 8.76028047766750E-03, 5.31104427648608E-03,
      3.21654684790510E-03, 1.94371822578451E-03, 1.16883211628829E-03, 6.92849124448312E-04,
      3.96228538798634E-04, 2.09223131235667E-04, 9.84018778668421E-05, 5.35305768937989E-05,
      3.92647991187505E-05, 3.40660950542441E-05, 3.41245462714632E-05, 3.57404258591689E-05,
      3.67837015787691E-05, 3.72902659543356E-05, 3.71072704837236E-05, 3.58384647521920E-05,
      3.36166337034680E-05, 3.22049219560136E-05, 3.09136651064694E-05, 3.00402870366568E-05,
      2.95372897252305E-05, 2.88461269617614E-05
    };

    CHECK( id::ReactionID( "n,H1->g,H2[all]" ) == reaction.identifier() );
    CHECK( 102 == reaction.identifier().reactionType().mt() );
    CHECK( ReactionCategory::Primary == reaction.category() );
    CHECK( false == reaction.isSummationReaction() );
    CHECK( true == reaction.isPrimaryReaction() );
    CHECK( false == reaction.hasProducts() );

    CHECK( std::nullopt == reaction.partialReactionIdentifiers() );

    CHECK( std::nullopt == reaction.massDifferenceQValue() );
    CHECK( 2224647.9999999997 == reaction.reactionQValue() );

    CHECK( 30 == reaction.crossSection().numberGroups() );
    checkBoundaries( reaction.crossSection().boundaries() );
    checkGroups( xs, reaction.crossSection().values() );

    CHECK( 0 == reaction.numberProducts() );
  }

} // namespace h1
} // namespace neutron
