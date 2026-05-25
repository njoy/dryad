#ifndef NJOY_MEDIC_COVARIANCE_PRUNESMALLEIGENVALUES
#define NJOY_MEDIC_COVARIANCE_PRUNESMALLEIGENVALUES

// system includes
#include <vector>

// other includes
#include "njoy/matrix.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceMatrix.hpp"
#include "njoy/dryad/covariance/ProductMultiplicityCovarianceMatrix.hpp"

namespace njoy {
namespace medic {
namespace covariance {

  /**
   *  @brief Prune eigenvalues below a given value from the covariance matrix
   *
   *  @param[in] eigenvalue   the smallest allowed eigenvalue
   *  @param[in,out] matrix   the covariance matrix to be modified
   */
  template < typename Covariance >
  auto pruneSmallEigenvalues( double eigenvalue,
                              Covariance& covariance )
  -> std::enable_if_t< std::is_same_v< Covariance, dryad::covariance::CrossSectionCovarianceMatrix > ||
                       std::is_same_v< Covariance, dryad::covariance::AngularDistributionCovarianceMatrix > ||
                       std::is_same_v< Covariance, dryad::covariance::ProductMultiplicityCovarianceMatrix >,
                       void > {

    if ( covariance.isOnDiagonal() &&
         covariance.eigenvalues().has_value() && covariance.eigenvectors().has_value() ) {

      std::vector< double > eigenvalues = covariance.eigenvalues().value();
      std::vector< matrix::Vector< double > > eigenvectors = covariance.eigenvectors().value();

      auto iter = std::lower_bound( eigenvalues.rbegin(), eigenvalues.rend(), eigenvalue );
      eigenvalues.erase( iter.base(), eigenvalues.end() );
      eigenvectors.erase( std::next( eigenvectors.begin(), eigenvalues.size() ), eigenvectors.end() );

      covariance.eigendata( std::make_tuple( std::move( eigenvalues ), std::move( eigenvectors ) ) );
    }
  }

} // covariance namespace
} // medic namespace
} // njoy namespace

#endif
