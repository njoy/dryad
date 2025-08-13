#ifndef NJOY_DRYAD_UNIFORMANGULARDISTRIBUTIONS
#define NJOY_DRYAD_UNIFORMANGULARDISTRIBUTIONS

// system includes

// other includes
#include "dryad/base/GridDistributions.hpp"
#include "dryad/UniformEnergyDistribution.hpp"
#include "dryad/TabulatedAverageEnergy.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Energy distribution data given using uniform distributions
   */
  class UniformEnergyDistributions :
      protected base::GridDistributions< UniformEnergyDistribution > {

    /* type aliases */
    using Parent = base::GridDistributions< UniformEnergyDistribution >;

  public:

    /* constructor */

    #include "dryad/UniformEnergyDistributions/src/ctor.hpp"

    /* methods */

    using Parent::grid;
    using Parent::distributions;
    using Parent::boundaries;
    using Parent::interpolants;
    using Parent::numberPoints;
    using Parent::numberRegions;

    // there is no call operator on the uniform distribution, so we do not expose operator()

    /**
     *  @brief Return the average energy values
     */
    TabulatedAverageEnergy averageEnergies() const {

      std::vector< double > energies;
      energies.reserve( this->numberPoints() );
      std::transform( this->distributions().begin(), this->distributions().end(),
                      std::back_inserter( energies ),
                      [] ( auto&& distribution ) { return distribution.averageEnergy(); } );
      return TabulatedAverageEnergy( this->grid(), std::move( energies ),
                                     this->boundaries(),
                                     this->interpolants() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const UniformEnergyDistributions& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const UniformEnergyDistributions& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
