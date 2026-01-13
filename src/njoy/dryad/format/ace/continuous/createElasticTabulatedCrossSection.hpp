#ifndef NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATEELASTICTABULATEDCROSSSECTION
#define NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATEELASTICTABULATEDCROSSSECTION

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
   *  @brief Create an TabulatedCrossSection instance for elastic
   *
   *  @param[in] table   the ace table
   */
  template < typename Table >
  TabulatedCrossSection
  createElasticTabulatedCrossSection( const Table& table ) {

    // function to convert MeV to eV
    auto convertEnergy = [] ( auto&& energy ) {

      return energy * constants::mega;
    };

    // raw data
    auto energies = createVector( table.principalCrossSectionBlock().energies() );
    std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );
    auto values = createVector( table.principalCrossSectionBlock().elastic() );

    // return cross section (ACE cross sections are always linearised)
    return TabulatedCrossSection( std::move( energies ), std::move( values ) );
  }

} // continuous namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
