#ifndef NJOY_DRYAD_TABULATEDENERGYDISTRIBUTIONS
#define NJOY_DRYAD_TABULATEDENERGYDISTRIBUTIONS

// system includes

// other includes
#include "dryad/base/GridDistributions.hpp"
#include "dryad/TabulatedEnergyDistribution.hpp"
#include "dryad/TabulatedAverageEnergy.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Energy distribution data given using tables
   */
  class TabulatedEnergyDistributions :
      protected base::GridDistributions< TabulatedEnergyDistribution > {

    /* type aliases */
    using Parent = base::GridDistributions< TabulatedEnergyDistribution >;

  public:

    /* constructor */

    #include "dryad/TabulatedEnergyDistributions/src/ctor.hpp"

    /* methods */

    using Parent::grid;
    using Parent::distributions;
    using Parent::boundaries;
    using Parent::interpolants;
    using Parent::numberPoints;
    using Parent::numberRegions;
    using Parent::operator();

    /**
     *  @brief Return the average energy values
     */
    TabulatedAverageEnergy averageEnergies() const noexcept {

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
     *  @brief Return linearised energy distributions
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedEnergyDistributions linearise( ToleranceConvergence tolerance = {} ) const {

      std::vector< TabulatedEnergyDistribution > distributions;
      distributions.reserve( this->numberPoints() );
      std::transform( this->distributions().begin(), this->distributions().end(),
                      std::back_inserter( distributions ),
                      [&tolerance] ( auto&& distribution )
                                   { return distribution.linearise( tolerance ); } );
      return TabulatedEnergyDistributions( this->grid(), std::move( distributions ),
                                           this->boundaries(), this->interpolants() );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
