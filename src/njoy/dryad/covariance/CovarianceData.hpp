#ifndef NJOY_DRYAD_COVARIANCE_COVARIANCEDATA
#define NJOY_DRYAD_COVARIANCE_COVARIANCEDATA

// system includes
#include <optional>

// other includes
#include "njoy/dryad/covariance/CrossSectionCovarianceData.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief The covariance data
   */
  class CovarianceData {

    /* fields */

    std::optional< CrossSectionCovarianceData > xs_;

    /* auxiliary functions */

  public:

    /* constructor */

    #include "njoy/dryad/covariance/CovarianceData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the cross section covariances
     */
    const std::optional< CrossSectionCovarianceData >& crossSectionCovariances() const {

      return this->xs_;
    }

    /**
     *  @brief Return the cross section covariances
     */
    std::optional< CrossSectionCovarianceData >& crossSectionCovariances() {

      return this->xs_;
    }

    /**
     *  @brief Return whether or not there are cross section covariances
     */
    bool hasCrossSectionCovariances() const {

      return this->crossSectionCovariances().has_value();
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CovarianceData& right ) const {

      return this->crossSectionCovariances() == right.crossSectionCovariances();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CovarianceData& right ) const {

      return ! this->operator==( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
