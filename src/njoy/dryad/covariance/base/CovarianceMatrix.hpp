#ifndef NJOY_DRYAD_COVARIANCE_BASE_COVARIANCEMATRIX
#define NJOY_DRYAD_COVARIANCE_BASE_COVARIANCEMATRIX

// system includes
#include <algorithm>
#include <optional>
#include <numeric>
#include <vector>

// other includes
#include "scion/math/compare.hpp"
#include "tools/Log.hpp"
#include "tools/apply_permutation.hpp"
#include "njoy/matrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {
namespace base {

  /**
   *  @class
   *  @brief A base class representing a covariance matrix
   *
   *  For on-diagonal covariance matrice, the following data is always available
   *  (regardless of how the covariance matrix instance was constructed):
   *  - the covariance matrix
   *  - the standard deviations and correlation matrix
   *  - the eigenvalues and eigenvectors
   *
   *  Eigenvalues (and assocaited eigenvectors) are store in descending order.
   */
  template < typename Metadata, typename... Ts >
  class CovarianceMatrix {

    /* type aliases */
    using Key = std::tuple< Ts... >;
    using Selection = std::tuple< std::optional< Ts >... >;

    using Eigenvalues = std::optional< std::vector< double > >;
    using Eigenvectors = std::optional< std::vector< matrix::Vector< double > > >;
    using Eigendata = std::tuple< Eigenvalues, Eigenvectors >;

  private:

    /* fields - row and column metadata */
    Metadata row_metadata_;
    std::optional< Metadata > column_metadata_;

    /* fields - flag to indicate relative or absolute data */
    bool relative_;

    /* fields - covariance matrix */
    matrix::Matrix< double > covariances_;

    /* fields - standard deviations and correlations */
    std::optional< std::vector< double > > sigmas_;
    std::optional< matrix::Matrix< double > > correlations_;

    /* fields - eigenvalues and eigenvectors */
    Eigendata eigendata_;

    /* auxiliary function */
    #include "njoy/dryad/covariance/base/CovarianceMatrix/src/verifyMatrix.hpp"
    #include "njoy/dryad/covariance/base/CovarianceMatrix/src/verifyStandardDeviations.hpp"
    #include "njoy/dryad/covariance/base/CovarianceMatrix/src/sortEigenvalues.hpp"

  public:

    /* constructor */
    #include "njoy/dryad/covariance/base/CovarianceMatrix/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the row metadata
     */
    const Metadata& rowMetadata() const { return this->row_metadata_; }

    /**
     *  @brief Return the column metadata
     */
    const Metadata& columnMetadata() const {

      if ( this->column_metadata_.has_value() ) {

        return this->column_metadata_.value();
      }
      else {

        return this->row_metadata_;
      }
    }

    /**
     *  @brief Return whether or not this covariance matrix is off diagonal
     */
    bool isOffDiagonal() const {

      return this->column_metadata_.has_value();
    }

    /**
     *  @brief Return whether or not this covariance matrix is on diagonal
     */
    bool isOnDiagonal() const {

      return ! this->isOffDiagonal();
    }

    /**
     *  @brief Return whether or not this covariance matrix is relative or not
     */
    bool isRelativeMatrix() const {

      return this->relative_;
    }

    /**
     *  @brief Return whether or not this covariance matrix is absolute or not
     */
    bool isAbsoluteMatrix() const {

      return ! this->isRelativeMatrix();
    }

    /**
     *  @brief Return the covariance matrix
     */
    const matrix::Matrix< double >& covariances() const {

      return this->covariances_;
    }

    /**
     *  @brief Return the covariance matrix
     */
    matrix::Matrix< double >& covariances() {

      return this->covariances_;
    }

    /**
     *  @brief Set the covariance matrix
     *
     *  @param[in] covariances   the covariance matrix
     */
    void covariances( matrix::Matrix< double > covariances ) {

      this->covariances_ = std::move( covariances );
      if ( this->isOnDiagonal() ) {

        verifyMatrix( this->covariances(), this->rowMetadata().keys().size() );
        this->calculateCorrelations();
        this->calculateEigenvalues();
      }
      else {

        verifyMatrix( this->covariances(), this->rowMetadata().keys().size(),
                      this->columnMetadata().keys().size() );
        this->correlations( std::nullopt );
      }
    }

    /**
     *  @brief Return the standard deviations
     */
    const std::optional< std::vector< double > >& standardDeviations() const {

      return this->sigmas_;
    }

    /**
     *  @brief Return the standard deviations
     */
    std::optional< std::vector< double > >& standardDeviations() {

      return this->sigmas_;
    }

