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
 *  @param orbitalMomentum   the value of the orbital momentum
 */
HardSpherePenetrability( unsigned int orbitalMomentum ) :
  PolynomialSeriesRatio( generateFunction( orbitalMomentum ) ),
  orbital_momentum_( orbitalMomentum ) {}
