#ifndef NJOY_DRYAD_COVARIANCE_CROSSSECTIONCOVARIANCEDATA
#define NJOY_DRYAD_COVARIANCE_CROSSSECTIONCOVARIANCEDATA

// system includes
#include <algorithm>
#include <map>
#include <variant>
#include <vector>

// other includes
#include "njoy/dryad/covariance/base/CovarianceData.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief Cross section covariance data
   */
  class CrossSectionCovarianceData :
      protected base::CovarianceData< CrossSectionCovarianceMatrix, CrossSectionCovarianceData > {

    /* friend declarations */

    friend class base::CovarianceData< CrossSectionCovarianceMatrix, CrossSectionCovarianceData >;

    /* type aliases */

    using Parent = base::CovarianceData< CrossSectionCovarianceMatrix, CrossSectionCovarianceData >;

    /* fields */

    /* auxiliary functions */

    static void sort( std::vector< CrossSectionCovarianceMatrix >& submatrices ) {

      std::sort( submatrices.begin(), submatrices.end(),
                 [] ( auto&& left, auto&& right )
                    { return std::tie( left.rowMetadata().reactionIdentifiers().front(),
                                       left.columnMetadata().reactionIdentifiers().front(),
                                       left.rowMetadata().energies(),
                                       left.columnMetadata().energies() ) <
                             std::tie( right.rowMetadata().reactionIdentifiers().front(),
                                       right.columnMetadata().reactionIdentifiers().front(),
                                       right.rowMetadata().energies(),
                                       right.columnMetadata().energies() ); } );
    }

  public:

    /* constructor */

    #include "njoy/dryad/covariance/CrossSectionCovarianceData/src/ctor.hpp"

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
    bool operator==( const CrossSectionCovarianceData& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CrossSectionCovarianceData& right ) const {

      return Parent::operator!=( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif


