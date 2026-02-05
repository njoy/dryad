#ifndef NJOY_DRYAD_CROSSSECTIONCOVARIANCEDATA
#define NJOY_DRYAD_CROSSSECTIONCOVARIANCEDATA

// system includes
#include <algorithm>
#include <map>
#include <variant>
#include <vector>

// other includes
#include "tools/overload.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The cross section covariance data
   */
  class CrossSectionCovarianceData {

  public:

    using Covariance = std::variant< covariance::CrossSectionCovarianceMatrix,
                                      std::vector< covariance::CrossSectionCovarianceMatrix > >;

  private:

    /* fields */

    std::vector< Covariance > covariances_;
    std::vector< id::ReactionID > reactions_;

    /* auxiliary functions */

    #include "njoy/dryad/CrossSectionCovarianceData/src/generateCovariances.hpp"
    #include "njoy/dryad/CrossSectionCovarianceData/src/iterator.hpp"
    #include "njoy/dryad/CrossSectionCovarianceData/src/compare.hpp"

  public:

    /* constructor */

    #include "njoy/dryad/CrossSectionCovarianceData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of reactions for which covariance data is available
     */
    std::size_t numberReactions() const {

      return this->reactionIdentifiers().size();
    }

    /**
     *  @brief Return the number of covariance blocks
     */
    std::size_t numberCovarianceMatrices() const {

      return this->covariances().size();
    }

    /**
     *  @brief Return the reaction identifiers for which covariance data is available
     */
    const std::vector< id::ReactionID > reactionIdentifiers() const {

      return this->reactions_;
    }

    /**
     *  @brief Return the covariance data
     */
    const std::vector< Covariance >& covariances() const {

      return this->covariances_;
    }

    /**
     *  @brief Return whether or not a given reaction pair has covariance data
     *
     *  @param[in] row      the row reaction identifier
     *  @param[in] column   the column reaction identifier
     */
    bool hasCovarianceMatrix( const id::ReactionID& row,
                              const id::ReactionID& column ) const {

      auto iter = this->iterator( row, column );
      return iter != this->covariances().end() && compare( row, column, *iter );
    }

    /**
     *  @brief Return whether or not a given reaction has covariance data
     *
     *  @param[in] id   the reaction identifier
     */
    bool hasCovarianceMatrix( const id::ReactionID& id ) const {

      return this->hasCovarianceMatrix( id, id );
    }

    /**
     *  @brief Return the covariance data for a row and column reaction pair
     *
     *  @param[in] row      the row reaction identifier
     *  @param[in] column   the column reaction identifier
     */
    const Covariance& covarianceMatrix( const id::ReactionID& row,
                                        const id::ReactionID& column ) const {

      auto iter = this->iterator( row, column );
      if ( iter != this->covariances().end() && compare( row, column, *iter ) ) {

        return *iter;
      }
      else {

        Log::error( "The requested reaction pair \'{}\', \'{}\' does not have covariance data",
                    row.symbol(), column.symbol() );
        throw std::exception();
      }
    }

    /**
     *  @brief Return covariance data for a for a reaction
     *
     *  @param[in] id   the reaction identifier
     */
    const Covariance& covarianceMatrix( const id::ReactionID& id ) const {

      auto iter = this->iterator( id, id );
      if ( iter != this->covariances().end() && compare( id, id, *iter ) ) {

        return *iter;
      }
      else {

        Log::error( "The requested reaction \'{}\' does not have covariance data", id.symbol() );
        throw std::exception();
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CrossSectionCovarianceData& right ) const {

      return this->covariances() == right.covariances();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CrossSectionCovarianceData& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
