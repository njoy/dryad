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
 *  @param orbitalMomentum   the value of the orbital momentum
 */
CoulombShiftFactor( unsigned int orbitalMomentum ) :
  orbital_momentum_( orbitalMomentum ) {}
