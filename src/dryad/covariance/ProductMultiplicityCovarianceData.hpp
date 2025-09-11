#ifndef NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYCOVARIANCEDATA
#define NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYCOVARIANCEDATA

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/covariance/EnergyGroup.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/covariance/base/CovarianceMatrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief A covariance matrix for product multiplicities
   */
  class ProductMultiplicityCovarianceData :
    protected base::CovarianceMatrix< std::tuple< EnergyGroup, id::ParticleID > > {

    /* type aliases */
    using Key = std::tuple< std::size_t, EnergyGroup, id::ParticleID >;
    using Parent = base::CovarianceMatrix< Key >;

  public:

    /* constructor */

    /* methods */

    using Parent::rowKeys;
    using Parent::columnKeys;
    using Parent::isRelativeBlock;
    using Parent::isAbsoluteBlock;
    using Parent::covariances;
    using Parent::standardDeviations;
    using Parent::correlations;
    using Parent::eigenvalues;
    using Parent::calculateStandardDeviations;
    using Parent::calculateCorrelations;
    using Parent::calculateEigenvalues;
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
