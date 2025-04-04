/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
UniformAngularDistribution() = default;

UniformAngularDistribution( const UniformAngularDistribution& ) = default;
UniformAngularDistribution( UniformAngularDistribution&& ) = default;

UniformAngularDistribution& operator=( const UniformAngularDistribution& ) = default;
UniformAngularDistribution& operator=( UniformAngularDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param cosines   the cosine values
 *  @param type      the uniform distribution type
 */
UniformAngularDistribution( std::vector< double > cosines,
                            UniformDistributionType type ) :
  UniformDistribution( std::move( cosines ), std::move( type ) ) {}
