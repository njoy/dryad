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
 */
LegendreAngularDistribution( std::vector< double > coefficients ) :
    pdf_( std::move( coefficients ) ), cdf_() {

  this->pdf_.normalise();
  this->cdf_ = this->pdf().primitive( -1. );
}
