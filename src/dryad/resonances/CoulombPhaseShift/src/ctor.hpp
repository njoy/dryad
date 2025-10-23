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
 *  @param orbitalAngularMomentum   the value of the orbital angular momentum
 */
CoulombPhaseShift( unsigned int orbitalAngularMomentum ) :
  orbital_momentum_( orbitalAngularMomentum ) {}
