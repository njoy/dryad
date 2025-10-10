private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
HardSpherePenetrability( PolynomialSeriesRatio< double, double > ratio ) :
  PolynomialSeriesRatio( std::move( ratio ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
HardSpherePenetrability() = default;

HardSpherePenetrability( const HardSpherePenetrability& ) = default;
HardSpherePenetrability( HardSpherePenetrability&& ) = default;

HardSpherePenetrability& operator=( const HardSpherePenetrability& ) = default;
HardSpherePenetrability& operator=( HardSpherePenetrability&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param ratios         the ratio values
 *  @param values         the wave function values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
HardSpherePenetrability( unsigned int l ) :
  PolynomialSeriesRatio( generateFunction( l ) ),
  orbital_momentum_( l ) {}
