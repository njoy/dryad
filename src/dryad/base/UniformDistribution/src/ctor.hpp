/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
UniformDistribution() = default;

UniformDistribution( const UniformDistribution& ) = default;
UniformDistribution( UniformDistribution&& ) = default;

UniformDistribution& operator=( const UniformDistribution& ) = default;
UniformDistribution& operator=( UniformDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param values   the cosine values
 *  @param type     the uniform distribution type
 */
UniformDistribution( std::vector< double > values,
                     UniformDistributionType type ) :
  values_( std::move( values ) ), type_( std::move( type ) ) {

  verifySize( this->values_.size(), this->type() );
}
