#ifndef NJOY_FORMAT_ACE_READ_ELECTROATOMIC_CREATETABULATEDCROSSSECTIONS
#define NJOY_FORMAT_ACE_READ_ELECTROATOMIC_CREATETABULATEDCROSSSECTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/TabulatedCrossSection.hpp"
#include "njoy/format/createVector.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace electroatomic {

  /**
   *  @brief Create TabulatedCrossSection instances for electroatomic data
   *
   *  @param[in] table   the ace table
   */
  inline std::vector< dryad::TabulatedCrossSection >
  createTabulatedCrossSections( const ACEtk::PhotoatomicTable& table ) {

    std::vector< dryad::TabulatedCrossSection > xs;

    auto convertEnergy = [] ( auto&& energy ) {

      return energy * constants::mega;
    };

    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      auto energies = createVector( table.electronCrossSectionBlock()->energies() );
      std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );

      // total - MT501
      auto total = createVector( table.electronCrossSectionBlock()->total() );
      xs.emplace_back( energies, std::move( total ) );

      // ionisation - MT522
      auto ionisation = createVector( table.electronCrossSectionBlock()->totalElectroionisation() );
      xs.emplace_back( energies, std::move( ionisation ) );

      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // large angle elastic - MT525
        auto angle = createVector( table.electronCrossSectionBlock()->elastic() );
        xs.emplace_back( energies, std::move( angle ) );

        // total elastic - MT526
        auto elastic = createVector( table.electronElasticCrossSectionBlock()->total() );
        xs.emplace_back( energies, std::move( elastic ) );
      }
      else {

        // elastic - MT526
        auto elastic = createVector( table.electronCrossSectionBlock()->elastic() );
        xs.emplace_back( energies, std::move( elastic ) );
      }

      // bremsstrahlung - MT527
      auto bremsstrahlung = createVector( table.electronCrossSectionBlock()->bremsstrahlung() );
      xs.emplace_back( energies, std::move( bremsstrahlung ) );

      // excitation - MT528
      auto excitation = createVector( table.electronCrossSectionBlock()->excitation() );
      xs.emplace_back( energies, std::move( excitation ) );

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // subshell ionisation - MT534 and up
        auto subshell = createVector( table.electronCrossSectionBlock()->electroionisation( index ) );
        xs.emplace_back( energies, std::move( subshell ) );
      }

      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // elastic deficit
        std::vector< double > deficit = xs[3].values();
        std::transform( deficit.begin(), deficit.end(), xs[2].values().begin(), deficit.begin(), std::minus<>() );
        xs.emplace_back( energies, std::move( deficit ) );
      }
    }

    return xs;
  }

} // electroatomic namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
