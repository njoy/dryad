/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
UniformEnergyDistributions() = default;

UniformEnergyDistributions( const UniformEnergyDistributions& ) = default;
UniformEnergyDistributions( UniformEnergyDistributions&& ) = default;

UniformEnergyDistributions& operator=( const UniformEnergyDistributions& ) = default;
UniformEnergyDistributions& operator=( UniformEnergyDistributions&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param grid            the grid values
 *  @param distributions   the associated distributions
 *  @param boundaries      the boundaries of the interpolation regions
 *  @param interpolants    the interpolation types of the interpolation regions
 */
UniformEnergyDistributions( std::vector< double > grid,
                            std::vector< UniformEnergyDistribution > distributions,
                            std::vector< std::size_t > boundaries,
                            std::vector< InterpolationType > interpolants ) :
  Parent( std::move( grid ), std::move( distributions ),
          std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for angular distributions using a single interpolation zone
 *
 *  @param grid            the grid values
 *  @param distributions   the associated distributions
 *  @param interpolant     the interpolation type of the data (default lin-lin)
 */
UniformEnergyDistributions( std::vector< double > grid,
                            std::vector< UniformEnergyDistribution > distributions,
                            InterpolationType interpolant = InterpolationType::LinearLinear ) :
  Parent( std::move( grid ), std::move( distributions ), interpolant ) {}
