#ifndef NJOY_MEDIC_COVARIANCE_PRUNESMALLEIGENVALUES
#define NJOY_MEDIC_COVARIANCE_PRUNESMALLEIGENVALUES

// system includes
#include <vector>

// other includes
#include "njoy/matrix.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"
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
                       std::is_same_v< Covariance, dryad::covariance::ProductMultiplicityCovarianceMatrix >,
                       void > {

    if ( covariance.isOnDiagonal() &&
         covariance.eigenvalues().has_value() && covariance.eigenvectors().has_value() ) {

      decltype(auto) eigenvalues = covariance.eigenvalues().value();
      decltype(auto) eigenvectors = covariance.eigenvectors().value();

      auto iter = std::lower_bound( eigenvalues.rbegin(), eigenvalues.rend(), eigenvalue );
      if ( iter != eigenvalues.rend() ) {

        eigenvalues.erase( iter.base(), eigenvalues.end() );
        eigenvectors.erase( std::next( eigenvectors.begin(), eigenvalues.size() ), eigenvectors.end() );
        covariance.calculateCovariances();
        covariance.calculateCorrelations();
      }
      else {

        Log::error( "Pruning the eigenvalues would cause there to be no eigenvalues left" );
        Log::info( "Check eigenvalue threshold" );
        throw std::exception();
      }
    }
  }

} // covariance namespace
} // medic namespace
} // njoy namespace

#endif
