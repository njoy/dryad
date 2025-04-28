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
 *  @param[in] lower          the lower energy limit
 *  @param[in] upper          the upper energy limit
 *  @param[in] reactions      the reactions in the linear combination
 *  @param[in] coefficients   the coefficients of the linear combination
 */
LinearCombinationCovariance( double lower, double upper,
                             std::vector< id::ReactionID > reactions,
                             std::vector< double > coefficients ) :
  lower_( std::move( lower ) ), upper_( std::move( upper ) ),
  reactions_( std::move( reactions ) ),
  coefficients_( std::move( coefficients ) ) {

  verifySize( this->reactions().size(), this->coefficients().size() );
}
