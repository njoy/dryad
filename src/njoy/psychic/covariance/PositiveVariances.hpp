#ifndef NJOY_PSYCHIC_COVARIANCE_POSITIVEVARIANCES
#define NJOY_PSYCHIC_COVARIANCE_POSITIVEVARIANCES

// system includes

// other includes
#include "scion/math/compare.hpp"
#include "njoy/psychic/base/Test.hpp"
#include "njoy/psychic/TestStatus.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceMatrix.hpp"
#include "njoy/dryad/covariance/ProductMultiplicityCovarianceMatrix.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace psychic {
namespace covariance {

  /**
   *  @class
   *  @brief Test to verify if all variances are strictly positive
   */
  class PositiveVariances : protected base::Test< PositiveVariances > {

    /* friend declarations */
    friend class base::Test< PositiveVariances >;

    /* type aliases */
    using Parent = base::Test< PositiveVariances >;

    /* fields */

    // test tolerances

    // test result information

    /* auxiliary functions */

    /**
     *  @brief Reset the test result information
     */
    void reset() {}

  public:

    /* constructor */

    /**
     *  @brief Constructor
     */
    PositiveVariances() :
      Parent( "psychic.covariance.PositiveVariances" ) {}

    /* methods */

    using Parent::name;
    using Parent::status;
    using Parent::clear;

    /**
     *  @brief Verify if the provided covariance matrix has variances that are strictly positive
     *
     *  This test can be run only for on-diagonal covariance matrices if the eigenvalues are
     *  available.
     *
     *  The test returns the following status values:
     *    - Success : all variances are strictly positive
     *    - Warning : all variances are positive
     *    - Fail : some of the variances seem to be negative
     *    - Skipped : the test was skipped
     *
     *  @param[in] covariance   the covariance matrix instance to be tested
     */
    template < typename Covariance >
    auto operator()( const Covariance& covariance )
    -> std::enable_if_t< std::is_same_v< Covariance, dryad::covariance::CrossSectionCovarianceMatrix > ||
                         std::is_same_v< Covariance, dryad::covariance::AngularDistributionCovarianceMatrix > ||
                         std::is_same_v< Covariance, dryad::covariance::ProductMultiplicityCovarianceMatrix >,
                         const std::optional< TestStatus >& > {

      this->clear();
      this->status( TestStatus::Success );

      if ( covariance.isOnDiagonal() ) {

        for ( double value : covariance.covariances().diagonal() ) {

          if ( value <= 0. ) {

            this->status( value < 0. ? TestStatus::Fail : TestStatus::Warning );
            break;
          }
        }
      }
      else {

        this->status( TestStatus::Skipped );
      }

      return this->status();
    }
  };

} // covariance namespace
} // psychic namespace
} // njoy namespace

#endif
