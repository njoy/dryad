#ifndef NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYCOVARIANCEMATRIX
#define NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYCOVARIANCEMATRIX

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/EnergyGroup.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/ProductMultiplicityMetadata.hpp"
#include "njoy/dryad/covariance/base/CovarianceMatrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief A covariance matrix for product multiplicities
   */
  class ProductMultiplicityCovarianceMatrix :
    protected base::CovarianceMatrix< ProductMultiplicityMetadata,
                                      id::ReactionID, id::EnergyGroup, id::ParticleID > {

    /* type aliases */

    using Parent = base::CovarianceMatrix< ProductMultiplicityMetadata,
                                           id::ReactionID, id::EnergyGroup, id::ParticleID >;

    /* fields */

    /* auxiliary functions */

    /* constructor */

    ProductMultiplicityCovarianceMatrix( Parent&& base ) :
      Parent( std::move( base ) ) {}

  public:

    /* constructor */

    public:

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ProductMultiplicityCovarianceMatrix() = default;

    ProductMultiplicityCovarianceMatrix( const ProductMultiplicityCovarianceMatrix& ) = default;
    ProductMultiplicityCovarianceMatrix( ProductMultiplicityCovarianceMatrix&& ) = default;

    ProductMultiplicityCovarianceMatrix& operator=( const ProductMultiplicityCovarianceMatrix& ) = default;
    ProductMultiplicityCovarianceMatrix& operator=( ProductMultiplicityCovarianceMatrix&& ) = default;

    /**
     *  @brief Constructor for an on-diagonal product multiplicity covariance matrix
     *
     *  @param[in] metadata      the row and column metadata
     *  @param[in] covariances   the covariance matrix
     *  @param[in] relative      the relative covariance flag (default is true)
     */
    ProductMultiplicityCovarianceMatrix( ProductMultiplicityMetadata metadata,
                                         matrix::Matrix< double > covariances,
                                         bool relative = true ) :
      Parent( std::move( metadata ), std::move( covariances ), relative ) {}

    /**
     *  @brief Constructor for an off-diagonal product multiplicity covariance matrix
     *
     *  @param[in] rowMetadata      the row metadata
     *  @param[in] columnMetadata   the column metadata
     *  @param[in] covariances      the covariance matrix
     *  @param[in] relative         the relative covariance flag (default is true)
     */
    ProductMultiplicityCovarianceMatrix( ProductMultiplicityMetadata rowMetadata,
                                         ProductMultiplicityMetadata columnMetadata,
                                         matrix::Matrix< double > covariances,
                                         bool relative = true ) :
      Parent( std::move( rowMetadata ), std::move( columnMetadata ),
              std::move( covariances ), relative ) {}

    /**
     *  @brief Constructor for an on-diagonal product multiplicity correlation matrix
     *
     *  @param[in] metadata       the row and column metadata
     *  @param[in] deviations     the standard deviations
     *  @param[in] correlations   the correlation matrix
     *  @param[in] relative       the relative covariance flag (default is true)
     */
    ProductMultiplicityCovarianceMatrix( ProductMultiplicityMetadata metadata,
                                         std::vector< double > deviations,
                                         matrix::Matrix< double > correlations,
                                         bool relative = true ) :
      Parent( std::move( metadata ), std::move( deviations ),
              std::move( correlations ), relative ) {}

    /**
     *  @brief Constructor for an off-diagonal product multiplicity correlation matrix
     *
     *  @param[in] rowMetadata        the row metadata
     *  @param[in] columnMetadata     the column metadata
     *  @param[in] rowDeviations      the standard deviations to be applied to each row
     *  @param[in] columnDeviations   the standard deviations to be applied to each column
     *  @param[in] correlations       the correlation matrix
     *  @param[in] relative           the relative covariance flag (default is true)
     */
    ProductMultiplicityCovarianceMatrix( ProductMultiplicityMetadata rowMetadata,
                                         ProductMultiplicityMetadata columnMetadata,
                                         const std::vector< double >& rowDeviations,
                                         const std::vector< double >& columnDeviations,
                                         matrix::Matrix< double > correlations,
                                         bool relative = true ) :
      Parent( std::move( rowMetadata ), std::move( columnMetadata ),
              rowDeviations, columnDeviations,
              std::move( correlations ), relative ) {}

    /**
     *  @brief Constructor using eigenvalues and eigenvectors for an on-diagonal
     *         product multiplicity covariance matrix
     *
     *  @param[in] metadata       the row and column metadata
     *  @param[in] eigenvalues    the eigenvalues
     *  @param[in] eigenvectors   the associated eigenvectors
     *  @param[in] relative       the relative covariance flag
     */
    ProductMultiplicityCovarianceMatrix( ProductMultiplicityMetadata metadata,
                                         std::vector< double > eigenvalues,
                                         std::vector< matrix::Vector< double > > eigenvectors,
                                         bool relative = true ) :
      Parent( std::move( metadata ), std::move( eigenvalues ),
              std::move( eigenvectors ), relative ) {}

    /* methods */

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
    ProductMultiplicityCovarianceMatrix
    extract( const std::optional< id::ReactionID >& reaction,
             const std::optional< id::EnergyGroup >& group,
             const std::optional< id::ParticleID >& product ) const {

      return Parent::extract( reaction, group, product );
    }

    /**
     *  @brief Extract a submatrix from the covariance matrix based
     *         on selected values of the keys
     */
    ProductMultiplicityCovarianceMatrix
    extract( const std::optional< id::ReactionID >& rowReaction,
             const std::optional< id::EnergyGroup >& rowGroup,
             const std::optional< id::ParticleID >& rowProduct,
             const std::optional< id::ReactionID >& colReaction,
             const std::optional< id::EnergyGroup >& colGroup,
             const std::optional< id::ParticleID >& colProduct ) const {

      return Parent::extract( rowReaction, rowGroup, rowProduct,
                              colReaction, colGroup, colProduct );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ProductMultiplicityCovarianceMatrix& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ProductMultiplicityCovarianceMatrix& right ) const {

      return ! this->operator==( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
