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
  cosines_( std::move( cosines ) ), type_( std::move( type ) ) {}
