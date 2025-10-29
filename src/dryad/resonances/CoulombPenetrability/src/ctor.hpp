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
 *  @param orbitalMomentum   the value of the orbital momentum
 */
CoulombPenetrability( unsigned int orbitalMomentum ) :
  orbital_momentum_( orbitalMomentum ) {}
