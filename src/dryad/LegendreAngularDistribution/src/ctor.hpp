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
LegendreAngularDistribution( std::vector< double > coefficients ) :
  LegendreSeries( std::move( coefficients ) ) {}
