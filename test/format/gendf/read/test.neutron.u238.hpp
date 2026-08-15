namespace neutron {

// test functions based on n-092_U_238.angular_covariances.gendf
namespace u238 {

  void verifyAngularDistributionCovariances( const covariance::AngularDistributionCovarianceData& angular ) {

    //! @todo add covariance verification

    id::ReactionID mt2( "n,U238->n(0)" );

    CHECK( 1 == angular.numberReactions() );
    CHECK( 1 == angular.reactionIdentifiers().size() );
    CHECK( mt2 == angular.reactionIdentifiers()[0] );

    CHECK( 1 == angular.numberCovarianceMatrices() );
    CHECK( 1 == angular.covariances().size() );
    CHECK( true == angular.hasCovarianceMatrix( mt2 ) );
  }

  void verifyU238( const MultigroupProjectileTarget& chunk ) {

    CHECK( id::ParticleID( "n" ) == chunk.projectileIdentifier() );
    CHECK( id::ParticleID( "U238" ) == chunk.targetIdentifier() );

    CHECK( InteractionType::Nuclear == chunk.interactionType() );

    CHECK( 0 == chunk.numberReactions() );

    CHECK( std::nullopt != chunk.covarianceData() );
    CHECK( std::nullopt == chunk.covarianceData()->crossSection() );
    CHECK( std::nullopt != chunk.covarianceData()->angularDistribution() );

    verifyAngularDistributionCovariances( chunk.covarianceData()->angularDistribution().value() );
  }

} // namespace u238
} // namespace neutron
