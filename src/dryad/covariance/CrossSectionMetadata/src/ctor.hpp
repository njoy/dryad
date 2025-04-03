/**
 *  @brief Constructor
 *
 *  @param[in] projectile   the projectile identifier
 *  @param[in] target       the target identifier
 *  @param[in] reaction     the reaction identifier
 *  @param[in] energies     the energy boundaries
 */
CrossSectionMetadata( id::ParticleID projectile,
                      id::ParticleID target,
                      id::ReactionID reaction,
                      std::vector< double > energies ) :
  projectile_id_( std::move( projectile ) ),
  target_id_( std::move( target ) ),
  reaction_id_( std::move( reaction ) ),
  energies_( std::move( energies ) ) {

  verifyEnergies( this->energies() );
}
