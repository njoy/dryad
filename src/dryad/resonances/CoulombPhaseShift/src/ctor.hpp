/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CoulombPhaseShift() = default;

CoulombPhaseShift( const CoulombPhaseShift& ) = default;
CoulombPhaseShift( CoulombPhaseShift&& ) = default;

CoulombPhaseShift& operator=( const CoulombPhaseShift& ) = default;
CoulombPhaseShift& operator=( CoulombPhaseShift&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param orbitalMomentum   the value of the orbital momentum
 */
CoulombPhaseShift( unsigned int orbitalMomentum ) :
  orbital_momentum_( orbitalMomentum ) {}
