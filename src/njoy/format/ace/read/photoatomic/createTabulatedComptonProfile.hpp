#ifndef NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATETABULATEDECOMPTONPROFILE
#define NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATETABULATEDECOMPTONPROFILE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/TabulatedComptonProfile.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createInterpolant.hpp"
#include "ACEtk/photoatomic/ComptonProfile.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace photoatomic {

  /**
   *  @brief Create TabulatedComptonProfile instances from ACE data
   *
   *  @param[in] subshellIdentifier   the subshell identifier
   *  @param[in] profile              a Compton profile instance
   */
  inline dryad::TabulatedComptonProfile
  createTabulatedComptonProfile(
      dryad::id::ElectronSubshellID subshellIdentifier,
      const njoy::ACEtk::photoatomic::ComptonProfile& profile ) {

    try {

      auto momentum = createVector( profile.momentum() );
      auto pdf = createVector( profile.pdf() );
      auto cdf = createVector( profile.cdf() );
      std::vector< std::size_t > boundaries = { momentum.size() - 1 };
      std::vector< dryad::InterpolationType > interpolants = { endf::read::createInterpolant( profile.interpolation() ) };
      return dryad::TabulatedComptonProfile(
               std::move( subshellIdentifier ),
               dryad::TabulatedComptonProfileFunction(
                 momentum, std::move( pdf ),
                 boundaries, interpolants ),
               dryad::TabulatedComptonProfileFunction(
                 momentum, std::move( cdf ),
                 boundaries, interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated Compton profile" );
      throw;
    }
  }

} // photoatomic namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
