#ifndef NJOY_DRYAD_ISOTROPICANGULARDISTRIBUTIONS
#define NJOY_DRYAD_ISOTROPICANGULARDISTRIBUTIONS

// system includes

// other includes
#include "njoy/dryad/base/GridDistributions.hpp"
#include "njoy/dryad/LegendreAngularDistribution.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief All angular distributions are isotropic
   */
  class IsotropicAngularDistributions {

  public:

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const IsotropicAngularDistributions& ) const {

      return true;
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const IsotropicAngularDistributions& ) const {

      return false;
    }
  };

} // dryad namespace
} // njoy namespace

#endif
