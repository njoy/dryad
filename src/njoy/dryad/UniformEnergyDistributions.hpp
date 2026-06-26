#ifndef NJOY_DRYAD_UNIFORMENERGYDISTRIBUTIONS
#define NJOY_DRYAD_UNIFORMENERGYDISTRIBUTIONS

// system includes

// other includes
#include "njoy/dryad/base/GridDistributions.hpp"
#include "njoy/dryad/UniformEnergyDistribution.hpp"
#include "njoy/dryad/TabulatedAverageEnergy.hpp"

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

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    UniformEnergyDistributions() = default;

    UniformEnergyDistributions( const UniformEnergyDistributions& ) = default;
    UniformEnergyDistributions( UniformEnergyDistributions&& ) = default;

    UniformEnergyDistributions& operator=( const UniformEnergyDistributions& ) = default;
    UniformEnergyDistributions& operator=( UniformEnergyDistributions&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param grid            the grid values
     *  @param distributions   the associated distributions
     *  @param boundaries      the boundaries of the interpolation regions
     *  @param interpolants    the interpolation types of the interpolation regions
     */
    UniformEnergyDistributions( std::vector< double > grid,
                                std::vector< UniformEnergyDistribution > distributions,
                                std::vector< std::size_t > boundaries,
                                std::vector< InterpolationType > interpolants ) :
      Parent( std::move( grid ), std::move( distributions ),
              std::move( boundaries ), std::move( interpolants ) ) {}

    /**
     *  @brief Constructor for energy distributions using a single interpolation zone
     *
     *  @param grid            the grid values
     *  @param distributions   the associated distributions
     *  @param interpolant     the interpolation type of the data (default lin-lin)
     */
    UniformEnergyDistributions( std::vector< double > grid,
                                std::vector< UniformEnergyDistribution > distributions,
                                InterpolationType interpolant = InterpolationType::LinearLinear ) :
      Parent( std::move( grid ), std::move( distributions ), interpolant ) {}

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
