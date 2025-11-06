/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
UniformEnergyDistribution() = default;

UniformEnergyDistribution( const UniformEnergyDistribution& ) = default;
UniformEnergyDistribution( UniformEnergyDistribution&& ) = default;

UniformEnergyDistribution& operator=( const UniformEnergyDistribution& ) = default;
UniformEnergyDistribution& operator=( UniformEnergyDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param energies   the energy values
 *  @param type       the uniform distribution type
 */
UniformEnergyDistribution( std::vector< double > energies,
                           UniformDistributionType type ) :
  UniformDistribution( std::move( energies ), std::move( type ) ) {}
