#ifndef NJOY_PSYCHIC_COVARIANCE_BOUNDEDCORRELATIONS
#define NJOY_PSYCHIC_COVARIANCE_BOUNDEDCORRELATIONS

// system includes

// other includes
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
   *  @brief Test to verify if all correlation values are between -1 and 1
   */
  class BoundedCorrelations : protected base::Test< BoundedCorrelations > {

    /* friend declarations */
    friend class base::Test< BoundedCorrelations >;

    /* type aliases */
    using Parent = base::Test< BoundedCorrelations >;

    /* fields */

    // test tolerances
    double tolerance_;

    // test result information
    std::optional< double > smallest_correlation_;
    std::optional< double > largest_correlation_;

    /* auxiliary functions */

    /**
     *  @brief Reset the test result information
     */
    void reset() {

      this->smallestCorrelation( std::nullopt );
      this->largestCorrelation( std::nullopt );
    }

  public:

    /* constructor */

    BoundedCorrelations( double tolerance = constants::psychic::tolerance ) :
      Parent( "psychic.covariance.BoundedCorrelations" ),
      tolerance_( tolerance ) {}

    /* methods */

    using Parent::name;
    using Parent::status;
    using Parent::clear;

    /**
     *  @brief Return the comparison tolerance
     */
    double tolerance() const {

      return this->tolerance_;
    }

    /**
     *  @brief Return the smallest correlation value that was found
     */
    const std::optional< double >& smallestCorrelation() const {

      return this->smallest_correlation_;
    }

    /**
     *  @brief Set the smallest correlation value that was found
     *
     *  @param[in] correlation   the correlation value
     */
    void smallestCorrelation( std::optional< double > correlation ) {

      this->smallest_correlation_ = std::move( correlation );
    }

    /**
     *  @brief Return the largest correlation value that was found
     */
    const std::optional< double >& largestCorrelation() const {

      return this->largest_correlation_;
    }

    /**
     *  @brief Set the largest correlation value that was found
     *
     *  @param[in] correlation   the correlation value
     */
    void largestCorrelation( std::optional< double > correlation ) {

      this->largest_correlation_ = std::move( correlation );
    }

    /**
     *  @brief Verify if the provided covariance matrix has correlations between -1 and 1
     *
     *  This test can be run for on-diagonal and off-diagonal covariance matrices if the
     *  correlations are available.
     *
     *  The test returns the following status values:
     *    - Success : the correlations are between -1 and 1
     *    - Warning : the correlations are between -1 and 1, taking into account a tolerance
     *    - Fail : the correlations matrix are outside the -1 and 1 range
     *    - Skipped : the test was skipped
     *
     *  The smallest and largest correlation values are available for the Warning and Fail state.
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
      if ( covariance.correlations().has_value() ) {

        this->status( TestStatus::Success );

        auto min = covariance.correlations()->minCoeff();
        auto max = covariance.correlations()->maxCoeff();

        if ( min < -1. ) {

          this->smallestCorrelation( min );
          this->status( min < -1. - this->tolerance() ? TestStatus::Fail : TestStatus::Warning );
        }
        if ( max > +1. ) {

          this->largestCorrelation( max );
          this->status( this->status() && max > +1. + this->tolerance() ? TestStatus::Fail : TestStatus::Warning );
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
