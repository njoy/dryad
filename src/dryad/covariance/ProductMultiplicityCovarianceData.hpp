#ifndef NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYCOVARIANCEDATA
#define NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYCOVARIANCEDATA

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/EnergyGroup.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/covariance/base/CovarianceMatrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief A covariance matrix for product multiplicities
   */
  class ProductMultiplicityCovarianceData :
    protected base::CovarianceMatrix< std::tuple< id::EnergyGroup, id::ParticleID > > {

    /* type aliases */

    using Key = std::tuple< id::EnergyGroup, id::ParticleID >;
    using Parent = base::CovarianceMatrix< Key >;

    /* auxiliary functions */

    static std::vector< Key > generateKeys( std::vector< double > energies,
                                            std::vector< id::ParticleID > products ) {

      if ( energies.size() == 0 || products.size() == 0 ) {

        throw std::exception();
      }

      std::vector< Key > keys;
      keys.reserve( energies.size() * products.size() );
      for ( unsigned int i = 0; i < energies.size() - 1; ++i ) {

        for ( unsigned int j = 0; j < products.size(); ++j ) {

          keys.emplace_back( id::EnergyGroup( energies[i], energies[i+1] ), products[j] );
        }
      }

      return keys;
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ProductMultiplicityCovarianceData() = default;

    ProductMultiplicityCovarianceData( const ProductMultiplicityCovarianceData& ) = default;
    ProductMultiplicityCovarianceData( ProductMultiplicityCovarianceData&& ) = default;

    ProductMultiplicityCovarianceData& operator=( const ProductMultiplicityCovarianceData& ) = default;
    ProductMultiplicityCovarianceData& operator=( ProductMultiplicityCovarianceData&& ) = default;

    /**
     *  @brief Constructor for an on-diagonal covariance matrix (relative or absolute)
     *
     *  @param[in] keys          the keys associated with the covariance block
     *  @param[in] covariances   the covariance matrix
     *  @param[in] relative      the relative covariance flag
     */
    ProductMultiplicityCovarianceData( std::vector< Key > keys,
                                       Matrix< double > covariances,
                                       bool relative = true ) :
      Parent( std::move( keys ), std::move( covariances ), relative ) {}

    /**
     *  @brief Constructor for product multiplicity covariance data
     *
     *  @param[in] energies      the group structure
     *  @param[in] products      the product identifiers
     *  @param[in] covariances   the covariance matrix
     *  @param[in] relative      the relative covariance flag
     */
    ProductMultiplicityCovarianceData( std::vector< double > energies,
                                       std::vector< id::ParticleID > products,
                                       Matrix< double > covariances,
                                       bool relative = true ) :
        ProductMultiplicityCovarianceData(
            generateKeys( std::move( energies ), std::move( products ) ),
            std::move( covariances ) ) {}

    /* methods */

    using Parent::rowKeys;
    using Parent::columnKeys;
    using Parent::isRelativeBlock;
    using Parent::isAbsoluteBlock;
    using Parent::covariances;
    using Parent::standardDeviations;
    using Parent::correlations;
    using Parent::eigenvalues;
    using Parent::calculateStandardDeviations;
    using Parent::calculateCorrelations;
    using Parent::calculateEigenvalues;
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
