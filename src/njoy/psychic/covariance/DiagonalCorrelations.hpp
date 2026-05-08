#ifndef NJOY_PSYCHIC_COVARIANCE_DIAGONALCORRELATIONS
#define NJOY_PSYCHIC_COVARIANCE_DIAGONALCORRELATIONS

// system includes

// other includes
#include "scion/math/compare.hpp"
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
   *  @brief Test to verify if all diagonal correlation values are equal to 1
   */
  class DiagonalCorrelations : protected base::Test< DiagonalCorrelations > {

    /* friend declarations */
    friend class base::Test< DiagonalCorrelations >;

    /* type aliases */
    using Parent = base::Test< DiagonalCorrelations >;

    /* fields */

    // test tolerances
    double tolerance_;

    // test result information

    /* auxiliary functions */

    /**
     *  @brief Reset the test result information
     */
    void reset() {}

  public:

    /* constructor */

    DiagonalCorrelations( double tolerance = constants::psychic::tolerance ) :
      Parent( "psychic.covariance.DiagonalCorrelations" ),
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
     *  @brief Verify if the provided covariance matrix has diagonal correlations equal to 1
     *
     *  The test returns the following status values:
     *    - Success : all diagonal correlations are equal to 1
     *    - Warning : all diagonal correlations are equal to 1, taking into account a tolerance
     *    - Fail : not all diagonal correlations are equal to 1
     *    - Skipped : the test was skipped
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

        for ( double value : covariance.correlations()->diagonal() ) {

          if ( value != 1. ) {

            this->status( scion::math::isClose( value, 1., this->tolerance() ) ? TestStatus::Warning : TestStatus::Fail );
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
