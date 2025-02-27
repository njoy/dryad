#ifndef NJOY_DRYAD_COVARIANCE_COVARIANCEBLOCK
#define NJOY_DRYAD_COVARIANCE_COVARIANCEBLOCK

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/covariance/matrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief A base class representing a covariance matrix block with
   *         associated metadata
   *
   *  The only requirement on the Metadata template is that it has a size()
   *  function.
   */
  template < typename Metadata >
  class CovarianceBlock {

    /* fields - meta data */
    Metadata row_;
    std::optional< Metadata > column_;
    bool relative_;

    /* fields - covariance matrix */
    std::optional< Matrix< double > > covariances_;

    /* fields - standard deviations and correlations */
    std::optional< std::vector< double > > sigmas_;
    std::optional< Matrix< double > > correlations_;

    /* fields - eigenvalues */
    std::optional< std::vector< double > > eigenvalues_;

    /* auxiliary function */
    #include "dryad/covariance/CovarianceBlock/src/verifyMatrix.hpp"
    #include "dryad/covariance/CovarianceBlock/src/verifyStandardDeviations.hpp"

  public:

    /* constructor */
    #include "dryad/covariance/CovarianceBlock/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the row metadata
     */
    const Metadata& rowMetadata() const { return this->row_; }

    /**
     *  @brief Return the column metadata
     *
     *  This returns the row metadata if the covariance block is a diagonal block
     */
    const Metadata& columnMetadata() const {

      if ( this->column_ ) {

        return this->column_.value();
      }
      else {

        return this->row_;
      }
    }

    /**
     *  @brief Return whether or not this covariance block is an off diagonal block
     */
    bool isOffDiagonalBlock() const {

      return this->column_.has_value();
    }

    /**
     *  @brief Return whether or not this covariance block is a diagonal block
     */
    bool isDiagonalBlock() const {

      return ! this->isOffDiagonalBlock();
    }

    /**
     *  @brief Return whether or not this covariance block is relative or not
     */
    bool isRelativeBlock() const {

      return this->relative_;
    }

    /**
     *  @brief Return the covariance matrix
     */
    const std::optional< Matrix< double > >& covariances() const {

      return this->covariances_;
    }

    /**
     *  @brief Return the standard deviations
     */
    const std::optional< std::vector< double > >& standardDeviations() const {

      return this->sigmas_;
    }

    /**
     *  @brief Return the correlation matrix
     */
    const std::optional< Matrix< double > >& correlations() const {

      return this->correlations_;
    }

    /**
     *  @brief Return the eigenvalues
     */
    const std::optional< std::vector< double > >& eigenvalues() const {

      return this->eigenvalues_;
    }

    #include "dryad/covariance/CovarianceBlock/src/calculateStandardDeviations.hpp"
    #include "dryad/covariance/CovarianceBlock/src/calculateCorrelations.hpp"
    #include "dryad/covariance/CovarianceBlock/src/calculateEigenvalues.hpp"
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
