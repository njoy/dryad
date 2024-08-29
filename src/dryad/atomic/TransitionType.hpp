#ifndef NJOY_DRYAD_ATOMIC_TRANSITIONTYPE
#define NJOY_DRYAD_ATOMIC_TRANSITIONTYPE

// system includes

// other includes

namespace njoy {
namespace dryad {
namespace atomic {

/**
 *  @enum
 *  @brief The type of transition in an atomic relaxation
 *
 *  This enum is used to differentiate between the radiative and non-radiative
 *  transition types that can occur.
 */
enum class TransitionType : short {

  Radiative,    /**< The transition is radiative (emission of a photon) */
  NonRadiative  /**< The transition is non-radiative (emission of an electron */
};

} // atomic namespace
} // dryad namespace
} // njoy namespace

#endif
