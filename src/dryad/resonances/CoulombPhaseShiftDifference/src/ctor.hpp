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
 *  @param orbitalAngularMomentum   the value of the orbital angular momentum
 */
CoulombPhaseShiftDifference( unsigned int orbitalAngularMomentum ) :
  orbital_momentum_( orbitalAngularMomentum ) {}
