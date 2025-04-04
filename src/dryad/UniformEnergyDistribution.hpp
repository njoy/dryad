#ifndef NJOY_DRYAD_UNIFORMENERGYDISTRIBUTION
#define NJOY_DRYAD_UNIFORMENERGYDISTRIBUTION

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
   *  @brief A uniform or equally probably anergy distribution
   */
  class UniformEnergyDistribution : protected base::UniformDistribution {

    /* fields */

    /* auxiliary functions */

  public:

    /* type aliases */

    /* constructor */

    #include "dryad/UniformEnergyDistribution/src/ctor.hpp"

    /* methods */

    using UniformDistribution::type;

    /**
     *  @brief Return the energy values for the distribution
     */
    const std::vector< double >& energies() const noexcept {

      return this->values();
    }

    /**
     *  @brief Return the number of discrete energies or intervals
     */
    std::size_t numberEnergies() const noexcept {

      return this->number();
    }

    /**
     *  @brief Return the average energy defined by the distribution
     */
    double averageEnergy() const noexcept {

      return this->mean();
    }
  };

} // dryad namespace
} // njoy namespace

#endif
