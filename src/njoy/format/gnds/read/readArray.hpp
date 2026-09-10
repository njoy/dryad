#ifndef NJOY_FORMAT_GNDS_READ_READARRAY
#define NJOY_FORMAT_GNDS_READ_READARRAY

// system includes
#include <algorithm>
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
#include "njoy/format/gnds/read/createPermutation.hpp"
#include "njoy/format/gnds/read/readShape.hpp"
#include "njoy/format/gnds/read/readValues.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief The array shape and data as a row major flat array
   */
  struct Array {

    std::vector< std::size_t > shape;
    std::vector< double > values;
  };

  /**
   *  @brief Convert an index (row or column major) into tensor indices (row major)
   *
   *  @param[in] index   the index in the given storage order
   *  @param[in] shape   the array shape
   *  @param[in] order   the storage order
   */
  inline std::vector< std::size_t >
  convertToIndices( std::size_t index,
                    const std::vector< std::size_t >& shape,
                    StorageOrder order ) {

    std::vector< std::size_t > indices( shape.size(), 0 );
    if ( order == StorageOrder::RowMajor ) {

      for ( std::size_t i = shape.size(); i-- > 0; ) {

        indices[i] = index % shape[i];
        index /= shape[i];
      }
    }
    else {

      for ( std::size_t i = 0; i < shape.size(); ++i ) {

        indices[i] = index % shape[i];
        index /= shape[i];
      }
    }
    return indices;
  }

  /**
   *  @brief Convert tensor indices (row major) into an index (row major)
   *
   *  @param[in] indices   the indices
   *  @param[in] strides   the row major strides
   */
  inline std::size_t
  convertToIndex( const std::vector< std::size_t >& indices,
                  const std::vector< std::size_t >& strides ) {

    std::size_t index = 0;
    for ( std::size_t i = 0; i < indices.size(); ++i ) {

      index += indices[i] * strides[i];
    }
    return index;
  }

  /**
   *  @brief Verify whether the tensor indices (row major) are within the stored
   *         hyper-triangle
   *
   *  @param[in] indices       the indices
   *  @param[in] symmetry      the symmetry option (lower or upper)
   *  @param[in] permutation   the permutation type
   */
  inline bool inHyperTriangle( const std::vector< std::size_t >& indices,
                               Symmetry symmetry, Permutation permutation ) {

    bool strict = permutation == Permutation::AntiSymmetric;
    for ( std::size_t i = 0; i + 1 < indices.size(); ++i ) {

      if ( symmetry == Symmetry::Lower ) {

        if ( strict ? ! ( indices[i] > indices[i + 1] )
                    : ! ( indices[i] >= indices[i + 1] ) ) { return false; }
      }
      else {

        if ( strict ? ! ( indices[i] < indices[i + 1] )
                    : ! ( indices[i] <= indices[i + 1] ) ) { return false; }
      }
    }
    return true;
  }

  /**
   *  @brief Expand a stored hyper-triangle in a dense row major array
   *
   *  @param[in,out] values     the row major values with the hyper-triangle
   *  @param[in] shape          the array shape
   *  @param[in] strides        the row major strides (see rowMajorStrides)
   *  @param[in] symmetry       the symmetry option (Lower or Upper)
   *  @param[in] permutation    the permutation type
   */
  inline void expandSymmetry( std::vector< double >& values,
                              const std::vector< std::size_t >& shape,
                              const std::vector< std::size_t >& strides,
                              Symmetry symmetry, Permutation permutation ) {

    if ( permutation != Permutation::None ) {

      for ( std::size_t i = 0; i < values.size(); ++i ) {

        auto indices = convertToIndices( i, shape, StorageOrder::RowMajor );
        if ( inHyperTriangle( indices, symmetry, permutation ) ) {

          double value = values[i];
          if ( permutation == Permutation::Symmetric ) {

            std::sort( indices.begin(), indices.end() );
            do {

              values[ convertToIndex( indices, strides ) ] = value;
            }
            while ( std::next_permutation( indices.begin(), indices.end() ) );
          }
          else {

            auto count_inversions = [] ( const std::vector< std::size_t >& indices ) {

              std::size_t inversions = 0;
              for ( std::size_t i = 0; i < indices.size(); ++i ) {

                for ( std::size_t j = i + 1; j < indices.size(); ++j ) {

                  if ( indices[i] > indices[j] ) {

                    ++inversions;
                  }
                }
              }
              return inversions;
            };

            // the value is written with a sign given by the parity of each
            // permutation relative to the stored index tuple (so the stored
            // position itself always keeps the unmodified value)
            int reference = ( count_inversions( indices ) % 2 == 0 ) ? 1 : -1;

            std::sort( indices.begin(), indices.end() );
            do {

              int sign = ( count_inversions( indices ) % 2 == 0 ) ? 1 : -1;
              values[ convertToIndex( indices, strides ) ] = sign * reference * value;
            }
            while ( std::next_permutation( indices.begin(), indices.end() ) );
          }
        }
      }
    }
  }

  /**
   *  @brief Read data from a GNDS array node
   *
   *  An array node can store a tensor of any rank n. The node provides a large
   *  number of options on compression, symmetry, etc. See the GNDS specs for more
   *  details.
   *
   *  Bear with me, this is complicated.
   *
   *  Compression types: none, flattened, diagonal.
   *  The compression type applies to the stored values before the application of symmetry
   *  and permutation.
   *
   *  Symmetry types: none, lower and upper.
   *  The symmetry type tells us if the tensor is given as a full tensor or as the lower or
   *  upper hyper-triangular. Symmetry can only be used for tensors that are of equal shape
   *  across all dimensions.
   *
   *  Permutation types: none, symmetric (+1) or anti-symmetric (-1)
   *  The permutation type tells us how to fill in the missing elements of the tensor. None
   *  basically means zero. The symmetric permutation means that the value for a tensor
   *  location (i_n, ..., i_1) is the same for all permutations of the indices i_1, ..., i_n.
   *  Anti-symmetric is the same but the value changes sign when swappin any two of its indices
   *  (for example: T[i_1, ..., i_n] = -T[i_n, ..., i_1]). Because of this, the diagonal elements
   *  of an anti-symmetric tensor are always zero.
   *
   *  Note: the default for the permutation attribute is set to "+1" (symmetric) contrary
   *        to what the specs say.
   *
   *  @param[in] array   the gnds array node
   */
  inline Array readArray( const pugi::xml_node& array ) {

    throwExceptionOnWrongNode( array, "array" );

    Array data;

    // read shape and calculate the total size
    data.shape = readShape( array.attribute( "shape" ).as_string() );
    data.values.resize( std::accumulate( data.shape.begin(), data.shape.end(),
                                         1, std::multiplies< std::size_t >() ) );
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

    // read permutation
    // note: we assume that the default is Symmetry while the GNDS specs say it is None
    Permutation permutation = Permutation::Symmetric;
    attribute = array.attribute( "permutation" );
    if ( attribute ) {

      permutation = createPermutation( attribute.as_string() );
    }

    // read storage order
    StorageOrder order = StorageOrder::RowMajor;
    attribute = array.attribute( "storageOrder" );
    if ( attribute ) {

      order = createStorageOrder( attribute.as_string() );
    }

    // look for the values node (it has no label) and read it
    pugi::xml_node child;
    for ( child = array.child( "values" ); child; child = child.next_sibling( "values" ) ) {

      if ( ! child.attribute( "label" ) ) {

        break;
      }
    }
    auto values = readValues( child );

    // get the row major strides
    std::vector< std::size_t > strides( data.shape.size(), 1 );
    for ( std::size_t i = data.shape.size() - 1; i > 0; --i ) {

      strides[i - 1] = strides[i] * data.shape[i];
    }

    // uncompressed and no symmetry: just use the values
    if ( compression == Compression::None && symmetry == Symmetry::None ) {

      if ( values.size() != data.values.size() ) {

        Log::error( "The number of values found in the array ({}) is different from "
                    "the number of expected values ({})", values.size(), data.values.size() );
        throw std::exception();
      }

      if ( order == StorageOrder::RowMajor ) {

        data.values = std::move( values );
      }
      else {

        for ( std::size_t i = 0; i < values.size(); ++i ) {

          auto indices = convertToIndices( i, data.shape, order );
          data.values[ convertToIndex( indices, strides ) ] = values[i];
        }
      }

      return data;
    }
    // uncompressed array with a symmetry option: place the hyper-triangle in the right
    // position and apply the symmetry
    else if ( compression == Compression::None && symmetry != Symmetry::None ) {

      std::size_t index = 0;
      for ( std::size_t i = 0; i < data.values.size(); ++i ) {

        auto indices = convertToIndices( i, data.shape, order );
        if ( inHyperTriangle( indices, symmetry, permutation ) ) {

          if ( index >= values.size() ) {

            Log::error( "The number of values found in the array ({}) is less than "
                        "the number of expected values", values.size() );
            throw std::exception();
          }
          data.values[ convertToIndex( indices, strides ) ] = values[index++];
        }
      }

      if ( index != values.size() ) {

        Log::error( "The number of values found in the array ({}) is different from "
                    "the number of expected values ({})", values.size(), index );
        throw std::exception();
      }

      expandSymmetry( data.values, data.shape, strides, symmetry, permutation );

      return data;
    }
    // diagonal compression
    else if ( compression == Compression::Diagonal ) {

      std::size_t rank = data.shape.size();

      std::vector< std::size_t > startingIndices;
      auto starts = array.find_child_by_attribute( "values", "label", "startingIndices" );
      if ( starts ) {

        startingIndices = readValues< std::size_t >( starts );
        if ( startingIndices.size() % rank != 0 ) {

          Log::error( "The number of starting indices ({}) is not a multiple of "
                      "the final tensor rank ({})",
                      startingIndices.size(), rank );
          throw std::exception();
        }
      }
      else {

        startingIndices.resize( rank, 0 );
      }

      std::size_t index = 0;
      for ( std::size_t i = 0; i < startingIndices.size() / rank; ++i ) {

        // the starting multi-index for this diagonal vector
        std::vector< std::size_t > start( startingIndices.begin() + i * rank,
                                          startingIndices.begin() + ( i + 1 ) * rank );

        // the vector length is bounded by the distance to the nearest array edge
        std::size_t length = data.shape[0] - start[0];
        for ( std::size_t j = 1; j < rank; ++j ) {

          length = std::min( length, data.shape[j] - start[j] );
        }

        // walk parallel to the main diagonal, consuming sequential values
        for ( std::size_t j = 0; j < length; ++j ) {

          if ( index >= values.size() ) {

            Log::error( "The number of values found in the array ({}) is less than "
                        "the number of expected diagonal entries", values.size() );
            throw std::exception();
          }

          std::vector< std::size_t > indices( rank );
          for ( std::size_t k = 0; k < rank; ++k ) {

            indices[k] = start[k] + j;
          }
          data.values[ convertToIndex( indices, strides ) ] = values[index++];
        }
      }

      if ( index != values.size() ) {

        Log::error( "The number of values found in the array ({}) is different from "
                    "the number of expected diagonal entries ({})", values.size(), index );
        throw std::exception();
      }

      return data;
    }
    // flattened compression: decompress the array, apply storage order and symmetry
    else if ( compression == Compression::Flattened ) {

      auto startsNode = array.find_child_by_attribute( "values", "label", "starts" );
      auto lengthsNode = array.find_child_by_attribute( "values", "label", "lengths" );
      if ( ! startsNode || ! lengthsNode ) {

        Log::error( "Flattened array compression requires both a \'starts\' and "
                    "a \'lengths\' values node" );
        throw std::exception();
      }
      auto starts = readValues< std::size_t >( startsNode );
      auto lengths = readValues< std::size_t >( lengthsNode );
      if ( starts.size() != lengths.size() ) {

        Log::error( "The number of starts ({}) and lengths ({}) are inconsistent",
                    starts.size(), lengths.size() );
        throw std::exception();
      }

      std::vector< double > linear( data.values.size(), 0. );
      std::size_t index = 0;
      for ( std::size_t i = 0; i < starts.size(); ++i ) {

        if ( starts[i] + lengths[i] > linear.size() ) {

          Log::error( "A flattened run (start {}, length {}) exceeds the array "
                      "size ({})", starts[i], lengths[i], linear.size() );
          throw std::exception();
        }
        for ( std::size_t j = 0; j < lengths[i]; ++j ) {

          if ( index >= values.size() ) {

            Log::error( "The number of values ({}) is smaller than the sum of "
                        "the lengths", values.size() );
            throw std::exception();
          }
          linear[ starts[i] + j ] = values[index++];
        }
      }

      if ( index != values.size() ) {

        Log::error( "The number of values ({}) does not match the sum of the "
                    "lengths ({})", values.size(), index );
        throw std::exception();
      }

      if ( order == StorageOrder::RowMajor ) {

        data.values = std::move( linear );
      }
      else {

        for ( std::size_t i = 0; i < linear.size(); ++i ) {

          auto indices = convertToIndices( i, data.shape, order );
          data.values[ convertToIndex( indices, strides ) ] = linear[i];
        }
      }

      if ( symmetry != Symmetry::None ) {

        expandSymmetry( data.values, data.shape, strides, symmetry, permutation );
      }

      return data;
    }

    Log::error( "The array configuration is currently unsupported, contact a developer" );
    throw std::exception();
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
