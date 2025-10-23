/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
HardSpherePhaseShift() = default;

HardSpherePhaseShift( const HardSpherePhaseShift& ) = default;
HardSpherePhaseShift( HardSpherePhaseShift&& ) = default;

HardSpherePhaseShift& operator=( const HardSpherePhaseShift& ) = default;
HardSpherePhaseShift& operator=( HardSpherePhaseShift&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param orbitalAngularMomentum   the value of the orbital angular momentum
 */
HardSpherePhaseShift( unsigned int orbitalAngularMomentum ) :
  ratio_( generateFunction( orbitalAngularMomentum ) ),
  orbital_momentum_( orbitalAngularMomentum ) {}
