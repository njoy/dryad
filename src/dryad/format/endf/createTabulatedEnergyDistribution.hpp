#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDENERGYDISTRIBUTION
#define NJOY_DRYAD_FORMAT_ENDF_CREATETABULATEDENERGYDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/TabulatedEnergyDistribution.hpp"
#include "ENDFtk/section/6.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a TabulatedEnergyDistribution from a parsed ENDF MF6 LAW = 1
   *         LegendreCoefficients entry
   */
  TabulatedEnergyDistribution
  createTabulatedEnergyDistribution(
    const ENDFtk::section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients& distribution ) {

    //! @todo interpolants and boundaries on LegendreCoefficients for interpolation on
    //!       outgoing energy?
    //! @todo what is the interpolation type over the outgoing energy axis?

    try {

      auto energies = createVector( distribution.energies() );
      auto values = createVector( distribution.totalEmissionProbabilities() );
      return TabulatedEnergyDistribution( std::move( energies ), std::move( values ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an energy distribution table" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedEnergyDistribution from a parsed ENDF MF26 LAW = 1
   *         LegendreCoefficients entry (with NA = 0)
   */
  TabulatedEnergyDistribution
  createTabulatedEnergyDistribution(
    const ENDFtk::section::Type< 26 >::ContinuumEnergyAngle::LegendreCoefficients& distribution ) {

    if ( distribution.numberAngularParameters() != 0 ) {

      Log::error( "MF26 LAW = 1 data must be fully isotropic, found NA = {}",
                  distribution.numberAngularParameters() );
      throw std::exception();
    }

    //! @todo interpolants and boundaries on LegendreCoefficients for interpolation on
    //!       outgoing energy?
    //! @todo what is the interpolation type over the outgoing energy axis?

    try {

      auto energies = createVector( distribution.energies() );
      auto values = createVector( distribution.totalEmissionProbabilities() );
      return TabulatedEnergyDistribution( std::move( energies ), std::move( values ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an energy distribution table" );
      throw;
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
