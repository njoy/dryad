private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
HardSphereShiftFactor( PolynomialSeriesRatio< double, double > ratio ) :
  PolynomialSeriesRatio( std::move( ratio ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
HardSphereShiftFactor() = default;

HardSphereShiftFactor( const HardSphereShiftFactor& ) = default;
HardSphereShiftFactor( HardSphereShiftFactor&& ) = default;

HardSphereShiftFactor& operator=( const HardSphereShiftFactor& ) = default;
HardSphereShiftFactor& operator=( HardSphereShiftFactor&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param orbitalAngularMomentum   the value of the orbital angular momentum
 */
HardSphereShiftFactor( unsigned int orbitalAngularMomentum ) :
  PolynomialSeriesRatio( generateFunction( orbitalAngularMomentum ) ),
  orbital_momentum_( orbitalAngularMomentum ) {}
