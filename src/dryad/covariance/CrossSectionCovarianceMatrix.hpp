#ifndef NJOY_DRYAD_COVARIANCE_CROSSSECTIONCOVARIANCEBLOCK
#define NJOY_DRYAD_COVARIANCE_CROSSSECTIONCOVARIANCEBLOCK

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/covariance/VarianceScaling.hpp"
#include "dryad/covariance/CrossSectionMetadata.hpp"
#include "dryad/covariance/CovarianceBlock.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief A cross section covariance matrix block
   */
  class CrossSectionCovarianceBlock :
    protected CovarianceBlock< CrossSectionMetadata > {

    /* fields */
    std::optional< VarianceScaling > scaling_;

  public:

    /* constructor */
    #include "dryad/covariance/CrossSectionCovarianceBlock/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the variance scaling information
     *
     *  If this type of information is given, it will be for an on-diagonal
     *  covariance block.
     */
    const std::optional< VarianceScaling >& varianceScaling() const {

      return this->scaling_;
    }

    /**
     *  @brief Return whether or not the covariance block has variance scaling
     *         information
     */
    bool hasVarianceScaling() const {

      return this->scaling_.has_value();
    }

    using CovarianceBlock::rowMetadata;
    using CovarianceBlock::columnMetadata;
    using CovarianceBlock::isOffDiagonalBlock;
    using CovarianceBlock::isDiagonalBlock;
    using CovarianceBlock::isRelativeBlock;
    using CovarianceBlock::isAbsoluteBlock;
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
