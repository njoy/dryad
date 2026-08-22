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
#include "njoy/format/gnds/read/createCompression.hpp"
#include "njoy/format/gnds/read/createSymmetry.hpp"
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

    // read shape
    data.shape = readShape( array.attribute( "shape" ).as_string() );
    data.values.resize( std::accumulate( data.shape.begin(), data.shape.end(),
                                         1, std::multiplies() ) );
    if ( data.shape.size() == 0 ) {

      Log::error( "Array shape should define at least one dimension, found none" );
      throw std::exception();
    }

    // read compression
    Compression compression = Compression::None;
    auto attribute = array.attribute( "compression" );
    if ( attribute ) {

      compression = createCompression( attribute.as_string() );
    }

    // read symmetry
    Symmetry symmetry = Symmetry::None;
    attribute = array.attribute( "symmetry" );
    if ( attribute ) {

      symmetry = createSymmetry( attribute.as_string() );
    }
    if ( symmetry != Symmetry::None ) {

      if ( std::any_of( data.shape.begin(), data.shape.end(),
                        [&] ( auto&& number ) { return number != data.shape.front(); } ) ) {

        Log::error( "The array shape must be equal-dimensional when using any symmetry option" );
        throw std::exception();
      }
    }

    StorageOrder order = StorageOrder::RowMajor;
    attribute = array.attribute( "storageOrder" );
    if ( attribute ) {

      order = createStorageOrder( attribute.as_string() );
    }

    if ( order != StorageOrder::RowMajor ) {

      Log::error( "Array conversion currently only supports row-major, contact a developer" );
      Log::info( "storageOrder: {}", attribute ? attribute.as_string() : "row-major" );
      throw std::exception();
    }

    // look for the values node (it has no label) and read it
    pugi::xml_node child;
    for ( child = array.child( "values" ); child; child = child.next_sibling( "values" ) ) {

      if ( ! child.attribute( "label" ) ) {

        break;
      }
    }
    auto values = readValues( child );

//    // handle compression of the values
//    switch ( compression ) {
//
//      case Compression::None : {
//
//
//        break;
//      }
//      case Compression::Diagonal : {
//
//
//        break;
//      }
//      case Compression::Flattened : {
//
//        auto indices = array.find_child_by_attribute( "values", "label", "starts" );
//        auto lengths = array.find_child_by_attribute( "values", "label", "lengths" );
//
//        break;
//      }
//      default : {
//
//        break;
//      }
//    };

    if ( data.shape.size() == 2 ) {

      std::size_t rows = data.shape[0];
      std::size_t cols = data.shape[1];
      if ( compression == Compression::Diagonal ) {

        for ( std::size_t i = 0; i < rows; ++i ) {

          for ( std::size_t j = i; j < cols; ++j ) {

            if ( i == j ) {

              data.values[ i + j * cols ] = values[i];
            }
            else {

              data.values[ i + j * cols ] = 0.;
              data.values[ j + i * cols ] = 0.;
            }
          }
        }
      }
      else if ( compression == Compression::None && symmetry == Symmetry::Lower ) {

        std::size_t index = 0;
        for ( std::size_t i = 0; i < rows; ++i ) {

          for ( std::size_t j = 0; j <= i; ++j ) {

            if ( i == j ) {

              data.values[ i + j * cols ] = values[index++];
            }
            else {

              data.values[ i + j * cols ] = values[index++];
              data.values[ j + i * cols ] = data.values[ i + j * cols ];
            }
          }
        }
      }
      else if ( compression == Compression::None && symmetry == Symmetry::Upper ) {

        std::size_t index = 0;
        for ( std::size_t i = 0; i < rows; ++i ) {

          for ( std::size_t j = i; j < cols; ++j ) {

            if ( i == j ) {

              data.values[ i + j * cols ] = values[index++];
            }
            else {

              data.values[ i + j * cols ] = values[index++];
              data.values[ j + i * cols ] = data.values[ i + j * cols ];
            }
          }
        }
      }
      else if ( compression == Compression::None && symmetry == Symmetry::None ) {

        data.values = std::move( values );
      }
      else {

        Log::error( "Array conversion currently unsupported, contact a developer" );
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
