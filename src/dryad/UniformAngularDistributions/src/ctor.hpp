/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
UniformAngularDistributions() = default;

UniformAngularDistributions( const UniformAngularDistributions& ) = default;
UniformAngularDistributions( UniformAngularDistributions&& ) = default;

UniformAngularDistributions& operator=( const UniformAngularDistributions& ) = default;
UniformAngularDistributions& operator=( UniformAngularDistributions&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param grid            the grid values
 *  @param distributions   the associated distributions
 *  @param boundaries      the boundaries of the interpolation regions
 *  @param interpolants    the interpolation types of the interpolation regions
 */
UniformAngularDistributions( std::vector< double > grid,
                             std::vector< UniformAngularDistribution > distributions,
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
UniformAngularDistributions( std::vector< double > grid,
                             std::vector< UniformAngularDistribution > distributions,
                             InterpolationType interpolant = InterpolationType::LinearLinear ) :
  Parent( std::move( grid ), std::move( distributions ), interpolant ) {}
