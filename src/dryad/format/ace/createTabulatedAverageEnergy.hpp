#ifndef NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDAVERAGEENERGY
#define NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDAVERAGEENERGY

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/TabulatedAverageEnergy.hpp"
#include "ACEtk/electron/ExcitationBlock.hpp"
#include "ACEtk/electron/BremsstrahlungBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create a TabulatedAverageEnergy from an ExcitationBlock
   */
  TabulatedAverageEnergy
  createTabulatedAverageEnergy( const njoy::ACEtk::electron::ExcitationBlock& block ) {

    try {

      auto convertEnergy = [] ( auto&& energy ) {

        return energy * 1e+6;
      };

      Log::info( "Reading average energy data" );
      auto energies = createVector( block.energies() );
      auto values = createVector( block.excitationEnergyLoss() );
      std::transform( energies.begin(), energies.end(), values.begin(), values.begin(),
                      [] ( auto&& left, auto&& right ) { return ( left - right ) * 1e+6; } );
      std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );
      std::vector< std::size_t > boundaries = { energies.size() - 1 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
      return TabulatedAverageEnergy(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an average reaction product energy table" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedAverageEnergy from an ExcitationBlock
   */
  TabulatedAverageEnergy
  createTabulatedAverageEnergy( const njoy::ACEtk::electron::BremsstrahlungBlock& block ) {

    try {

      auto convertEnergy = [] ( auto&& energy ) {

        return energy * 1e+6;
      };

      Log::info( "Reading average energy data" );
      auto energies = createVector( block.energies() );
      auto values = createVector( block.energyAfterBremsstrahlung() );
      std::transform( energies.begin(), energies.end(), values.begin(), values.begin(),
                      [] ( auto&& left, auto&& right ) { return ( left - right ) * 1e+6; } );
      std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );
      std::vector< std::size_t > boundaries = { energies.size() - 1 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
      return TabulatedAverageEnergy(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an average reaction product energy table" );
      throw;
    }
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
