#ifndef NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYMETADATA
#define NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYMETADATA

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/EnergyGroup.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/base/Metadata.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief Covariance metadata for product multiplicities
   */
  class ProductMultiplicityMetadata :
    protected base::Metadata< id::ReactionID, id::EnergyGroup, id::ParticleID > {

    /* type aliases */

    using Parent = base::Metadata< id::ReactionID, id::EnergyGroup, id::ParticleID >;

    /* fields */

    std::vector< id::ReactionID > reactions_;
    std::vector< double > energies_;
    std::vector< id::ParticleID > products_;

    /* auxiliary functions */

    #include "njoy/dryad/covariance/ProductMultiplicityMetadata/src/generateEnergyGroups.hpp"
    #include "njoy/dryad/covariance/ProductMultiplicityMetadata/src/generateKeys.hpp"
    #include "njoy/dryad/covariance/ProductMultiplicityMetadata/src/updateMetadata.hpp"

  public:

    /* constructor */
    #include "njoy/dryad/covariance/ProductMultiplicityMetadata/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the reaction identifiers
     */
    const std::vector< id::ReactionID >& reactionIdentifiers() const {

      return this->reactions_;
    }

    /**
     *  @brief Return the energy group boundaries
     */
    const std::vector< double >& energies() const {

      return this->energies_;
    }

    /**
     *  @brief Return the reaction product identifiers
     */
    const std::vector< id::ParticleID >& productIdentifiers() const {

      return this->products_;
    }

    using Parent::keys;
    using Parent::selection;

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ProductMultiplicityMetadata& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ProductMultiplicityMetadata& right ) const {

      return ! this->operator==( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
