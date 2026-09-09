#ifndef NJOY_FORMAT_GNDS_READ_READCOVARIANCEMATRIX
#define NJOY_FORMAT_GNDS_READ_READCOVARIANCEMATRIX

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "njoy/matrix.hpp"
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
                                       std::optional< std::string >, std::optional< std::string >,
                                       std::optional< std::string > >;

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

    // read the array node
    auto array = readArray( covariance.child( "gridded2d" ).child( "array" ) );
    if ( array.shape.size() != 2 ) {

      Log::error( "Expected a GNDS array node with rank {}, found one with rank {} instead",
                  2, array.shape.size() );
      throw std::exception();
    }

    // create the matrix
    matrix::Matrix< double > matrix( array.shape[0], array.shape[1] );
    unsigned int index = 0;
    for ( unsigned int i = 0; i < matrix.rows(); ++i ) {

      for ( unsigned int j = 0; j < matrix.cols(); ++j ) {

        matrix( i, j ) = array.values[index++];
      }
    }

    // read the axes
    auto axes = readAxes( covariance.child( "gridded2d" ).child( "axes" ) );

    // assign the data
    std::get< 1 >( data ) = std::move( std::get< 2 >( axes[0] ).value() );
    std::get< 2 >( data ) = std::move( std::get< 2 >( axes[1] ).value() );
    std::get< 3 >( data ) = std::move( matrix );
    std::get< 4 >( data ) = std::move( std::get< 1 >( axes[0] ) );
    std::get< 5 >( data ) = std::move( std::get< 1 >( axes[1] ) );
    std::get< 6 >( data ) = std::move( std::get< 1 >( axes[2] ) );

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
