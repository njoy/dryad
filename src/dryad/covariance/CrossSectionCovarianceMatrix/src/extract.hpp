/**
 *  @brief Extract a submatrix from the covariance matrix based
 *         on selected values of the keys
 */
CrossSectionCovarianceMatrix
extract( const std::optional< id::ReactionID >& reaction,
         const std::optional< id::EnergyGroup >& group ) const {

  return Parent::extract( reaction, group );
}

/**
 *  @brief Extract a submatrix from the covariance matrix based
 *         on selected values of the keys
 */
CrossSectionCovarianceMatrix
extract( const std::optional< id::ReactionID >& rowReaction,
         const std::optional< id::EnergyGroup >& rowGroup,
         const std::optional< id::ReactionID >& colReaction,
         const std::optional< id::EnergyGroup >& colGroup ) const {

  return Parent::extract( rowReaction, rowGroup,
                          colReaction, colGroup );
}
