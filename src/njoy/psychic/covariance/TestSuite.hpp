#ifndef NJOY_PSYCHIC_COVARIANCE_TESTSUITE
#define NJOY_PSYCHIC_COVARIANCE_TESTSUITE

// system includes

// other includes
#include "njoy/psychic/base/Test.hpp"
#include "njoy/psychic/TestStatus.hpp"
#include "njoy/psychic/covariance/TestSuite.hpp"
#include "njoy/psychic/covariance/PositiveVariances.hpp"
#include "njoy/psychic/covariance/PositiveSemiDefinite.hpp"
#include "njoy/psychic/covariance/BoundedCorrelations.hpp"
#include "njoy/psychic/covariance/DiagonalCorrelations.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"
#include "njoy/dryad/covariance/ProductMultiplicityCovarianceMatrix.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace psychic {
namespace covariance {

  /**
   *  @class
   *  @brief A comprehensive covariance test suite
   */
  class TestSuite : protected base::Test< TestSuite > {

    /* friend declarations */
    friend class base::Test< TestSuite >;

    /* type aliases */
    using Parent = base::Test< TestSuite >;

    /* fields */

    PositiveVariances positive_variances_;
    PositiveSemiDefinite positive_semi_definite_;
    BoundedCorrelations bounded_correlations_;
    DiagonalCorrelations diagonal_correlations_;

    /* auxiliary functions */

    /**
     *  @brief Reset the test result information
     */
    void reset() {

      this->positiveVariances().clear();
      this->positiveSemiDefinite().clear();
      this->boundedCorrelations().clear();
      this->diagonalCorrelations().clear();
    }

  public:

    /* constructor */

    TestSuite( double tolerance = constants::psychic::tolerance,
               double negative = constants::psychic::largest_allowed_negative_eigenvalue ) :
      Parent( "psychic.covariance.TestSuite" ),
      positive_variances_(),
      positive_semi_definite_( negative ),
      bounded_correlations_( tolerance ),
      diagonal_correlations_( tolerance ) {}

    /* methods */

    using Parent::name;
    using Parent::status;
    using Parent::clear;

    PositiveVariances& positiveVariances() { return this->positive_variances_; }
    PositiveSemiDefinite& positiveSemiDefinite() { return this->positive_semi_definite_; }
    BoundedCorrelations& boundedCorrelations() { return this->bounded_correlations_; }
    DiagonalCorrelations& diagonalCorrelations() { return this->diagonal_correlations_; }

    /**
     *  @brief Perform the test suite on the provided covariance matrix
     *
     *  @param[in] covariance   the covariance matrix instance to be tested
     */
    template < typename Covariance >
    auto operator()( const Covariance& covariance )
    -> std::enable_if_t< std::is_same_v< Covariance, dryad::covariance::CrossSectionCovarianceMatrix > ||
                         std::is_same_v< Covariance, dryad::covariance::ProductMultiplicityCovarianceMatrix >,
                         const std::optional< TestStatus >& > {

      this->clear();
      this->status( this->positiveVariances()( covariance ).value() );
      this->status( this->positiveSemiDefinite()( covariance ).value() && this->status().value() );
      this->status( this->boundedCorrelations()( covariance ).value() && this->status().value() );
      this->status( this->diagonalCorrelations()( covariance ).value() && this->status().value() );

      return this->status();
    }
  };

} // covariance namespace
} // psychic namespace
} // njoy namespace

#endif
