/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CoulombPenetrability() = default;

CoulombPenetrability( const CoulombPenetrability& ) = default;
CoulombPenetrability( CoulombPenetrability&& ) = default;

CoulombPenetrability& operator=( const CoulombPenetrability& ) = default;
CoulombPenetrability& operator=( CoulombPenetrability&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param orbitalAngularMomentum   the value of the orbital angular momentum
 */
CoulombPenetrability( unsigned int orbitalAngularMomentum ) :
  orbital_momentum_( orbitalAngularMomentum ) {}
