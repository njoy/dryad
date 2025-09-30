/**
 *  @brief Extract a submatrix from the covariance matrix based
 *         on selected values of the keys
 */
ProductMultiplicityCovarianceMatrix
extract( const std::optional< id::ReactionID >& reaction,
         const std::optional< id::EnergyGroup >& group,
         const std::optional< id::ParticleID >& product ) const {

  return Parent::extract( reaction, group, product );
}

/**
 *  @brief Extract a submatrix from the covariance matrix based
 *         on selected values of the keys
 */
ProductMultiplicityCovarianceMatrix
extract( const std::optional< id::ReactionID >& rowReaction,
         const std::optional< id::EnergyGroup >& rowGroup,
         const std::optional< id::ParticleID >& rowProduct,
         const std::optional< id::ReactionID >& colReaction,
         const std::optional< id::EnergyGroup >& colGroup,
         const std::optional< id::ParticleID >& colProduct ) const {

  return Parent::extract( rowReaction, rowGroup, rowProduct,
                          colReaction, colGroup, colProduct );
}
