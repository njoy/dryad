#ifndef NJOY_DRYAD_COVARIANCE_VARIANCESCALING
#define NJOY_DRYAD_COVARIANCE_VARIANCESCALING

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/covariance/ScalingType.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief Variance scaling information
   *
   *  Some ENDF evaluations provide variance scaling information for cross section
   *  covariances. Each factor value for a given group characterizes an uncorrelated
   *  contribution to the absolute variance of the cross section averaged over any
   *  energy subgroup that includes a portion of the energy interval over which the
   *  factor is defined.
   */
  class VarianceScaling {

    /* fields - variance scaling group structure and factors */
    std::vector< double > energies_;
    std::vector< double > factors_;

    /* fields - scaling type */
    ScalingType type_;

    /* auxiliary functions */
    #include "dryad/covariance/VarianceScaling/src/verifySize.hpp"

  public:

    /* constructor */
    #include "dryad/covariance/VarianceScaling/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the energy group boundaries
     */
    const std::vector< double >& energies() const {

      return this->energies_;
    }

    /**
     *  @brief Return the scaling factors
     */
    const std::vector< double >& factors() const {

      return this->factors_;
    }

    /**
     *  @brief Return the number of energy groups
     */
    std::size_t numberGroups() const noexcept {

      return this->energies().size() - 1;
    }

    /**
     *  @brief Return the scaling procedure type
     */
    const ScalingType& type() const noexcept {

      return this->type_;
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
