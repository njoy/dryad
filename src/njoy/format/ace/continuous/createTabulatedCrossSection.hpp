#ifndef NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATETABULATEDCROSSSECTION
#define NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATETABULATEDCROSSSECTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/TabulatedCrossSection.hpp"
#include "ACEtk/PhotonuclearTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace continuous {

  /**
   *  @brief Create an TabulatedCrossSection instance
   *
   *  @param[in] table   the ace table
   *  @param[in] index   the reaction index in the ACE file
   */
  template < typename Table >
  TabulatedCrossSection
  createTabulatedCrossSection( const Table& table, std::size_t index ) {

    // function to convert MeV to eV
    auto convertEnergy = [] ( auto&& energy ) {

      return energy * constants::mega;
    };

    // raw data
    auto energies = createVector( table.principalCrossSectionBlock().energies() );
    auto values = createVector( table.crossSectionBlock().crossSectionData( index ).crossSections() );

    // erase initial energies if needed and convert energies
    energies.erase( energies.begin(), energies.begin() + energies.size() - values.size() );
    std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );

    // return cross section (ACE cross sections are always linearised)
    return TabulatedCrossSection( std::move( energies ), std::move( values ) );
  }

} // continuous namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
