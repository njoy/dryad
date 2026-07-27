#ifndef NJOY_DRYAD_COVARIANCE_ANGULARDISTRIBUTIONCOVARIANCEDATA
#define NJOY_DRYAD_COVARIANCE_ANGULARDISTRIBUTIONCOVARIANCEDATA

// system includes
#include <vector>

// other includes
#include "njoy/dryad/covariance/base/CovarianceData.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceMatrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief Angular distribution covariance data
   */
  class AngularDistributionCovarianceData :
      protected base::CovarianceData< AngularDistributionCovarianceMatrix, AngularDistributionCovarianceData > {

    /* friend declarations */

    friend class base::CovarianceData< AngularDistributionCovarianceMatrix, AngularDistributionCovarianceData >;

    /* type aliases */

    using Parent = base::CovarianceData< AngularDistributionCovarianceMatrix, AngularDistributionCovarianceData >;

    /* fields */

    /* auxiliary functions */

    static void sort( std::vector< AngularDistributionCovarianceMatrix >& submatrices ) {

      std::sort( submatrices.begin(), submatrices.end(),
                 [] ( auto&& left, auto&& right )
                    { return std::tie( left.rowMetadata().reactionIdentifiers().front(),
                                       left.columnMetadata().reactionIdentifiers().front(),
                                       left.rowMetadata().moments(),
                                       left.columnMetadata().moments(),
                                       left.rowMetadata().energies(),
                                       left.columnMetadata().energies() ) <
                             std::tie( right.rowMetadata().reactionIdentifiers().front(),
                                       right.columnMetadata().reactionIdentifiers().front(),
                                       right.rowMetadata().moments(),
                                       right.columnMetadata().moments(),
                                       right.rowMetadata().energies(),
                                       right.columnMetadata().energies() ); } );
    }

  public:

    /* constructor */

    #include "njoy/dryad/covariance/AngularDistributionCovarianceData/src/ctor.hpp"

    /* methods */

    using Parent::numberReactions;
    using Parent::numberCovarianceMatrices;
    using Parent::reactionIdentifiers;
    using Parent::covariances;
    using Parent::hasCovarianceMatrix;
    using Parent::covarianceMatrix;

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const AngularDistributionCovarianceData& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const AngularDistributionCovarianceData& right ) const {

      return Parent::operator!=( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif


