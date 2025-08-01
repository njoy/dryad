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
   *  @brief A uniform or equally probably energy distribution
   */
  class UniformEnergyDistribution : protected base::UniformDistribution {

    /* fields */

    /* auxiliary functions */

  public:

    /* type aliases */

    using XType = double;
    using YType = double;

    /* constructor */

    #include "dryad/UniformEnergyDistribution/src/ctor.hpp"

    /* methods */

    using UniformDistribution::type;

    /**
     *  @brief Return the energy values for the distribution
     */
    const std::vector< double >& energies() const {

      return this->values();
    }

    /**
     *  @brief Return the number of discrete energies or intervals
     */
    std::size_t numberEnergies() const {

      return this->number();
    }

    /**
     *  @brief Return the average energy defined by the distribution
     */
    double averageEnergy() const {

      return this->mean();
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const UniformEnergyDistribution& right ) const {

      return base::UniformDistribution::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const UniformEnergyDistribution& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
