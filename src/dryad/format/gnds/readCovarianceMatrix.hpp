#ifndef NJOY_DRYAD_FORMAT_GNDS_READCOVARIANCEMATRIX
#define NJOY_DRYAD_FORMAT_GNDS_READCOVARIANCEMATRIX

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "dryad/format/gnds/readAxes.hpp"
#include "dryad/format/gnds/readArray.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  using CovarianceMatrix = std::tuple< bool, std::vector< double >, std::vector< double >,
                                       dryad::covariance::Matrix< double > >;

  /**
   *  @brief Read data from a GNDS covarianceMatrix node
   */
  static CovarianceMatrix readCovarianceMatrix( const pugi::xml_node& covariance ) {

    throwExceptionOnWrongNode( covariance, "covarianceMatrix" );

    CovarianceMatrix data;

    // check for the covariance type (relative or absolute)
    std::string type = covariance.attribute( "type" ).as_string();
    if ( type == "relative" ) {

      std::get< 0 >( data ) = true;
    }
    else {

      std::get< 0 >( data ) = true;
    }

    // read the axes and the array
    auto axes = readAxes( covariance.child( "gridded2d" ).child( "axes" ) );
    std::get< 1 >( data ) = std::get< 2 >( axes[0] ).value();
    std::get< 2 >( data ) = std::get< 2 >( axes[1] ).value();
    std::get< 3 >( data ) = readArray( covariance.child( "gridded2d" ).child( "array" ) );

    return data;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
