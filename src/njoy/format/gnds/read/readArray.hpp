#ifndef NJOY_FORMAT_GNDS_READ_READARRAY
#define NJOY_FORMAT_GNDS_READ_READARRAY

// system includes
#include <numeric>
#include <functional>
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/createStorageOrder.hpp"
#include "njoy/format/gnds/read/readShape.hpp"
#include "njoy/format/gnds/read/readValues.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  struct Array {

    std::vector< std::size_t > shape;
    std::vector< double > values;
  };

  /**
   *  @brief Read data from a GNDS array node
   *
   *  @param[in] array   the gnds array node
   */
  inline Array readArray( const pugi::xml_node& array ) {

    throwExceptionOnWrongNode( array, "array" );

    Array data;

    data.shape = readShape( array.attribute( "shape" ).as_string() );
    data.values.resize( std::accumulate( data.shape.begin(), data.shape.end(),
                                         1, std::multiplies() ) );

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

    StorageOrder order = StorageOrder::RowMajor;
    attribute = array.attribute( "storageOrder" );
    if ( attribute ) {

      order = createStorageOrder( attribute.as_string() );
    }

    if ( order != StorageOrder::RowMajor ) {

      Log::error( "Array conversion currently only supports row-major, contact a developer" );
      Log::info( "Compression: {}", compression.has_value() ? compression.value() : "none" );
      Log::info( "Symmetry: {}", symmetry.has_value() ? symmetry.value() : "none" );
      Log::info( "storageOrder: {}", attribute ? attribute.as_string() : "row-major" );
      throw std::exception();
    }

    auto indices = array.find_child_by_attribute( "values", "label", "starts" );
    auto lengths = array.find_child_by_attribute( "values", "label", "lengths" );

    auto values = readValues( array.child( "values" ) );

    if ( data.shape.size() == 2 ) {

      std::size_t rows = data.shape[0];
      std::size_t cols = data.shape[1];
      if ( compression.has_value() && compression.value() == "diagonal" ) {

        for ( unsigned int i = 0; i < rows; ++i ) {

          for ( unsigned int j = i; j < cols; ++j ) {

            if ( i == j ) {

              data.values[ i + j * rows ] = values[i];
            }
            else {

              data.values[ i + j * rows ] = 0.;
              data.values[ j + i * rows ] = 0.;
            }
          }
        }
      }
      else if ( !compression.has_value() && symmetry.has_value() &&
                symmetry.value() == "lower" ) {

        unsigned int index = 0;
        for ( unsigned int i = 0; i < rows; ++i ) {

          for ( unsigned int j = 0; j <= i; ++j ) {

            if ( i == j ) {

              data.values[ i + j * rows ] = values[index++];
            }
            else {

              data.values[ i + j * rows ] = values[index++];
              data.values[ j + i * rows ] = data.values[ i + j * rows ];
            }
          }
        }
      }
      else if ( !compression.has_value() && symmetry.has_value() &&
                symmetry.value() == "upper" ) {

        unsigned int index = 0;
        for ( unsigned int i = 0; i < rows; ++i ) {

          for ( unsigned int j = i; j < cols; ++j ) {

            if ( i == j ) {

              data.values[ i + j * rows ] = values[index++];
            }
            else {

              data.values[ i + j * rows ] = values[index++];
              data.values[ j + i * rows ] = data.values[ i + j * rows ];
            }
          }
        }
      }
      else if ( !compression.has_value() && !symmetry.has_value()  ) {

        data.values = std::move( values );
      }
      else {

        Log::error( "Array conversion currently unsupported, contact a developer" );
        Log::info( "Compression: {}", compression.has_value() ? compression.value() : "none" );
        Log::info( "Symmetry: {}", symmetry.has_value() ? symmetry.value() : "none" );
        Log::info( "storageOrder: {}", attribute ? attribute.as_string() : "row-major" );
        throw std::exception();
      }

      return data;
    }
    else {

      Log::error( "Can currently only read arrays of size 2, contact a developer" );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
