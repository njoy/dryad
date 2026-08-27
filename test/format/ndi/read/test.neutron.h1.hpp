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

} // namespace h1
} // namespace neutron
