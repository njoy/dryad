/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedAngularDistributions() = default;

TabulatedAngularDistributions( const TabulatedAngularDistributions& ) = default;
TabulatedAngularDistributions( TabulatedAngularDistributions&& ) = default;

TabulatedAngularDistributions& operator=( const TabulatedAngularDistributions& ) = default;
TabulatedAngularDistributions& operator=( TabulatedAngularDistributions&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param grid            the grid values
 *  @param distributions   the associated distributions
 *  @param boundaries      the boundaries of the interpolation regions
 *  @param interpolants    the interpolation types of the interpolation regions
 */
TabulatedAngularDistributions( std::vector< double > grid,
                               std::vector< TabulatedAngularDistribution > distributions,
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
TabulatedAngularDistributions( std::vector< double > grid,
                               std::vector< TabulatedAngularDistribution > distributions,
                               InterpolationType interpolant = InterpolationType::LinearLinear ) :
  Parent( std::move( grid ), std::move( distributions ), interpolant ) {}
