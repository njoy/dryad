#ifndef NJOY_DRYAD_MULTIENERGYDISTRIBUTIONS
#define NJOY_DRYAD_MULTIENERGYDISTRIBUTIONS

// system includes

// other includes

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The energy distribution is composed of partial distributions with
   *         an associated probability
   */
  class MultiEnergyDistributions {

  public:

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const MultiEnergyDistributions& right ) const {

      return true;
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const MultiEnergyDistributions& right ) const {

      return false;
    }
  };

} // dryad namespace
} // njoy namespace

#endif
