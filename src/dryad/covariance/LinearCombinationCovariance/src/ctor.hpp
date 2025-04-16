/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
LinearCombinationCovariance() = default;

LinearCombinationCovariance( const LinearCombinationCovariance& ) = default;
LinearCombinationCovariance( LinearCombinationCovariance&& ) = default;

LinearCombinationCovariance& operator=( const LinearCombinationCovariance& ) = default;
LinearCombinationCovariance& operator=( LinearCombinationCovariance&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] reactions      the reactions in the linear combination
 *  @param[in] coefficients   the coefficients of the linear combination
 */
LinearCombinationCovariance( std::vector< id::ReactionID > reactions,
                             std::vector< double > coefficients ) :
  reactions_( std::move( reactions ) ),
  coefficients_( std::move( coefficients ) ) {

  verifySize( this->reactions().size(), this->coefficients().size() );
}
