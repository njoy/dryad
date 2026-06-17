/**
 *  @brief Extract a submatrix from the covariance matrix based
 *         on selected values of the keys
 */
AngularDistributionCovarianceMatrix
extract( const std::optional< id::ReactionID >& reaction,
         const std::optional< std::size_t >& moment,
         const std::optional< id::EnergyGroup >& group ) const {

  return AngularDistributionCovarianceMatrix(
           Parent::extract( reaction, moment, group ),
           this->frame() );
}

/**
 *  @brief Extract a submatrix from the covariance matrix based
 *         on selected values of the keys
 */
AngularDistributionCovarianceMatrix
extract( const std::optional< id::ReactionID >& rowReaction,
         const std::optional< std::size_t >& rowMoment,
         const std::optional< id::EnergyGroup >& rowGroup,
         const std::optional< id::ReactionID >& colReaction,
         const std::optional< std::size_t >& colMoment,
         const std::optional< id::EnergyGroup >& colGroup ) const {

  return AngularDistributionCovarianceMatrix(
           Parent::extract( rowReaction, rowMoment, rowGroup,
                          colReaction, colMoment, colGroup ),
           this->frame() );
}
