#ifndef NJOY_FORMAT_ENDF_READ_CREATETABULATEDENERGYDISTRIBUTION
#define NJOY_FORMAT_ENDF_READ_CREATETABULATEDENERGYDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedEnergyDistribution.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "ENDFtk/section/6.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a TabulatedEnergyDistribution from a parsed ENDF MF6 LAW = 1
   *         LegendreCoefficients entry
   */
  inline dryad::TabulatedEnergyDistribution
  createTabulatedEnergyDistribution(
    const ENDFtk::section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients& distribution,
    const dryad::InterpolationType& interpolant,
    bool normalise ) {

    try {

      auto energies = createVector( distribution.energies() );
      auto values = createVector( distribution.totalEmissionProbabilities() );
      return dryad::TabulatedEnergyDistribution( std::move( energies ), std::move( values ),
                                                 interpolant, normalise );
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
  inline dryad::TabulatedEnergyDistribution
  createTabulatedEnergyDistribution(
    const ENDFtk::section::Type< 26 >::ContinuumEnergyAngle::LegendreCoefficients& distribution,
    const dryad::InterpolationType& interpolant,
    bool normalise ) {

    if ( distribution.numberAngularParameters() != 0 ) {

      Log::error( "MF26 LAW = 1 data must be fully isotropic, found NA = {}",
                  distribution.numberAngularParameters() );
      throw std::exception();
    }

    try {

      auto energies = createVector( distribution.energies() );
      auto values = createVector( distribution.totalEmissionProbabilities() );
      return dryad::TabulatedEnergyDistribution( std::move( energies ), std::move( values ),
                                                 interpolant, normalise );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an energy distribution table" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
