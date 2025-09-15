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
    protected base::CovarianceMatrix< 3 > {

    /* type aliases */

    using Parent = base::CovarianceMatrix< 3 >;

    /* fields */
    id::ReactionID reaction_;
    std::vector< double > energies_;
    std::vector< id::ParticleID > products_;

    /* auxiliary functions */

    #include "dryad/covariance/ProductMultiplicityCovarianceMatrix/src/generateKeys.hpp"

  public:

    /* constructor */

    #include "dryad/covariance/ProductMultiplicityCovarianceMatrix/src/ctor.hpp"

    /* methods */

    using Parent::rowKeys;
    using Parent::columnKeys;
    using Parent::isRelativeBlock;
    using Parent::isAbsoluteBlock;
    using Parent::isOnDiagonal;
    using Parent::isOffDiagonal;
    using Parent::covariances;
    using Parent::standardDeviations;
    using Parent::correlations;
    using Parent::eigenvalues;
    using Parent::calculateStandardDeviations;
    using Parent::calculateCorrelations;
    using Parent::calculateCovariances;
    using Parent::calculateEigenvalues;
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
