#ifndef NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPPROJECTILETARGET
#define NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPPROJECTILETARGET

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "scion/math/compare.hpp"
#include "njoy/dryad/InteractionType.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"
#include "njoy/dryad/MultigroupProjectileTarget.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/gendf/read/createMultigroupReactions.hpp"
#include "njoy/format/gendf/read/covariance/createCrossSectionCovarianceData.hpp"
#include "njoy/format/gendf/read/covariance/createAngularDistributionCovarianceData.hpp"
#include "ENDFtk/GMaterial.hpp"
#include "ENDFtk/tree/GMaterial.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {

  /**
   *  @brief Create a MultigroupProjectileTarget from an unparsed GENDF material
   *
   *  @param[in] projectile            the projectile identifier
   *  @param[in] target                the target identifier
   *  @param[in] relative              the flag to indicate whether or not the covariance data is relative
   *  @param[in] frame                 the reference frame for the angular covariance data
   *  @param[in] material              the unparsed GENDF material (main groupr file)
   *  @param[in] covariances_xs        the optional unparsed xs covariances material (errorr file)
   *  @param[in] covariances_angular   the optional unparsed angular covariances material (errorr file)
   */
  inline dryad::MultigroupProjectileTarget
  createMultigroupProjectileTarget( const dryad::id::ParticleID& projectile,
                                    const dryad::id::ParticleID& target,
                                    bool relative,
                                    const dryad::ReferenceFrame& frame,
                                    const ENDFtk::tree::GMaterial& material,
                                    const std::optional< ENDFtk::tree::GMaterial >& covariances_xs,
                                    const std::optional< ENDFtk::tree::GMaterial >& covariances_angular ) {

    auto information = material.section( 1, 451 ).parse< 1, 451 >();
    if ( information.type() != -1 ) {

      Log::error( "The main GENDF file is not a GROUPR file." );
      throw std::exception();
    }

    std::vector< double > boundaries = createVector( information.neutronStructure() );

    if ( covariances_xs.has_value() ) {

      auto cov_information = covariances_xs->section( 1, 451 ).parse< 1, 451 >();
      if ( cov_information.type() != -11 ) {

        Log::error( "The cross section covariance file is not an ERRORR file." );
        throw std::exception();
      }

      std::vector< double > cov_boundaries = createVector( cov_information.neutronStructure() );

      if ( cov_boundaries.size() != boundaries.size() &&
           std::equal( boundaries.begin(), boundaries.end(), cov_boundaries.begin(),
                      [] ( double left, double right ) { return scion::math::isClose( left, right ); } ) ) {

        Log::error( "The group boundaries in the main GENDF file and the cross section covariance GENDF file do not match." );
        throw std::exception();
      }
    }

    if ( covariances_angular.has_value() ) {

      auto cov_information = covariances_angular->section( 1, 451 ).parse< 1, 451 >();
      if ( cov_information.type() != -11 ) {

        Log::error( "The angular distribution covariance file is not an ERRORR file." );
        throw std::exception();
      }

      std::vector< double > cov_boundaries = createVector( cov_information.neutronStructure() );

      if ( cov_boundaries.size() != boundaries.size() &&
           std::equal( boundaries.begin(), boundaries.end(), cov_boundaries.begin(),
                      [] ( double left, double right ) { return scion::math::isClose( left, right ); } ) ) {

        Log::error( "The group boundaries in the main GENDF file and the angular covariance GENDF file do not match." );
        throw std::exception();
      }
    }

    // interaction type
    dryad::InteractionType type = ( projectile == dryad::id::ParticleID::photon() ||
                                    projectile == dryad::id::ParticleID::electron() )
                                  ? dryad::InteractionType::Atomic
                                  : dryad::InteractionType::Nuclear;

    // get the dilution index for infinite dilution
    std::size_t dilution = 0;
    auto iter = std::find( information.dilutions().begin(), information.dilutions().end(), 1e+10 );
    if ( iter == information.dilutions().end() ) {

      Log::error( "Could not find the infinite dilution (sigma0 = 1e+10) in the GENDF file" );
      throw std::exception();
    }
    dilution = std::distance( information.dilutions().begin(), iter );

    // reaction data
    std::vector< dryad::MultigroupReaction > reactions =
    createMultigroupReactions( projectile, target, material, covariances_xs, covariances_angular,
                               boundaries, dilution );

    // covariance data
    std::optional< dryad::covariance::CovarianceData > covariances;
    if ( covariances_xs.has_value() || covariances_angular.has_value() ) {

      std::optional< dryad::covariance::CrossSectionCovarianceData > xs;
      std::optional< dryad::covariance::AngularDistributionCovarianceData > angular;

      if ( covariances_xs.has_value() ) {

        xs = covariance::createCrossSectionCovarianceData( projectile, target, relative,
                                                           covariances_xs.value() );
      }
      if ( covariances_angular.has_value() ) {

        angular = covariance::createAngularDistributionCovarianceData( projectile, target, frame,
                                                                       covariances_angular.value() );
      }

      covariances = dryad::covariance::CovarianceData( std::move( xs ), std::move( angular ) );
    }

    return dryad::MultigroupProjectileTarget( projectile, target, type,
                                              std::move( reactions ),
                                              std::move( covariances ) );
  }

} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
