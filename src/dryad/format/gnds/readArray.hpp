#ifndef NJOY_DRYAD_FORMAT_GNDS_READARRAY
#define NJOY_DRYAD_FORMAT_GNDS_READARRAY

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
   *  @brief Read data from a GNDS array node
   */
  static dryad::covariance::Matrix< double > readArray( const pugi::xml_node& array ) {

    throwExceptionOnWrongNode( array, "array" );

    std::vector< std::size_t > shape = readShape( array.attribute( "shape" ).as_string() );

    std::optional< std::string > compression = std::nullopt;
    auto attribute = array.attribute( "compression" );
    if ( attribute ) {

      compression = attribute.as_string();
      if ( compression == "none" ) {

        compression = std::nullopt;
      }
    }

    std::optional< std::string > symmetry = std::nullopt;
    attribute = array.attribute( "symmetry" );
    if ( attribute ) {

      symmetry = attribute.as_string();
      if ( symmetry == "none" ) {

        symmetry = std::nullopt;
      }
    }

    std::optional< std::string > order = std::nullopt;
    attribute = array.attribute( "storageOrder" );
    if ( attribute ) {

      order = attribute.as_string();
      if ( order == "row-major" ) {

        order = std::nullopt;
      }
    }

    if ( order.has_value() ) {

      Log::error( "Array conversion currently only supports row-major, contact a developer" );
      Log::info( "Compression: {}", compression.has_value() ? compression.value() : "none" );
      Log::info( "Symmetry: {}", symmetry.has_value() ? symmetry.value() : "none" );
      Log::info( "storageOrder: {}", order.has_value() ? order.value() : "row-major" );
      throw std::exception();
    }

    auto data = readValues( array.child( "values" ) );

    if ( shape.size() == 2 ) {

      dryad::covariance::Matrix< double > matrix( shape[0], shape[1] );
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
      else if ( !compression.has_value() && symmetry.has_value() &&
                symmetry.value() == "upper" ) {

        unsigned int index = 0;
        for ( unsigned int i = 0; i < matrix.rows(); ++i ) {

          for ( unsigned int j = i; j < matrix.cols(); ++j ) {

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
      else if ( !compression.has_value() && !symmetry.has_value()  ) {

        unsigned int index = 0;
        for ( unsigned int i = 0; i < matrix.rows(); ++i ) {

          for ( unsigned int j = 0; j < matrix.cols(); ++j ) {

            matrix( i, j ) = data[index++];
          }
        }
      }
      else {

        Log::error( "Array conversion currently unsupported, contact a developer" );
        Log::info( "Compression: {}", compression.has_value() ? compression.value() : "none" );
        Log::info( "Symmetry: {}", symmetry.has_value() ? symmetry.value() : "none" );
        Log::info( "storageOrder: {}", order.has_value() ? order.value() : "row-major" );
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
