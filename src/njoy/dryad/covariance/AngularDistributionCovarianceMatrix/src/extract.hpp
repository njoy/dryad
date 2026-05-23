/**
 *  @brief Extract a submatrix from the covariance matrix based
 *         on selected values of the keys
 */
AngularDistributionCovarianceMatrix
extract( const std::optional< id::ReactionID >& reaction,
         const std::optional< id::EnergyGroup >& group,
         const std::optional< std::size_t >& moment ) const {

  return Parent::extract( reaction, group, moment );
}

/**
 *  @brief Extract a submatrix from the covariance matrix based
 *         on selected values of the keys
 */
AngularDistributionCovarianceMatrix
extract( const std::optional< id::ReactionID >& rowReaction,
         const std::optional< id::EnergyGroup >& rowGroup,
         const std::optional< std::size_t >& rowMoment,
         const std::optional< id::ReactionID >& colReaction,
         const std::optional< id::EnergyGroup >& colGroup,
         const std::optional< std::size_t >& colMoment ) const {

  return Parent::extract( rowReaction, rowGroup, rowMoment,
                          colReaction, colGroup, colMoment );
}
