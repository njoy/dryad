#ifndef NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYCOVARIANCEDATA
#define NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYCOVARIANCEDATA

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/EnergyGroup.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/id/ReactionID.hpp"
#include "dryad/covariance/base/CovarianceMatrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief A covariance matrix for product multiplicities
   */
  class ProductMultiplicityCovarianceMatrix :
    protected base::CovarianceMatrix< id::ReactionID, id::EnergyGroup, id::ParticleID > {

    /* type aliases */

    using Parent = base::CovarianceMatrix< id::ReactionID, id::EnergyGroup, id::ParticleID >;
    using Key = Parent::Key;

    /* fields */
    id::ReactionID reaction_;
    std::vector< double > energies_;
    std::vector< id::ParticleID > products_;

    /* auxiliary functions */

    #include "dryad/covariance/ProductMultiplicityCovarianceMatrix/src/generateKeys.hpp"
    #include "dryad/covariance/ProductMultiplicityCovarianceMatrix/src/generateMetadata.hpp"

  public:

    /* constructor */

    #include "dryad/covariance/ProductMultiplicityCovarianceMatrix/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the reaction identifier
     */
    const id::ReactionID& reactionIdentifier() const {

      return this->reaction_;
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

    using Parent::rowKeys;
    using Parent::columnKeys;
    using Parent::isRelativeMatrix;
    using Parent::isAbsoluteMatrix;
    using Parent::isOnDiagonal;
    using Parent::isOffDiagonal;
    using Parent::covariances;
    using Parent::standardDeviations;
    using Parent::correlations;
    using Parent::eigenvalues;
    using Parent::calculateStandardDeviations;
    using Parent::calculateCorrelations;
    using Parent::calculateEigenvalues;

    #include "dryad/covariance/ProductMultiplicityCovarianceMatrix/src/extract.hpp"

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ProductMultiplicityCovarianceMatrix& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ProductMultiplicityCovarianceMatrix& right ) const {

      return ! this->operator==( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
