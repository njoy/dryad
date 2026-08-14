#ifndef NJOY_DRYAD_COVARIANCE_BASE_METADATA
#define NJOY_DRYAD_COVARIANCE_BASE_METADATA

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace covariance {
namespace base {

  /**
   *  @class
   *  @brief A base class representing covariance metadata
   *
   *  This metadata class stores the keys associated to the
   *  rows and columns of the covariance matrix. It also has
   *  the functionality to return the indices of the rows or
   *  columns of the matrix corresponding to a selection of
   *  keys.
   */
  template < typename... Ts >
  class Metadata {

  protected:

    /* type aliases */
    using Key = std::tuple< Ts... >;
    using Selection = std::tuple< std::optional< Ts >... >;

    /* fields - keys */
    std::vector< Key > keys_;

  private:

    template < typename LeftTuple, typename RightTuple, std::size_t... Is >
    static auto compare_key_impl( const LeftTuple& left, const RightTuple& right,
                                  std::index_sequence< Is... > ) {

      auto compare = [] ( auto&& left, auto&& right ) {

        if ( left == std::nullopt || left == right ) {

          return true;
        }
        return false;
      };

      return ( compare( std::get< Is >( left ), std::get< Is >( right ) ) && ... );
    }

    static auto compare_key( const std::tuple< std::optional< Ts >... >& left,
                             const std::tuple< Ts... >& right ) {

      return compare_key_impl( left, right, std::make_index_sequence< sizeof...( Ts ) >{} );
    }

  public:

    /* constructor */
    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    Metadata() = default;

    Metadata( const Metadata& ) = default;
    Metadata( Metadata&& ) = default;

    Metadata& operator=( const Metadata& ) = default;
    Metadata& operator=( Metadata&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] keys   the keys associated with the covariance matrix
     */
    Metadata( std::vector< Key > keys ) : keys_( std::move( keys ) ) {}

    /* methods */

    /**
     *  @brief Return the keys
     */
    const std::vector< Key >& keys() const { return this->keys_; }

    std::vector< std::size_t >
    selection( const std::optional< Ts >&... args ) const {

      Selection select = std::make_tuple( args... );

      std::vector< std::size_t > indices;
      for ( std::size_t i = 0; i < this->keys().size(); ++i ) {

        if ( compare_key( select, this->keys()[i] ) ) {

          indices.emplace_back( i );
        }
      }
      return indices;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const Metadata& right ) const {

      return this->keys() == right.keys();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const Metadata& right ) const {

      return ! this->operator==( right );
    }
  };

} // base namespace
} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
