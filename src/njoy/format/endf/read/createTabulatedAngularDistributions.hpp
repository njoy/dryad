#ifndef NJOY_FORMAT_ENDF_READ_CREATETABULATEDANGULARDISTRIBUTIONS
#define NJOY_FORMAT_ENDF_READ_CREATETABULATEDANGULARDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/TabulatedAngularDistributions.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "njoy/format/endf/read/createTabulatedAngularDistribution.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a TabulatedAngularDistributions instance from a parsed
   *         ENDF MF4 TabulatedDistributions
   *
   *  @param[in] distribution   the parsed ENDF tabulated distributions
   *  @param[in] normalise      the flag to indicate whether or not distributions
   *                            need to be normalised
   */
  inline dryad::TabulatedAngularDistributions
  createTabulatedAngularDistributions(
      const ENDFtk::section::Type< 4 >::TabulatedDistributions& distribution,
      bool normalise ) {

    try {

      auto energies = createVector( distribution.incidentEnergies() );
      std::vector< dryad::TabulatedAngularDistribution > distributions;
      distributions.reserve( energies.size() );
      for ( auto&& table : distribution.angularDistributions() ) {

        distributions.emplace_back( createTabulatedAngularDistribution( table, normalise ) );
      }
      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return dryad::TabulatedAngularDistributions(
               std::move( energies ), std::move( distributions ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an average reaction product energy table" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedAngularDistributions instance from a parsed
   *         MF6 DiscreteTwoBodyScattering component
   *
   *  @param[in] distribution   the parsed ENDF tabulated distributions
   *  @param[in] normalise      the flag to indicate whether or not distributions
   *                            need to be normalised
   */
  inline dryad::TabulatedAngularDistributions
  createTabulatedAngularDistributions(
      const ENDFtk::section::Type< 26 >::DiscreteTwoBodyScattering& distribution,
      bool normalise ) {

    try {

      auto energies = createVector( distribution.incidentEnergies() );
      std::vector< dryad::TabulatedAngularDistribution > distributions;
      distributions.reserve( energies.size() );
      for ( auto&& table : distribution.distributions() ) {

        distributions.emplace_back( createTabulatedAngularDistribution( table, normalise ) );
      }
      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return dryad::TabulatedAngularDistributions(
               std::move( energies ), std::move( distributions ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an average reaction product energy table" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
