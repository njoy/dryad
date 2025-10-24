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
 *  @param orbitalMomentum   the value of the orbital momentum
 */
HardSphereShiftFactor( unsigned int orbitalMomentum ) :
  PolynomialSeriesRatio( generateFunction( orbitalMomentum ) ),
  orbital_momentum_( orbitalMomentum ) {}
