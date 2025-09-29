#ifndef NJOY_DRYAD_COVARIANCE_BASE_METADATA
#define NJOY_DRYAD_COVARIANCE_BASE_METADATA

// system includes
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
   *  This metadata class stores the keys asscoaited to the
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

  public:

    /* constructor */
    #include "dryad/covariance/base/Metadata/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the keys
     */
    const std::vector< Key >& keys() const { return this->keys_; }

    #include "dryad/covariance/base/Metadata/src/selection.hpp"

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
