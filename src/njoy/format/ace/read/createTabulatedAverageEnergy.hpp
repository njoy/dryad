#ifndef NJOY_FORMAT_ACE_READ_CREATETABULATEDAVERAGEENERGY
#define NJOY_FORMAT_ACE_READ_CREATETABULATEDAVERAGEENERGY

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/TabulatedAverageEnergy.hpp"
#include "njoy/format/createVector.hpp"
#include "ACEtk/electroatomic/ExcitationBlock.hpp"
#include "ACEtk/electroatomic/BremsstrahlungBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {

  /**
   *  @brief Create a TabulatedAverageEnergy from an ExcitationBlock
   *
   *  @param[in] block   the electroatomic excitation energy block
   */
  inline dryad::TabulatedAverageEnergy
  createTabulatedAverageEnergy(
      const njoy::ACEtk::electroatomic::ExcitationBlock& block ) {

    try {

      auto convertEnergy = [] ( auto&& energy ) {

        return energy * constants::mega;
      };
      auto convertEnergyDifference = [] ( auto&& left, auto&& right ) {

        return ( left - right ) * constants::mega;
      };

      Log::info( "Reading average energy data" );
      auto energies = createVector( block.energies() );
      auto values = createVector( block.excitationEnergyLoss() );
      std::transform( energies.begin(), energies.end(), values.begin(), values.begin(),
                      convertEnergyDifference );
      std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );
      std::vector< std::size_t > boundaries = { energies.size() - 1 };
      std::vector< dryad::InterpolationType > interpolants = { dryad::InterpolationType::LinearLinear };
      return dryad::TabulatedAverageEnergy(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an average reaction product energy table" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedAverageEnergy from an BremsstrahlungBlock
   *
   *  @param[in] block   the electroatomic Bremsstrahlung energy block
   */
  inline dryad::TabulatedAverageEnergy
  createTabulatedAverageEnergy(
      const njoy::ACEtk::electroatomic::BremsstrahlungBlock& block ) {

    try {

      auto convertEnergy = [] ( auto&& energy ) {

        return energy * constants::mega;
      };
      auto convertEnergyDifference = [] ( auto&& left, auto&& right ) {

        return ( left - right ) * constants::mega;
      };

      Log::info( "Reading average energy data" );
      auto energies = createVector( block.energies() );
      auto values = createVector( block.energyAfterBremsstrahlung() );
      std::transform( energies.begin(), energies.end(), values.begin(), values.begin(),
                      convertEnergyDifference );
      std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );
      std::vector< std::size_t > boundaries = { energies.size() - 1 };
      std::vector< dryad::InterpolationType > interpolants = { dryad::InterpolationType::LinearLinear };
      return dryad::TabulatedAverageEnergy(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an average reaction product energy table" );
      throw;
    }
  }

} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
