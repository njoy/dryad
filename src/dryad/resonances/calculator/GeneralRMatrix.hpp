#ifndef NJOY_DRYAD_RESONANCES_CALCULATOR_GENERALRMATRIX
#define NJOY_DRYAD_RESONANCES_CALCULATOR_GENERALRMATRIX

// system includes

// other includes

namespace njoy {
namespace dryad {
namespace resonances {
namespace calculator {

  /**
   *  @class
   *  @brief A matrix and cross section calculator for the general R-matrix formalism
   */
  class GeneralRMatrix {

    /* type aliases */

    /* fields */

    /* auxiliary functions */

  public:

    /* constructor */

    /* methods */

    void crossSections( double energy,
                        const std::vector< Channel >& channels,
                        const ResonanceTable& table,
                        std::map< id::ReactionID, double >& xs ) {


    }
  };

} // calculator namespace
} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
