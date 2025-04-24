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
 */
TabulatedAngularDistribution(
    std::vector< double > cosines,
    std::vector< double > values,
    std::vector< std::size_t > boundaries,
    std::vector< InterpolationType > interpolants,
    bool cdf = false ) :
  pdf_( std::move( cosines ), std::move( values ),
        std::move( boundaries ), std::move( interpolants ) ),
  cdf_( std::nullopt ) {

  this->pdf_.normalise();
}

/**
 *  @brief Constructor for a pdf using a single interpolation zone
 *
 *  @param cosines        the cosine values
 *  @param values         the probability values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedAngularDistribution(
    std::vector< double > cosines,
    std::vector< double > values,
    InterpolationType interpolant = InterpolationType::LinearLinear,
    bool cdf = false ) :
  pdf_( std::move( cosines ), std::move( values ), interpolant ),
  cdf_( std::nullopt ) {

  this->pdf_.normalise();
}

/**
 *  @brief Constructor using a pdf and cdf
 *
 *  @param pdf   the pdf of the distribution
 *  @param cdf   the cdf of the distribution
 */
TabulatedAngularDistribution( TabulatedAngularDistributionFunction pdf ) :
  pdf_( std::move( pdf ) ),
  cdf_( std::nullopt ) {

  this->pdf_.normalise();
}

/**
 *  @brief Constructor using a pdf and cdf
 *
 *  @param pdf   the pdf of the distribution
 *  @param cdf   the cdf of the distribution
 */
TabulatedAngularDistribution( TabulatedAngularDistributionFunction pdf,
                              TabulatedAngularDistributionFunction cdf ) :
  pdf_( std::move( pdf ) ),
  cdf_( std::move( cdf ) ) {

  this->pdf_.normalise();
}
