#ifndef NJOY_DRYAD_RESONANCES_FORMALISM
#define NJOY_DRYAD_RESONANCES_FORMALISM

// system includes

// other includes

namespace njoy {
namespace dryad {
namespace resonances {

/**
 *  @enum
 *  @brief The resonance formalism
 *
 *  This enum is used to differentiate between formalisms in resonance reconstruction.
 */
enum class Formalism : short {

  /**
   *  The Reich-Moore formalism using a single eliminated capture channel
   */
  ReichMoore = 1,
  /**
   *  The general R-matrix formalism
   */
  GeneralRMatrix = 2
};

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
