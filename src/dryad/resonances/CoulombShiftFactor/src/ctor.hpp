/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CoulombShiftFactor() = default;

CoulombShiftFactor( const CoulombShiftFactor& ) = default;
CoulombShiftFactor( CoulombShiftFactor&& ) = default;

CoulombShiftFactor& operator=( const CoulombShiftFactor& ) = default;
CoulombShiftFactor& operator=( CoulombShiftFactor&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param orbitalAngularMomentum   the value of the orbital angular momentum
 */
CoulombShiftFactor( unsigned int orbitalAngularMomentum ) :
  orbital_momentum_( orbitalAngularMomentum ) {}
