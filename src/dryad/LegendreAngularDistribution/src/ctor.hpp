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
 *  @param coefficients   the coefficients of the Legendre series (from
 *                        lowest to highest order coefficient)
 */
LegendreAngularDistribution( std::vector< double > coefficients, bool cdf = false ) :
  pdf_( std::move( coefficients ) ), cdf_( std::nullopt ) {}
