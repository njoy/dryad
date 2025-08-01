#ifndef NJOY_DRYAD_COVARIANCE_LINEARCOMBINATIONCOVARIANCE
#define NJOY_DRYAD_COVARIANCE_LINEARCOMBINATIONCOVARIANCE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ReactionID.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief Covariance data for a reaction defined as a linear
   *         combination of other reactions' covariance data
   */
  class LinearCombinationCovariance {

    /* fields */
    double lower_;
    double upper_;
    std::vector< id::ReactionID > reactions_;
    std::vector< double > coefficients_;

    /* auxiliary function */
    #include "dryad/covariance/LinearCombinationCovariance/src/verifySize.hpp"

  public:

    /* constructor */
    #include "dryad/covariance/LinearCombinationCovariance/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return this->lower_;
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return this->upper_;
    }

    /**
     *  @brief Return the reactions in the linear combination
     */
    const std::vector< id::ReactionID >& reactions() const {

      return this->reactions_;
    }

    /**
     *  @brief Return the coefficients for the linear combination
     */
    const std::vector< double >& coefficients() const {

      return this->coefficients_;
    }

    /**
     *  @brief Return the number of reactions in the linear combination
     */
    std::size_t numberReactions() const {

      return this->reactions().size();
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
