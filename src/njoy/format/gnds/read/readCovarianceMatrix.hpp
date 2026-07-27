#ifndef NJOY_FORMAT_GNDS_READ_READCOVARIANCEMATRIX
#define NJOY_FORMAT_GNDS_READ_READCOVARIANCEMATRIX

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/readAxes.hpp"
#include "njoy/format/gnds/read/readArray.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  using CovarianceMatrix = std::tuple< bool, std::vector< double >, std::vector< double >,
                                       matrix::Matrix< double >,
                                       std::string, std::string, std::string >;

  /**
   *  @brief Read data from a GNDS covarianceMatrix node
   *
   *  @param[in] covariance   the gnds covariance node
   */
  inline CovarianceMatrix readCovarianceMatrix( const pugi::xml_node& covariance ) {

    throwExceptionOnWrongNode( covariance, "covarianceMatrix" );

    CovarianceMatrix data;

    // check for the covariance type (relative or absolute)
    std::string type = covariance.attribute( "type" ).as_string();
    if ( type == "relative" ) {

      std::get< 0 >( data ) = true;
    }
    else {

      std::get< 0 >( data ) = false;
    }

    // read the axes and the array
    auto axes = readAxes( covariance.child( "gridded2d" ).child( "axes" ) );
    std::get< 1 >( data ) = std::move( std::get< 2 >( axes[0] ).value() );
    std::get< 2 >( data ) = std::move( std::get< 2 >( axes[1] ).value() );
    std::get< 3 >( data ) = readArray( covariance.child( "gridded2d" ).child( "array" ) );
    std::get< 4 >( data ) = std::move( std::get< 1 >( axes[0] ).value() );
    std::get< 5 >( data ) = std::move( std::get< 1 >( axes[1] ).value() );
    std::get< 6 >( data ) = std::move( std::get< 1 >( axes[2] ).value() );

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
