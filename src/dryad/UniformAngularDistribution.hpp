#ifndef NJOY_DRYAD_UNIFORMANGULARDISTRIBUTION
#define NJOY_DRYAD_UNIFORMANGULARDISTRIBUTION

// system includes
#include <algorithm>
#include <numeric>
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/base/UniformDistribution.hpp"
#include "dryad/UniformDistributionType.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A uniform or equally probably angular distribution
   *
   *  The uniform distribution can be defined for discrete values
   *  (e.g. as used in inelastic thermal scattering ACE files) or
   *  cosine intervals (e.g. as used in older incident neutron ACE
   *  files).
   */
  class UniformAngularDistribution : protected base::UniformDistribution {

    /* fields */

    /* auxiliary functions */

  public:

    /* type aliases */

    /* constructor */

    #include "dryad/UniformAngularDistribution/src/ctor.hpp"

    /* methods */

    using UniformDistribution::type;

    /**
     *  @brief Return the cosine values for the distribution
     */
    const std::vector< double >& cosines() const noexcept {

      return this->values();
    }

    /**
     *  @brief Return the number of discrete cosines or intervals
     */
    std::size_t numberCosines() const noexcept {

      return this->number();
    }

    /**
     *  @brief Return the average cosine defined by the distribution
     */
    double averageCosine() const noexcept {

      return this->mean();
    }
  };

} // dryad namespace
} // njoy namespace

#endif
