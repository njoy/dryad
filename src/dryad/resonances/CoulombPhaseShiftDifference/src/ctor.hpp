/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CoulombPhaseShiftDifference() = default;

CoulombPhaseShiftDifference( const CoulombPhaseShiftDifference& ) = default;
CoulombPhaseShiftDifference( CoulombPhaseShiftDifference&& ) = default;

CoulombPhaseShiftDifference& operator=( const CoulombPhaseShiftDifference& ) = default;
CoulombPhaseShiftDifference& operator=( CoulombPhaseShiftDifference&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param orbitalMomentum   the value of the orbital momentum
 */
CoulombPhaseShiftDifference( unsigned int orbitalMomentum ) :
  orbital_momentum_( orbitalMomentum ) {}
