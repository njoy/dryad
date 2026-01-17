#ifndef NJOY_DRYAD_EXTERNAL_COMPTONPROFILES
#define NJOY_DRYAD_EXTERNAL_COMPTONPROFILES

// system includes
#include <vector>
#include <vector>

// other includes
#include "njoy/dryad/TabulatedComptonProfile.hpp"

namespace njoy {
namespace dryad {
namespace external {

  /**
   *  @class
   *  @brief Compton profile models
   *
   *  Compton profiles are currently not available in standard evaluated nuclear data
   *  files. The ComptonProfiles class is basically going to contain factory functions
   *  to produce Compton profiles for a given atom, either based on external data or
   *  possibly model calculations.
   *
   *  Currently we only have tabulated data based on Biggs, Mendelsohn and Mann
   *  calculated profiles from the following reference:
   *    F. Biggs, L. B. Mendelsohn, J. B. Mann
   */
  class ComptonProfiles {

    /* static fields */

    static inline const std::vector< double > biggs_mendelsohn_mann_momentum = {

        0.00,  0.05,  0.10,  0.15,  0.20,  0.30,  0.40,  0.50,  0.60,  0.70,
        0.80,  1.00,  1.20,  1.40,  1.60,  1.80,  2.00,  2.40,  3.00,  4.00,
        5.00,  6.00,  7.00,  8.00, 10.00, 15.00, 20.00, 30.00, 40.00, 60.00,
      100.00
    };

  public:

    /* constructor */

    /* methods */

    /**
     *  @brief Return Biggs, Mendelsohn and Mann Compton profiles for a given z number
     */
    static std::vector< TabulatedComptonProfile >
    biggsMendelsohnMannProfiles(  ) {

      return this->id_;
    }
  };

} // external namespace
} // dryad namespace
} // njoy namespace

#endif
