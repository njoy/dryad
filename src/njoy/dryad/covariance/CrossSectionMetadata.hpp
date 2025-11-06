#ifndef NJOY_DRYAD_COVARIANCE_CROSSSECTIONMETADATA
#define NJOY_DRYAD_COVARIANCE_CROSSSECTIONMETADATA

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/EnergyGroup.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/base/Metadata.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief Covariance metadata for cross sections
   */
  class CrossSectionMetadata :
    protected base::Metadata< id::ReactionID, id::EnergyGroup > {

    /* type aliases */

    using Parent = base::Metadata< id::ReactionID, id::EnergyGroup >;

    /* fields */

    std::vector< id::ReactionID > reactions_;
    std::vector< double > energies_;

    /* auxiliary functions */

    #include "njoy/dryad/covariance/CrossSectionMetadata/src/generateEnergyGroups.hpp"
    #include "njoy/dryad/covariance/CrossSectionMetadata/src/generateKeys.hpp"
    #include "njoy/dryad/covariance/CrossSectionMetadata/src/updateMetadata.hpp"

  public:

    /* constructor */
    #include "njoy/dryad/covariance/CrossSectionMetadata/src/ctor.hpp"

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

    using Parent::keys;
    using Parent::selection;

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CrossSectionMetadata& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CrossSectionMetadata& right ) const {

      return ! this->operator==( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
