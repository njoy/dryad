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
 *  @param orbitalAngularMomentum   the value of the orbital angular momentum
 */
HardSpherePenetrability( unsigned int orbitalAngularMomentum ) :
  PolynomialSeriesRatio( generateFunction( orbitalAngularMomentum ) ),
  orbital_momentum_( orbitalAngularMomentum ) {}
