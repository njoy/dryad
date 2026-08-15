#ifndef NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPPROJECTILETARGET
#define NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPPROJECTILETARGET

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/InteractionType.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"
#include "njoy/dryad/MultigroupProjectileTarget.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/gendf/read/createMultigroupReactions.hpp"
#include "njoy/format/gendf/read/covariance/createCovarianceData.hpp"
#include "ENDFtk/GMaterial.hpp"
#include "ENDFtk/tree/GMaterial.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {

  /**
   *  @brief Create a MultigroupProjectileTarget from an unparsed GENDF material
   *
   *  Only the infinite dilution (sigma0 = 1e+10) cross sections are read. For a
   *  GROUPR formatted file the dilution list is searched for the infinite dilution
   *  value, for an ERRORR formatted file the single available dilution is used.
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] relative     the flag to indicate whether or not the covariance data is relative
   *  @param[in] frame        the reference frame
   *  @param[in] material     the unparsed GENDF material
   */
  inline dryad::MultigroupProjectileTarget
  createMultigroupProjectileTarget( const dryad::id::ParticleID& projectile,
                                    const dryad::id::ParticleID& target,
                                    bool relative,
                                    const dryad::ReferenceFrame& frame,
                                    const ENDFtk::tree::GMaterial& material ) {

    auto information = material.section( 1, 451 ).parse< 1, 451 >();
    std::vector< double > boundaries = createVector( information.neutronStructure() );

    // interaction type
    dryad::InteractionType type =
        ( projectile == dryad::id::ParticleID::photon() ||
          projectile == dryad::id::ParticleID::electron() )
        ? dryad::InteractionType::Atomic
        : dryad::InteractionType::Nuclear;

    // the dilution index for the infinite dilution cross section
    std::size_t dilution = 0;
    if ( information.type() == -1 ) {

      // groupr gendf : search the dilution list for infinite dilution (1e+10)
      auto dilutions = information.dilutions();
      auto iter = std::find( dilutions.begin(), dilutions.end(), 1e+10 );
      if ( iter == dilutions.end() ) {

        Log::error( "Could not find the infinite dilution (sigma0 = 1e+10) in the GENDF file" );
        throw std::exception();
      }
      dilution = std::distance( dilutions.begin(), iter );
    }

    // reaction data
    std::vector< dryad::MultigroupReaction > reactions =
    createMultigroupReactions( projectile, target, material, boundaries, dilution );

    // covariance data
    std::optional< dryad::covariance::CovarianceData > covariances =
    covariance::createCovarianceData( projectile, target, relative, frame, material );

    return dryad::MultigroupProjectileTarget( projectile, target, type,
                                              std::move( reactions ),
                                              std::move( covariances ) );
  }

} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
