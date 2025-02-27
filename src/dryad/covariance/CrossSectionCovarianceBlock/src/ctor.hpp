/**
 *  @brief Constructor for a diagonal cross section covariance block
 *
 *  @param[in] projectile    the projectile identifier
 *  @param[in] target        the target identifier
 *  @param[in] reaction      the reaction identifier
 *  @param[in] energies      the energy boundaries
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
CrossSectionCovarianceBlock( id::ParticleID projectile,
                             id::ParticleID target,
                             id::ReactionID reaction,
                             std::vector< double > energies,
                             Matrix< double > covariances,
                             bool relative = true ) :
  CovarianceBlock( CrossSectionMetadata( std::move( projectile ),
                                         std::move( target ),
                                         std::move( reaction ),
                                         std::move( energies ) ),
                   std::move( covariances ), relative ) {}

/**
 *  @brief Constructor for an off-diagonal cross section covariance block
 *
 *  @param[in] rowProjectile       the row projectile identifier
 *  @param[in] rowTarget           the row target identifier
 *  @param[in] rowReaction         the row reaction identifier
 *  @param[in] rowEnergies         the row energy boundaries
 *  @param[in] columnProjectile    the column projectile identifier
 *  @param[in] columnTarget        the column target identifier
 *  @param[in] columnReaction      the column reaction identifier
 *  @param[in] columnEnergies      the column energy boundaries
 *  @param[in] covariances         the covariance matrix
 *  @param[in] relative            the relative covariance flag
 */
CrossSectionCovarianceBlock( id::ParticleID rowProjectile,
                             id::ParticleID rowTarget,
                             id::ReactionID rowReaction,
                             std::vector< double > rowEnergies,
                             id::ParticleID columnProjectile,
                             id::ParticleID columnTarget,
                             id::ReactionID columnReaction,
                             std::vector< double > columnEnergies,
                             Matrix< double > covariances,
                             bool relative = true ) :
  CovarianceBlock( CrossSectionMetadata( std::move( rowProjectile ),
                                         std::move( rowTarget ),
                                         std::move( rowReaction ),
                                         std::move( rowEnergies ) ),
                   CrossSectionMetadata( std::move( columnProjectile ),
                                         std::move( columnTarget ),
                                         std::move( columnReaction ),
                                         std::move( columnEnergies ) ),
                   std::move( covariances ),
                   relative ) {}
