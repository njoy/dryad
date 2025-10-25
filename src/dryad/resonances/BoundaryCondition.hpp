#ifndef NJOY_DRYAD_RESONANCES_BOUNDARYCONDITION
#define NJOY_DRYAD_RESONANCES_BOUNDARYCONDITION

// system includes

// other includes

namespace njoy {
namespace dryad {
namespace resonances {

/**
 *  @enum
 *  @brief The boundary condition options
 *
 *  This enum is used to differentiate between boundary condition option in
 *  resonance reconstruction.
 */
enum class BoundaryCondition : short {

  /**
   *  The boundary condition eliminates the energy dependent shift factor so
   *  that L = S - B + iP = iP
   */
  ShiftFactor = 1,
  /**
   *  The boundary condition is constant (often equal to the orbital angular momentum)
   */
  Constant = 2
};

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
