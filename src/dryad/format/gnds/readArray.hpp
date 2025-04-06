#ifndef NJOY_DRYAD_FORMAT_GNDS_READAXIS
#define NJOY_DRYAD_FORMAT_GNDS_READAXIS

// system includes
#include <optional>
#include <sstream>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "dryad/format/gnds/readShape.hpp"
#include "dryad/format/gnds/readValues.hpp"
#include "dryad/covariance/matrix.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Read data from a GNDS axis node
   */
  static covariance::Matrix< double > readArray( const pugi::xml_node& array ) {

    throwExceptionOnWrongNode( array, "array" );

    std::vector< std::size_t > shape = readShape( array.attribute( "shape" ).as_string() );

    std::optional< std::string > compression = std::nullopt;
    auto attribute = array.attribute( "compression" );
    if ( attribute ) {

      compression = attribute.as_string();
    }

    std::optional< std::string > symmetry = std::nullopt;
    attribute = array.attribute( "symmetry" );
    if ( attribute ) {

      symmetry = attribute.as_string();
    }

    auto data = readValues( array.child( "values" ) );

    if ( shape.size() == 2 ) {

      covariance::Matrix< double > matrix( shape[0], shape[1] );
      if ( compression.has_value() && compression.value() == "diagonal" ) {

        for ( unsigned int i = 0; i < matrix.rows(); ++i ) {

          for ( unsigned int j = i; j < matrix.cols(); ++j ) {

            if ( i == j ) {

              matrix( i, j ) = data[i];
            }
            else {

              matrix( i, j ) = 0.;
              matrix( j, i ) = 0.;
            }
          }
        }
      }
      else if ( !compression.has_value() && symmetry.has_value() &&
                symmetry.value() == "lower" ) {

        unsigned int index = 0;
        for ( unsigned int i = 0; i < matrix.rows(); ++i ) {

          for ( unsigned int j = 0; j <= i; ++j ) {

            if ( i == j ) {

              matrix( i, j ) = data[index++];
            }
            else {

              matrix( i, j ) = data[index++];
              matrix( j, i ) = matrix( i, j );
            }
          }
        }
      }
      else {

        Log::error( "Array conversion currently unsupported, contact a developer" );
        throw std::exception();
      }

      return matrix;
    }
    else {

      Log::error( "Can currently only read arrays of size 2, contact a developer" );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
