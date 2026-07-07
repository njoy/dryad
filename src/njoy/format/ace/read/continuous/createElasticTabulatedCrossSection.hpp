#ifndef NJOY_FORMAT_ACE_READ_CONTINUOUS_CREATEELASTICTABULATEDCROSSSECTION
#define NJOY_FORMAT_ACE_READ_CONTINUOUS_CREATEELASTICTABULATEDCROSSSECTION

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
   *  @brief Create an TabulatedCrossSection instance for elastic
   *
   *  @param[in] table   the ace table
   */
  template < typename Table >
  dryad::TabulatedCrossSection
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
    return dryad::TabulatedCrossSection( std::move( energies ), std::move( values ) );
  }

} // continuous namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
