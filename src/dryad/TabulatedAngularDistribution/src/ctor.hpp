/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedAngularDistribution() = default;

TabulatedAngularDistribution( const TabulatedAngularDistribution& ) = default;
TabulatedAngularDistribution( TabulatedAngularDistribution&& ) = default;

TabulatedAngularDistribution& operator=( const TabulatedAngularDistribution& ) = default;
TabulatedAngularDistribution& operator=( TabulatedAngularDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param cosines        the cosine values
 *  @param values         the probability values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 *  @param normalise      option to indicate whether or not to normalise
 *                        all probability data (default: no normalisation)
 */
TabulatedAngularDistribution(
    std::vector< double > cosines,
    std::vector< double > values,
    std::vector< std::size_t > boundaries,
    std::vector< InterpolationType > interpolants,
    bool normalise = false ) :
  pdf_( std::move( cosines ), std::move( values ),
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
 *  @brief Constructor for a pdf using a single interpolation zone
 *
 *  @param cosines        the cosine values
 *  @param values         the probability values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 *  @param normalise      option to indicate whether or not to normalise
 *                        all probability data (default: no normalisation)
 */
TabulatedAngularDistribution(
    std::vector< double > cosines,
    std::vector< double > values,
    InterpolationType interpolant = InterpolationType::LinearLinear,
    bool normalise = false ) :
  pdf_( std::move( cosines ), std::move( values ), std::move( interpolant ) ),
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
TabulatedAngularDistribution( TabulatedAngularDistributionFunction pdf,
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
 *  @param pdf   the pdf of the distribution
 *  @param cdf   the cdf of the distribution
 */
TabulatedAngularDistribution( TabulatedAngularDistributionFunction pdf,
                              TabulatedAngularDistributionFunction cdf ) :
  pdf_( std::move( pdf ) ), cdf_( std::move( cdf ) ) {}
