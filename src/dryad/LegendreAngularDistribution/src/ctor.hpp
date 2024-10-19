private:

/**
 *  @brief Private constructor
 *
 *  @param series   the series expansion
 */
LegendreAngularDistribution( LegendreSeries< double, double > table ) :
  LegendreSeries( std::move( table ) ) {}

public:

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
LegendreAngularDistribution( std::vector< double > coefficients ) :
  LegendreSeries( std::move( coefficients ) ) {}