    /**
     *  @brief Set the standard deviations
     *
     *  @param[in] deviations   the standard deviations
     */
    void standardDeviations( std::optional< std::vector< double > > deviations ) {

      if ( this->isOnDiagonal() ) {

        this->sigmas_ = std::move( deviations );
        if ( this->standardDeviations().has_value() ) {

          verifyMatrix( this->standardDeviations().value(),
                        this->correlations().value(),
                        this->rowMetadata().keys().size() );
          this->calculateCovariances();
          this->calculateEigenvalues();
        }
      }
      else {

        throw std::runtime_error( "Standard deviations cannot be set for an off-diagonal covariance matrix" );
      }
    }

    /**
     *  @brief Return the correlation matrix
     */
    const std::optional< matrix::Matrix< double > >& correlations() const {

      return this->correlations_;
    }

    /**
     *  @brief Return the correlation matrix
     */
    std::optional< matrix::Matrix< double > >& correlations() {

      return this->correlations_;
    }

    /**
     *  @brief Set the correlation matrix
     *
     *  @param[in] correlations   the correlation matrix
     */
    void correlations( std::optional< matrix::Matrix< double > > correlations ) {

      if ( this->isOnDiagonal() ) {

        this->correlations_ = std::move( correlations );
        if ( this->correlations().has_value() ) {


          verifyMatrix( this->standardDeviations().value(),
                        this->correlations().value(),
                        this->rowMetadata().keys().size() );
          this->calculateCovariances();
          this->calculateEigenvalues();
        }
      }
      else {

        throw std::runtime_error( "Correlations cannot be set for an off-diagonal covariance matrix "
                                  "without specifying row and column deviations" );
      }
    }

    /**
     *  @brief Return the eigenvalues
     */
    const std::optional< std::vector< double > >& eigenvalues() const {

      return std::get< 0 >( this->eigendata_ );
    }

    /**
     *  @brief Return the eigenvalues
     */
    std::optional< std::vector< double > >& eigenvalues() {

      return std::get< 0 >( this->eigendata_ );
    }

    /**
     *  @brief Return the eigenvectors
     */
    const std::optional< std::vector< matrix::Vector< double > > >& eigenvectors() const {

      return std::get< 1 >( this->eigendata_ );
    }

    /**
     *  @brief Return the eigenvectors
     */
    std::optional< std::vector< matrix::Vector< double > > >& eigenvectors() {

      return std::get< 1 >( this->eigendata_ );
    }

    /**
     *  @brief Return the eigenvalues and eigenvectors
     */
    const Eigendata& eigendata() const {

      return this->eigendata_;
    }

    /**
     *  @brief Return the eigenvalues and eigenvectors
     */
    Eigendata& eigendata() {

      return this->eigendata_;
    }

    /**
     *  @brief Set the eigenvalues and eigenvectors
     *
     *  @param[in] eigenvalues    the eigenvalues
     *  @param[in] eigenvectors   the eigenvectors
     */
    void eigendata( Eigendata eigendata ) {

      if ( this->isOnDiagonal() ) {

        this->eigendata_ = std::move( eigendata );
        if ( this->eigenvalues().has_value() && this->eigenvectors().has_value() ) {

          verifyMatrix( this->eigenvalues().value(),
                        this->eigenvectors().value(),
                        this->rowMetadata().keys().size() );
          this->calculateCovariances();
          this->calculateCorrelations();
        }
      }
      else {

        throw std::runtime_error( "Eigenvalues and eigenvectors cannot be set for an off-diagonal "
                                  "covariance matrix" );
      }
    }

    #include "njoy/dryad/covariance/base/CovarianceMatrix/src/calculateCovariances.hpp"
    #include "njoy/dryad/covariance/base/CovarianceMatrix/src/calculateStandardDeviations.hpp"
    #include "njoy/dryad/covariance/base/CovarianceMatrix/src/calculateCorrelations.hpp"
    #include "njoy/dryad/covariance/base/CovarianceMatrix/src/calculateEigenvalues.hpp"

    #include "njoy/dryad/covariance/base/CovarianceMatrix/src/extract.hpp"

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CovarianceMatrix& right ) const {

      return std::tie( this->rowMetadata(), this->columnMetadata(), this->covariances(),
                       this->standardDeviations(), this->correlations(),
                       this->eigenvalues(), this->eigenvectors() ) ==
             std::tie( right.rowMetadata(), right.columnMetadata(), right.covariances(),
                       right.standardDeviations(), right.correlations(),
                       right.eigenvalues(), right.eigenvectors() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CovarianceMatrix& right ) const {

      return ! this->operator==( right );
    }
  };

} // base namespace
} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
