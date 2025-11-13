private:

/**
 *  @brief Private constructor
 *
 *  @param series   the series expansion
 */
LegendreAngularDistributionFunction( LegendreSeries< double, double > table ) :
  LegendreSeries( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
LegendreAngularDistributionFunction() = default;

LegendreAngularDistributionFunction( const LegendreAngularDistributionFunction& ) = default;
LegendreAngularDistributionFunction( LegendreAngularDistributionFunction&& ) = default;

LegendreAngularDistributionFunction& operator=( const LegendreAngularDistributionFunction& ) = default;
LegendreAngularDistributionFunction& operator=( LegendreAngularDistributionFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the Legendre series (from
 *                        lowest to highest order coefficient)
 */
LegendreAngularDistributionFunction( std::vector< double > coefficients ) :
  LegendreSeries( std::move( coefficients ) ) {}
