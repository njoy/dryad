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
   *  @brief Metadata for the rows or columns of a covariance matrix block
   *         for cross section data
   */
  class CrossSectionMetaData {

    /* fields */
    id::ParticleID nuclide_;
    id::ReactionID reaction_;
    std::vector< double > energies_;

    /* auxiliary function */
    #include "dryad/covariance/CrossSectionMetaData/src/verifyEnergies.hpp"

  public:

    /* constructor */
    #include "dryad/covariance/CrossSectionMetaData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the nuclide identifier
     */
    const id::ParticleID& nuclideIdentifier() const { return this->nuclide_; }

    /**
     *  @brief Return the reaction identifier
     */
    const id::ReactionID& reactionIdentifier() const { return this->reaction_; }

    /**
     *  @brief Return the energy group boundaries
     */
    const std::vector< double >& energies() const { return this->energies_; }

    /**
     *  @brief Return the number of energy groups
     */
    std::size_t numberGroups() const { return this->energies().size() - 1; }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
