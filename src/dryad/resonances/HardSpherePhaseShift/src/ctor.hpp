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
 *  @param orbitalMomentum   the value of the orbital momentum
 */
HardSpherePhaseShift( unsigned int orbitalMomentum ) :
  ratio_( generateFunction( orbitalMomentum ) ),
  orbital_momentum_( orbitalMomentum ) {}
