#ifndef NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATETABULATEDCOMPTONPROFILES
#define NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATETABULATEDCOMPTONPROFILES

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/external/ComptonProfiles.hpp"
#include "njoy/format/ace/read/photoatomic/createTabulatedComptonProfile.hpp"
#include "ACEtk/photoatomic/ComptonProfileBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace photoatomic {

  /**
   *  @brief Create TabulatedComptonProfile instances from ACE data
   *
   *  This function assumes that the data is from Biggs, Mendelsihn and Mann.
   *
   *  The ACE file does not contain information on the shell identifier for each
   *  profile, so we use the ones from the external::ComptonProfiles class.
   *
   *  @param[in] block   the Compton profile block
   *  @param[in] z       the z number of the atom
   */
  inline std::vector< dryad::TabulatedComptonProfile >
  createTabulatedComptonProfiles(
      const njoy::ACEtk::photoatomic::ComptonProfileBlock& block,
      int z ) {

    // the shells for this z number
    std::vector< dryad::id::ElectronSubshellID > identifiers =
    dryad::external::ComptonProfiles::biggsMendelsohnMannSubshellIdentifiers( z );
    if ( identifiers.size() < block.numberElectronShells() ) {

      // ENDF/B-VIII.1 Iridium is missing 6s1/2 so we should only error out when the
      // number of Biggs identifiers is smaller than the number of profiles in the
      // ACE files
      Log::error( "Error encountered while creating a tabulated Compton profiles" );
      throw std::exception();
    }

    // read the profiles
    std::vector< dryad::TabulatedComptonProfile > profiles;
    for ( std::size_t i = 0; i < block.numberElectronShells(); ++i ) {

      profiles.emplace_back( createTabulatedComptonProfile( identifiers[i], block.comptonProfile( i + 1 ) ) );
    }

    return profiles;
  }

} // photoatomic namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
