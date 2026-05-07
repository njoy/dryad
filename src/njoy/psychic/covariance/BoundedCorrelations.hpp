#ifndef NJOY_PSYCHIC_COVARIANCES_BOUNDEDCORRELATIONS
#define NJOY_PSYCHIC_COVARIANCES_BOUNDEDCORRELATIONS

// system includes

// other includes
#include "njoy/psychic/base/Test.hpp"
#include "njoy/psychic/TestStatus.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"
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
    void reset() {}

  public:

    /* constructor */

    BoundedCorrelations( double tolerance = constants::psychic::tolerance ) :
      Parent( "psychic.covariance.BoundedCorrelations" ),
      tolerance_( tolerance ) {}

    /* methods */

    using Parent::name;
    using Parent::status;

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
     *  @param[in] covariance   the covariance matrix instance to be tested
     */
    template < typename Covariance >
    auto operator()( const Covariance& covariance )
    -> std::enable_if_t< std::is_same_v< Covariance, dryad::covariance::CrossSectionCovarianceMatrix > ||
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
          if ( this->status() == TestStatus::Success || this->status() == TestStatus::Warning ) {

            this->status( max > +1. + this->tolerance() ? TestStatus::Fail : TestStatus::Warning );
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
