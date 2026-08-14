#ifndef NJOY_DRYAD_COVARIANCE_BASE_COVARIANCEDATA
#define NJOY_DRYAD_COVARIANCE_BASE_COVARIANCEDATA

// system includes
#include <algorithm>
#include <map>
#include <variant>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"

namespace njoy {
namespace dryad {
namespace covariance {
namespace base {

  /**
   *  @class
   *  @brief A covariance data base class
   *
   *  This base class stores covariance matrices for the principal reaction dimension, and
   *  assumes that every matrix uses only a single reaction value.
   */
  template < typename CovarianceMatrix, typename Derived >
  class CovarianceData {

  public:

    using Covariance = std::variant< CovarianceMatrix, std::vector< CovarianceMatrix > >;

  private:

    /* fields */

    std::vector< Covariance > covariances_;
    std::vector< id::ReactionID > reactions_;

    /* auxiliary functions */

    static std::pair< std::vector< id::ReactionID >, std::vector< Covariance > >
    generateCovariances( std::vector< CovarianceMatrix > submatrices ) {

      // we are assuming the following:
      //   - all submatrices are for a single ProjectileTarget
      //   - each submatrix is for a single row and column reaction
      //   - all submatrices are on diagonal or above the diagonal

      std::vector< id::ReactionID > reactions;
      std::vector< Covariance > covariances;

      Derived::sort( submatrices );

      auto add_reaction = [] ( std::vector< id::ReactionID >& reactions, const id::ReactionID& id ) {

        auto iter = std::lower_bound( reactions.begin(), reactions.end(), id );
        if ( iter == reactions.end() || id != *iter ) {

          reactions.insert( iter, id );
        }
      };

      auto iter = submatrices.begin();
      while ( iter != submatrices.end() ) {

        auto row = iter->rowMetadata().reactionIdentifiers().front();
        auto column = iter->columnMetadata().reactionIdentifiers().front();

        add_reaction( reactions, row );
        add_reaction( reactions, column );

        auto next = std::upper_bound( iter, submatrices.end(),
                                      std::tie( row, column ),
                                      [] ( auto&& left, auto&& right )
                                         { return left < std::tie( right.rowMetadata().reactionIdentifiers().front(),
                                                                   right.columnMetadata().reactionIdentifiers().front() ); } );

        auto size = std::distance( iter, next );
        if ( size > 1 ) {

          std::vector< CovarianceMatrix > entries;
          entries.reserve( size );
          std::move( iter, next, std::back_inserter( entries ) );

          covariances.emplace_back( std::move( entries ) );
        }
        else {

          covariances.emplace_back( std::move( *iter ) );
        }

        iter = next;
      }

      return std::make_pair( std::move( reactions ), std::move( covariances ) );
    }

    auto iterator( const id::ReactionID& row, const id::ReactionID& column ) const {

      auto compare = [] ( auto&& left, auto&& right ) {

        auto get_tie = tools::overload{

          [] ( const CovarianceMatrix& entry ) {

            return std::tie( entry.rowMetadata().reactionIdentifiers().front(),
                             entry.columnMetadata().reactionIdentifiers().front() );
          },
          [] ( const std::vector< CovarianceMatrix >& entry ) {

            return std::tie( entry.front().rowMetadata().reactionIdentifiers().front(),
                             entry.front().columnMetadata().reactionIdentifiers().front() );
          }
        };

        return std::visit( get_tie, left ) < right;
      };

      auto iter = std::lower_bound( this->covariances().begin(), this->covariances().end(),
                                    std::tie( row, column ),
                                    compare );
      return iter;
    }

    static bool
    compare( const id::ReactionID& row, const id::ReactionID& column,
             const Covariance& covariance ) {

      auto get_tie = tools::overload{

        [] ( const CovarianceMatrix& entry ) {

          return std::tie( entry.rowMetadata().reactionIdentifiers().front(),
                           entry.columnMetadata().reactionIdentifiers().front() );
        },
        [] ( const std::vector< CovarianceMatrix >& entry ) {

          return std::tie( entry.front().rowMetadata().reactionIdentifiers().front(),
                           entry.front().columnMetadata().reactionIdentifiers().front() );
        }
      };

      return std::tie( row, column ) == std::visit( get_tie, covariance );
    }

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param matrices   the covariance matrices
     */
    CovarianceData( std::pair< std::vector< id::ReactionID >, std::vector< Covariance > > data ) :
      covariances_( std::move( data.second ) ),
      reactions_( std::move( data.first ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    CovarianceData() = default;

    CovarianceData( const CovarianceData& ) = default;
    CovarianceData( CovarianceData&& ) = default;

    CovarianceData& operator=( const CovarianceData& ) = default;
    CovarianceData& operator=( CovarianceData&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param matrices   the covariance matrices
     */
    CovarianceData( std::vector< CovarianceMatrix > matrices ) :
      CovarianceData( generateCovariances( matrices ) ) {}

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
     *  @brief Return covariance data for a reaction
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
    bool operator==( const CovarianceData& right ) const {

      return this->covariances() == right.covariances();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CovarianceData& right ) const {

      return ! this->operator==( right );
    }
  };

} // base namespace
} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
