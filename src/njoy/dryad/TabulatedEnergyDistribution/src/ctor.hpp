/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedEnergyDistribution() = default;

TabulatedEnergyDistribution( const TabulatedEnergyDistribution& ) = default;
TabulatedEnergyDistribution( TabulatedEnergyDistribution&& ) = default;

TabulatedEnergyDistribution& operator=( const TabulatedEnergyDistribution& ) = default;
TabulatedEnergyDistribution& operator=( TabulatedEnergyDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param energies       the energy values
 *  @param values         the probability values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 *  @param normalise      option to indicate whether or not to normalise
 *                        all probability data (default: no normalisation)
 */
TabulatedEnergyDistribution(
    std::vector< double > energies,
    std::vector< double > values,
    std::vector< std::size_t > boundaries,
    std::vector< InterpolationType > interpolants,
    bool normalise = false ) :
  pdf_( std::move( energies ), std::move( values ),
        std::move( boundaries ), std::move( interpolants ) ),
  cdf_() {

  if ( normalise ) {

    this->normalise();
  }
  else {

    this->calculateCdf();
  }
}

/**
 *  @brief Constructor for an energy distirbution using a single interpolation zone
 *
 *  @param energies       the energy values
 *  @param values         the probability values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 *  @param normalise      option to indicate whether or not to normalise
 *                        all probability data (default: no normalisation)
 */
TabulatedEnergyDistribution(
    std::vector< double > energies,
    std::vector< double > values,
    InterpolationType interpolant = InterpolationType::LinearLinear,
    bool normalise = false ) :
  pdf_( std::move( energies ), std::move( values ), interpolant ),
  cdf_() {

  if ( normalise ) {

    this->normalise();
  }
  else {

    this->calculateCdf();
  }
}

/**
 *  @brief Constructor using a pdf
 *
 *  @param pdf         the pdf of the distribution
 *  @param normalise   option to indicate whether or not to normalise
 *                     all probability data (default: no normalisation)
 */
TabulatedEnergyDistribution( TabulatedEnergyDistributionFunction pdf,
                             bool normalise = false ) :
  pdf_( std::move( pdf ) ), cdf_() {

  if ( normalise ) {

    this->normalise();
  }
  else {

    this->calculateCdf();
  }
}

/**
 *  @brief Constructor using a pdf and cdf
 *
 *  @param pdf         the pdf of the distribution
 *  @param cdf         the cdf of the distribution
 */
TabulatedEnergyDistribution( TabulatedEnergyDistributionFunction pdf,
                             TabulatedEnergyDistributionFunction cdf ) :
  pdf_( std::move( pdf ) ), cdf_( std::move( cdf ) ) {}
