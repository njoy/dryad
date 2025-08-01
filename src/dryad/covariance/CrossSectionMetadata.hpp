#ifndef NJOY_DRYAD_COVARIANCE_CROSSSECTIONMETADATA
#define NJOY_DRYAD_COVARIANCE_CROSSSECTIONMETADATA

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "dryad/id/ParticleID.hpp"
#include "dryad/id/ReactionID.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief Metadata for the rows or columns of a cross section
   *         covariance matrix block
   */
  class CrossSectionMetadata {

    /* fields */
    id::ParticleID projectile_id_;
    id::ParticleID target_id_;
    id::ReactionID reaction_id_;
    std::vector< double > energies_;

    /* auxiliary function */
    #include "dryad/covariance/CrossSectionMetadata/src/verifyEnergies.hpp"

  public:

    /* constructor */
    #include "dryad/covariance/CrossSectionMetadata/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the projectile identifier
     */
    const id::ParticleID& projectileIdentifier() const {

      return this->projectile_id_;
    }

    /**
     *  @brief Return the target identifier
     */
    const id::ParticleID& targetIdentifier() const {

      return this->target_id_;
    }

    /**
     *  @brief Return the reaction identifier
     */
    const id::ReactionID& reactionIdentifier() const {

      return this->reaction_id_;
    }

    /**
     *  @brief Return the energy group boundaries
     */
    const std::vector< double >& energies() const {

      return this->energies_;
    }

    /**
     *  @brief Return the number of energy groups
     */
    std::size_t numberGroups() const {

      return this->energies().size() - 1;
    }

    /**
     *  @brief Return the size
     */
    std::size_t size() const {

      return this->numberGroups();
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
