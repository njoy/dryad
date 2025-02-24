#ifndef NJOY_DRYAD_COVARIANCE_CROSSSECTIONCOVARIANCEBLOCK
#define NJOY_DRYAD_COVARIANCE_CROSSSECTIONCOVARIANCEBLOCK

// system includes

// other includes
#include "tools/Log.hpp"
#include "dryad/covariance/CrossSectionMetaData.hpp"
#include "dryad/covariance/CovarianceBlock.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief A cross section covariance covariance matrix block
   */
  class CrossSectionCovarianceBlock :
    protected CovarianceBlock< CrossSectionMetaData > {

  public:

    /* constructor */
    #include "dryad/covariance/CrossSectionCovarianceBlock/src/ctor.hpp"

    /* methods */

    using CovarianceBlock::rowMetadata;
    using CovarianceBlock::columnMetadata;
    using CovarianceBlock::isOffDiagonalBlock;
    using CovarianceBlock::isDiagonalBlock;
    using CovarianceBlock::isRelativeBlock;
    using CovarianceBlock::covariances;
    using CovarianceBlock::standardDeviations;
    using CovarianceBlock::correlations;
    using CovarianceBlock::eigenvalues;
    using CovarianceBlock::calculateStandardDeviations;
    using CovarianceBlock::calculateCorrelations;
    using CovarianceBlock::calculateEigenvalues;
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
