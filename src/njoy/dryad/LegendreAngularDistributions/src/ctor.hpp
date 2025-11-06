/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
LegendreAngularDistributions() = default;

LegendreAngularDistributions( const LegendreAngularDistributions& ) = default;
LegendreAngularDistributions( LegendreAngularDistributions&& ) = default;

LegendreAngularDistributions& operator=( const LegendreAngularDistributions& ) = default;
LegendreAngularDistributions& operator=( LegendreAngularDistributions&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param grid            the grid values
 *  @param distributions   the associated distributions
 *  @param boundaries      the boundaries of the interpolation regions
 *  @param interpolants    the interpolation types of the interpolation regions
 *  @param normalise       option to indicate whether or not to normalise
 *                         all probability data (default: no normalisation)
 */
LegendreAngularDistributions( std::vector< double > grid,
                              std::vector< LegendreAngularDistribution > distributions,
                              std::vector< std::size_t > boundaries,
                              std::vector< InterpolationType > interpolants,
                              bool normalise = false ) :
  Parent( std::move( grid ), std::move( distributions ),
          std::move( boundaries ), std::move( interpolants ) ) {

  if ( normalise ) {

    this->normalise();
  }
}

/**
 *  @brief Constructor for angular distributions using a single interpolation zone
 *
 *  @param grid            the grid values
 *  @param distributions   the associated distributions
 *  @param interpolant     the interpolation type of the data (default lin-lin)
 *  @param normalise       option to indicate whether or not to normalise
 *                         all probability data (default: no normalisation)
 */
LegendreAngularDistributions( std::vector< double > grid,
                              std::vector< LegendreAngularDistribution > distributions,
                              InterpolationType interpolant = InterpolationType::LinearLinear,
                              bool normalise = false ) :
  Parent( std::move( grid ), std::move( distributions ), interpolant ) {

  if ( normalise ) {

    this->normalise();
  }
}
