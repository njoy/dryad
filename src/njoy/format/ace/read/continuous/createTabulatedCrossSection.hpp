#ifndef NJOY_FORMAT_ACE_READ_CONTINUOUS_CREATETABULATEDCROSSSECTION
#define NJOY_FORMAT_ACE_READ_CONTINUOUS_CREATETABULATEDCROSSSECTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/TabulatedCrossSection.hpp"
#include "njoy/format/createVector.hpp"
#include "ACEtk/PhotonuclearTable.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace continuous {

  /**
   *  @brief Create an TabulatedCrossSection instance
   *
   *  @param[in] table   the ace table
   *  @param[in] index   the reaction index in the ACE file
   */
  template < typename Table >
  dryad::TabulatedCrossSection
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
    return dryad::TabulatedCrossSection( std::move( energies ), std::move( values ) );
  }

} // continuous namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
