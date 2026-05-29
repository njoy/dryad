#ifndef NJOY_DRYAD_COVARIANCE_COVARIANCEDATA
#define NJOY_DRYAD_COVARIANCE_COVARIANCEDATA

// system includes
#include <optional>
#include <tuple>

// other includes
#include "njoy/dryad/covariance/CrossSectionCovarianceData.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceData.hpp"

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
    std::optional< AngularDistributionCovarianceData > angular_;

    /* auxiliary functions */

  public:

    /* constructor */

    #include "njoy/dryad/covariance/CovarianceData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the cross section covariances
     */
    const std::optional< CrossSectionCovarianceData >& crossSection() const {

      return this->xs_;
    }

    /**
     *  @brief Return the cross section covariances
     */
    std::optional< CrossSectionCovarianceData >& crossSection() {

      return this->xs_;
    }

    /**
     *  @brief Return whether or not there are cross section covariances
     */
    bool hasCrossSectionCovariances() const {

      return this->crossSection().has_value();
    }

    /**
     *  @brief Return the angular distribution covariances
     */
    const std::optional< AngularDistributionCovarianceData >& angularDistribution() const {

      return this->angular_;
    }

    /**
     *  @brief Return the angular distribution covariances
     */
    std::optional< AngularDistributionCovarianceData >& angularDistribution() {

      return this->angular_;
    }

    /**
     *  @brief Return whether or not there are angular distribution covariances
     */
    bool hasAngularDistributionCovariances() const {

      return this->angularDistribution().has_value();
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CovarianceData& right ) const {

      return std::tie( this->crossSection(), this->angularDistribution() ) ==
             std::tie( right.crossSection(), right.angularDistribution() );
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
