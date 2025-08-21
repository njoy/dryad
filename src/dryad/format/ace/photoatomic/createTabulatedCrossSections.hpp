#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATETABULATEDCROSSSECTIONS
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATETABULATEDCROSSSECTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/TabulatedCrossSection.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create TabulatedCrossSection instances for photoatomic data
   *
   *  @param[in] table   the ace table
   */
  std::vector< TabulatedCrossSection >
  createTabulatedCrossSections( const ACEtk::PhotoatomicTable& table ) {

    std::vector< TabulatedCrossSection > xs;

    // photoatomic data is stored as log values, except when the value
    // is exactly 0 (in which case it is zero)
    auto convertEnergy = [] ( auto&& energy ) {

      return energy == 0. ? energy : std::exp( energy ) * 1e+6;
    };
    auto convertValue = [] ( auto&& value ) {

      return value == 0. ? value : std::exp( value );
    };

    auto energies = createVector( table.principalCrossSectionBlock().energies() );
    std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );

    std::vector< double > total;

    // coherent scattering - MT502
    auto coherent = createVector( table.principalCrossSectionBlock().coherent() );
    std::transform( coherent.begin(), coherent.end(), coherent.begin(), convertValue );
    total = coherent;
    xs.emplace_back( energies, std::move( coherent ) );

    // coherent scattering - MT504
    auto incoherent = createVector( table.principalCrossSectionBlock().incoherent() );
    std::transform( incoherent.begin(), incoherent.end(), incoherent.begin(), convertValue );
    std::transform( incoherent.begin(), incoherent.end(), total.begin(), total.begin(), std::plus<>() );
    xs.emplace_back( energies, std::move( incoherent ) );

    // pair production - MT516 (sum of MT515 and MT517)
    auto pair = createVector( table.principalCrossSectionBlock().pairproduction() );
    std::transform( pair.begin(), pair.end(), pair.begin(), convertValue );
    std::transform( pair.begin(), pair.end(), total.begin(), total.begin(), std::plus<>() );
    xs.emplace_back( energies, std::move( pair ) );

    // photoelectric - MT522 (sum of MT534 and up)
    auto photoelectric = createVector( table.principalCrossSectionBlock().photoelectric() );
    std::transform( photoelectric.begin(), photoelectric.end(), photoelectric.begin(), convertValue );
    std::transform( photoelectric.begin(), photoelectric.end(), total.begin(), total.begin(), std::plus<>() );
    xs.emplace_back( energies, std::move( photoelectric ) );

    // total - MT501
    xs.emplace( xs.begin(), energies, std::move( total ) );

    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // subshell photoelectric - MT534 and up
        auto subshell = createVector( table.photoelectricCrossSectionBlock()->photoelectric( index ) );
        std::transform( subshell.begin(), subshell.end(), subshell.begin(), convertValue );
        xs.emplace_back( energies, std::move( subshell ) );
      }
    }

    return xs;
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
