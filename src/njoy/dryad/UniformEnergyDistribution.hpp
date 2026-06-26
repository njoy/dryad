#ifndef NJOY_DRYAD_UNIFORMENERGYDISTRIBUTION
#define NJOY_DRYAD_UNIFORMENERGYDISTRIBUTION

// system includes
#include <algorithm>
#include <numeric>
#include <vector>

// other includes
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/dryad/base/UniformDistribution.hpp"
#include "njoy/dryad/UniformDistributionType.hpp"

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

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    UniformEnergyDistribution() = default;

    UniformEnergyDistribution( const UniformEnergyDistribution& ) = default;
    UniformEnergyDistribution( UniformEnergyDistribution&& ) = default;

    UniformEnergyDistribution& operator=( const UniformEnergyDistribution& ) = default;
    UniformEnergyDistribution& operator=( UniformEnergyDistribution&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param energies   the energy values
     *  @param type       the uniform distribution type
     */
    UniformEnergyDistribution( std::vector< double > energies,
                               UniformDistributionType type ) :
      UniformDistribution( std::move( energies ), std::move( type ) ) {}

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
