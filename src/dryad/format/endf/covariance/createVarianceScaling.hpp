#ifndef NJOY_DRYAD_FORMAT_ENDF_COVARIANCE_CREATEVARIANCESCALING
#define NJOY_DRYAD_FORMAT_ENDF_COVARIANCE_CREATEVARIANCESCALING

// system includes

// other includes
#include "tools/Log.hpp"
#include "tools/std20/algorithm.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/id/ReactionID.hpp"
#include "dryad/covariance/VarianceScaling.hpp"
#include "dryad/format/createVector.hpp"
#include "ENDFtk/section/CovariancePairs.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace covariance {

  /**
   *  @brief Create variance scaling information from ENDF covariance pair data
   */
  dryad::covariance::VarianceScaling
  createVarianceScaling( const ENDFtk::section::CovariancePairs& block ) {

    if ( block.LB() == 8 || block.LB() == 9 ) {

      std::vector< double > energies = createVector( block.firstArrayEnergies() );
      std::vector< double > factors = createVector( block.firstArrayFValues() );

      if ( factors.back() != 0. ) {

        Log::warning( "Variance scaling has non-zero factor beyond last energy value" );
      }

      factors.pop_back();
      dryad::covariance::ScalingType type = block.LB() == 8
                                          ? dryad::covariance::ScalingType::Inverse
                                          : dryad::covariance::ScalingType::Direct;
      return dryad::covariance::VarianceScaling( type, std::move( energies ), std::move( factors ) );
    }

    Log::error( "The ENDF covariance sub-subsection does not define variance scaling information" );
    Log::info( "Expected LB equal to 8 or 9, found {}", block.LB() );
    throw std::exception();
  }

} // covariance namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
