#ifndef NJOY_DRYAD_COVARIANCE_ANGULARDISTRIBUTIONCOVARIANCEMATRIX
#define NJOY_DRYAD_COVARIANCE_ANGULARDISTRIBUTIONCOVARIANCEMATRIX

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"
#include "njoy/dryad/id/EnergyGroup.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/AngularDistributionMetadata.hpp"
#include "njoy/dryad/covariance/base/CovarianceMatrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief A covariance matrix for angular distributions
   *
   *  This covariance matrix uses 3 dimensions as follows (from outer to inner
   *  dimension): the reactions, the Legendre moments and the energy groups.
   */
  class AngularDistributionCovarianceMatrix :
    protected base::CovarianceMatrix< AngularDistributionMetadata,
                                      id::ReactionID, std::size_t, id::EnergyGroup > {

    /* type aliases */

    using Parent = base::CovarianceMatrix< AngularDistributionMetadata,
                                           id::ReactionID, std::size_t, id::EnergyGroup >;

    /* fields */

    ReferenceFrame frame_;

    /* auxiliary functions */

    /* constructor */

    AngularDistributionCovarianceMatrix( Parent&& base, ReferenceFrame frame ) :
      Parent( std::move( base ) ), frame_( std::move( frame ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    AngularDistributionCovarianceMatrix() = default;

    AngularDistributionCovarianceMatrix( const AngularDistributionCovarianceMatrix& ) = default;
    AngularDistributionCovarianceMatrix( AngularDistributionCovarianceMatrix&& ) = default;

    AngularDistributionCovarianceMatrix& operator=( const AngularDistributionCovarianceMatrix& ) = default;
    AngularDistributionCovarianceMatrix& operator=( AngularDistributionCovarianceMatrix&& ) = default;

    /**
     *  @brief Constructor for an on-diagonal angular distribution covariance matrix
     *
     *  @param[in] frame         the reference frame of the covariance data
     *  @param[in] metadata      the row and column metadata
     *  @param[in] covariances   the covariance matrix
     *  @param[in] relative      the relative covariance flag (default is true)
     */
    AngularDistributionCovarianceMatrix( ReferenceFrame frame,
                                         AngularDistributionMetadata metadata,
                                         matrix::Matrix< double > covariances,
                                         bool relative = true) :
      Parent( std::move( metadata ), std::move( covariances ), relative ),
      frame_( std::move( frame ) ) {}

    /**
     *  @brief Constructor for an off-diagonal angular distribution covariance matrix
     *
     *  @param[in] frame            the reference frame of the covariance data
     *  @param[in] rowMetadata      the row metadata
     *  @param[in] columnMetadata   the column metadata
     *  @param[in] covariances      the covariance matrix
     *  @param[in] relative         the relative covariance flag (default is true)
     */
    AngularDistributionCovarianceMatrix( ReferenceFrame frame,
                                         AngularDistributionMetadata rowMetadata,
                                         AngularDistributionMetadata columnMetadata,
                                         matrix::Matrix< double > covariances,
                                         bool relative = true ) :
      Parent( std::move( rowMetadata ), std::move( columnMetadata ),
              std::move( covariances ), relative ),
      frame_( std::move( frame ) ) {}

    /**
     *  @brief Constructor for an on-diagonal angular distribution correlation matrix
     *
     *  @param[in] frame          the reference frame of the covariance data
     *  @param[in] metadata       the row and column metadata
     *  @param[in] deviations     the standard deviations
     *  @param[in] correlations   the correlation matrix
     *  @param[in] relative       the relative covariance flag (default is true)
     */
    AngularDistributionCovarianceMatrix( ReferenceFrame frame,
                                         AngularDistributionMetadata metadata,
                                         std::vector< double > deviations,
                                         matrix::Matrix< double > correlations,
                                         bool relative = true ) :
      Parent( std::move( metadata ), std::move( deviations ),
              std::move( correlations ), relative ),
      frame_( std::move( frame ) ) {}

    /**
     *  @brief Constructor for an off-diagonal angular distribution correlation matrix
     *
     *  @param[in] frame              the reference frame of the covariance data
     *  @param[in] rowMetadata        the row metadata
     *  @param[in] columnMetadata     the column metadata
     *  @param[in] rowDeviations      the standard deviations to be applied to each row
     *  @param[in] columnDeviations   the standard deviations to be applied to each column
     *  @param[in] correlations       the correlation matrix
     *  @param[in] relative           the relative covariance flag (default is true)
     */
    AngularDistributionCovarianceMatrix( ReferenceFrame frame,
                                         AngularDistributionMetadata rowMetadata,
                                         AngularDistributionMetadata columnMetadata,
                                         const std::vector< double >& rowDeviations,
                                         const std::vector< double >& columnDeviations,
                                         matrix::Matrix< double > correlations,
                                         bool relative = true ) :
      Parent( std::move( rowMetadata ), std::move( columnMetadata ),
              rowDeviations, columnDeviations,
              std::move( correlations ), relative ),
      frame_( std::move( frame ) ) {}

    /**
     *  @brief Constructor using eigenvalues and eigenvectors for an on-diagonal
     *         angular distribution covariance matrix
     *
     *  @param[in] frame          the reference frame of the covariance data
     *  @param[in] metadata       the row and column metadata
     *  @param[in] eigenvalues    the eigenvalues
     *  @param[in] eigenvectors   the associated eigenvectors
     *  @param[in] relative       the relative covariance flag
     */
    AngularDistributionCovarianceMatrix( ReferenceFrame frame,
                                         AngularDistributionMetadata metadata,
                                         std::vector< double > eigenvalues,
                                         std::vector< matrix::Vector< double > > eigenvectors,
                                         bool relative = true ) :
      Parent( std::move( metadata ), std::move( eigenvalues ),
              std::move( eigenvectors ), relative ),
      frame_( std::move( frame ) ) {}

    /* methods */

    /**
     *  @brief Return the reference frame
     */
    const ReferenceFrame& frame() const {

      return this->frame_;
    }

    /**
     *  @brief Set the reference frame
     *
     *  @param[in] frame   the reference frame of the covariance data
     */
    void frame( ReferenceFrame frame ) {

      this->frame_ = std::move( frame );
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
    using Parent::eigenvectors;
    using Parent::eigendata;
    using Parent::calculateCovariances;
    using Parent::calculateStandardDeviations;
    using Parent::calculateCorrelations;
    using Parent::calculateEigenvalues;

    /**
     *  @brief Extract a submatrix from the covariance matrix based
     *         on selected values of the keys
     */
    AngularDistributionCovarianceMatrix
    extract( const std::optional< id::ReactionID >& reaction,
             const std::optional< std::size_t >& moment,
             const std::optional< id::EnergyGroup >& group ) const {

      return AngularDistributionCovarianceMatrix(
               Parent::extract( reaction, moment, group ),
               this->frame() );
    }

    /**
     *  @brief Extract a submatrix from the covariance matrix based
     *         on selected values of the keys
     */
    AngularDistributionCovarianceMatrix
    extract( const std::optional< id::ReactionID >& rowReaction,
             const std::optional< std::size_t >& rowMoment,
             const std::optional< id::EnergyGroup >& rowGroup,
             const std::optional< id::ReactionID >& colReaction,
             const std::optional< std::size_t >& colMoment,
             const std::optional< id::EnergyGroup >& colGroup ) const {

      return AngularDistributionCovarianceMatrix(
               Parent::extract( rowReaction, rowMoment, rowGroup,
                              colReaction, colMoment, colGroup ),
               this->frame() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const AngularDistributionCovarianceMatrix& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const AngularDistributionCovarianceMatrix& right ) const {

      return ! this->operator==( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
