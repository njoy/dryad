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

  /**
   *  @brief The covariance matrix information
   */
  struct CovarianceMatrix {

    bool relative;
    std::vector< double > row_structure;
    std::vector< double > column_structure;
    matrix::Matrix< double > matrix;
    std::optional< std::string > row_unit;
    std::optional< std::string > column_unit;
    std::optional< std::string > covariance_unit;
  };

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
    data.relative = type == "relative";

    // read the array node
    auto array = readArray( covariance.child( "gridded2d" ).child( "array" ) );
    if ( array.shape.size() != 2 ) {

      Log::error( "Expected a GNDS array node with dimension {}, found one with dimension {} instead",
                  2, array.shape.size() );
      throw std::exception();
    }

    // create the matrix
    data.matrix.resize( array.shape[0], array.shape[1] );
    unsigned int index = 0;
    for ( unsigned int i = 0; i < data.matrix.rows(); ++i ) {

      for ( unsigned int j = 0; j < data.matrix.cols(); ++j ) {

        data.matrix( i, j ) = array.values[index++];
      }
    }

    // read the axes
    auto axes = readAxes( covariance.child( "gridded2d" ).child( "axes" ) );

    // assign the data
    data.row_structure = std::move( axes[0].values.value() );
    data.column_structure = std::move( axes[1].values.value() );
    data.row_unit = std::move( axes[0].unit );
    data.column_unit = std::move( axes[1].unit );
    data.covariance_unit = std::move( axes[2].unit );

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
