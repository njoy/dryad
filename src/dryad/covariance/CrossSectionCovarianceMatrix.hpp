#ifndef NJOY_DRYAD_COVARIANCE_CROSSSECTIONCOVARIANCEMATRIX
#define NJOY_DRYAD_COVARIANCE_CROSSSECTIONCOVARIANCEMATRIX

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/covariance/VarianceScaling.hpp"
#include "dryad/covariance/CrossSectionMetadata.hpp"
#include "dryad/covariance/base/CovarianceMatrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief A cross section covariance matrix block
   */
  class CrossSectionCovarianceMatrix :
    protected base::CovarianceMatrix< CrossSectionMetadata,
                                      id::ReactionID, id::EnergyGroup > {

    /* type aliases */

    using Parent = base::CovarianceMatrix< CrossSectionMetadata,
                                           id::ReactionID, id::EnergyGroup >;

    /* fields */
    std::optional< VarianceScaling > scaling_;

    /* auxiliary functions */

  public:

    /* constructor */

    #include "dryad/covariance/CrossSectionCovarianceMatrix/src/ctor.hpp"

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
    using Parent::calculateStandardDeviations;
    using Parent::calculateCorrelations;
    using Parent::calculateEigenvalues;

    #include "dryad/covariance/CrossSectionCovarianceMatrix/src/extract.hpp"

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CrossSectionCovarianceMatrix& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CrossSectionCovarianceMatrix& right ) const {

      return ! this->operator==( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
