/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
LegendreAngularDistribution() = default;

LegendreAngularDistribution( const LegendreAngularDistribution& ) = default;
LegendreAngularDistribution( LegendreAngularDistribution&& ) = default;

LegendreAngularDistribution& operator=( const LegendreAngularDistribution& ) = default;
LegendreAngularDistribution& operator=( LegendreAngularDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the distribution pdf represented by a
 *                        Legendre series (from lowest to highest order coefficient)
 *  @param normalise      option to indicate whether or not to normalise
 *                        all probability data (default: no normalisation)
 */
LegendreAngularDistribution( std::vector< double > coefficients,
                             bool normalise = false ) :
    pdf_( std::move( coefficients ) ), cdf_() {

  if ( normalise ) {

    this->pdf_.normalise();
  }
  this->calculateCdf();
}
