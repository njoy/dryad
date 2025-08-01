#ifndef NJOY_DRYAD_LEGENDREANGULARDISTRIBUTIONS
#define NJOY_DRYAD_LEGENDREANGULARDISTRIBUTIONS

// system includes

// other includes
#include "dryad/base/GridDistributions.hpp"
#include "dryad/LegendreAngularDistribution.hpp"
#include "dryad/TabulatedAverageCosine.hpp"
#include "dryad/TabulatedAngularDistributions.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Angular distribution data given using Legendre expansions
   */
  class LegendreAngularDistributions :
      protected base::GridDistributions< LegendreAngularDistribution > {

    /* type aliases */
    using Parent = base::GridDistributions< LegendreAngularDistribution >;

  public:

    /* constructor */

    #include "dryad/LegendreAngularDistributions/src/ctor.hpp"

    /* methods */

    using Parent::grid;
    using Parent::distributions;
    using Parent::boundaries;
    using Parent::interpolants;
    using Parent::numberPoints;
    using Parent::numberRegions;
    using Parent::operator();

    /**
     *  @brief Normalise the distributions
     */
    void normalise() {

      for ( auto& distribution : this->distributions() ) {

        distribution.normalise();
      }
    }

    /**
     *  @brief Return the average cosine values
     */
    TabulatedAverageCosine averageCosines() const {

      std::vector< double > cosines;
      cosines.reserve( this->numberPoints() );
      std::transform( this->distributions().begin(), this->distributions().end(),
                      std::back_inserter( cosines ),
                      [] ( auto&& distribution ) { return distribution.averageCosine(); } );
      return TabulatedAverageCosine( this->grid(), std::move( cosines ),
                                     this->boundaries(),
                                     this->interpolants() );
    }

    /**
     *  @brief Return linearised angular distributions
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedAngularDistributions linearise( ToleranceConvergence tolerance = {} ) const {

      //! @todo should we normalise the resulting distribution?

      std::vector< TabulatedAngularDistribution > distributions;
      distributions.reserve( this->numberPoints() );
      std::transform( this->distributions().begin(), this->distributions().end(),
                      std::back_inserter( distributions ),
                      [&tolerance] ( auto&& distribution )
                                   { return distribution.linearise( tolerance ); } );
      return TabulatedAngularDistributions( this->grid(), std::move( distributions ),
                                            this->boundaries(), this->interpolants() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const LegendreAngularDistributions& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const LegendreAngularDistributions& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
