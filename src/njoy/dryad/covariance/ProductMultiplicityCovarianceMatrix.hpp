#ifndef NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYCOVARIANCEMATRIX
#define NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYCOVARIANCEMATRIX

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/EnergyGroup.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/ProductMultiplicityMetadata.hpp"
#include "njoy/dryad/covariance/base/CovarianceMatrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief A covariance matrix for product multiplicities
   */
  class ProductMultiplicityCovarianceMatrix :
    protected base::CovarianceMatrix< ProductMultiplicityMetadata,
                                      id::ReactionID, id::EnergyGroup, id::ParticleID > {

    /* type aliases */

    using Parent = base::CovarianceMatrix< ProductMultiplicityMetadata,
                                           id::ReactionID, id::EnergyGroup, id::ParticleID >;

    /* fields */

    /* auxiliary functions */

  public:

    /* constructor */

    #include "njoy/dryad/covariance/ProductMultiplicityCovarianceMatrix/src/ctor.hpp"

    /* methods */

    using Parent::rowMetadata;
    using Parent::columnMetadata;
    using Parent::isRelativeMatrix;
    using Parent::isAbsoluteMatrix;
    using Parent::isOnDiagonal;
    using Parent::isOffDiagonal;
    using Parent::covariances;
    using Parent::standardDeviations;
    using Parent::correlations;
    using Parent::eigenvalues;
    using Parent::eigenvectors;
    using Parent::calculateStandardDeviations;
    using Parent::calculateCorrelations;
    using Parent::calculateEigenvalues;

    #include "njoy/dryad/covariance/ProductMultiplicityCovarianceMatrix/src/extract.hpp"

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
