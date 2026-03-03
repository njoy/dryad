#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATETABULATEDECOMPTONPROFILE
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATETABULATEDECOMPTONPROFILE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/TabulatedComptonProfile.hpp"
#include "njoy/dryad/format/endf/createInterpolant.hpp"
#include "ACEtk/photoatomic/ComptonProfile.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create TabulatedComptonProfile instances from ACE data
   *
   *  @param[in] subshellIdentifier   the subshell identifier
   *  @param[in] profile              a Compton profile instance
   */
  inline TabulatedComptonProfile
  createTabulatedComptonProfile(
      id::ElectronSubshellID subshellIdentifier,
      const njoy::ACEtk::photoatomic::ComptonProfile& profile ) {

    try {

      auto momentum = createVector( profile.momentum() );
      auto pdf = createVector( profile.pdf() );
      auto cdf = createVector( profile.cdf() );
      std::vector< std::size_t > boundaries = { momentum.size() - 1 };
      std::vector< InterpolationType > interpolants = { endf::createInterpolant( profile.interpolation() ) };
      return TabulatedComptonProfile(
               std::move( subshellIdentifier ),
               TabulatedComptonProfileFunction(
                 momentum, std::move( pdf ),
                 boundaries, interpolants ),
               TabulatedComptonProfileFunction(
                 momentum, std::move( cdf ),
                 boundaries, interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated Compton profile" );
      throw;
    }
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
