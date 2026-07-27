#ifndef NJOY_DRYAD_TABULATEDANGULARDISTRIBUTIONS
#define NJOY_DRYAD_TABULATEDANGULARDISTRIBUTIONS

// system includes

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/base/GridDistributions.hpp"
#include "njoy/dryad/TabulatedAngularDistribution.hpp"
#include "njoy/dryad/TabulatedAverageCosine.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Angular distribution data given using tables
   */
  class TabulatedAngularDistributions :
      protected base::GridDistributions< TabulatedAngularDistribution > {

    /* type aliases */
    using Parent = base::GridDistributions< TabulatedAngularDistribution >;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedAngularDistributions() = default;

    TabulatedAngularDistributions( const TabulatedAngularDistributions& ) = default;
    TabulatedAngularDistributions( TabulatedAngularDistributions&& ) = default;

    TabulatedAngularDistributions& operator=( const TabulatedAngularDistributions& ) = default;
    TabulatedAngularDistributions& operator=( TabulatedAngularDistributions&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] grid            the grid values
     *  @param[in] distributions   the associated distributions
     *  @param[in] boundaries      the boundaries of the interpolation regions
     *  @param[in] interpolants    the interpolation types of the interpolation regions
     *  @param[in] normalise       option to indicate whether or not to normalise
     *                             all probability data (default: no normalisation)
     */
    TabulatedAngularDistributions( std::vector< double > grid,
                                   std::vector< TabulatedAngularDistribution > distributions,
                                   std::vector< std::size_t > boundaries,
                                   std::vector< InterpolationType > interpolants,
                                   bool normalise = false ) :
      Parent( std::move( grid ), std::move( distributions ),
              std::move( boundaries ), std::move( interpolants ) ) {

      if ( normalise ) {

        this->normalise();
      }
    }

    /**
     *  @brief Constructor for angular distributions using a single interpolation zone
     *
     *  @param[in] grid            the grid values
     *  @param[in] distributions   the associated distributions
     *  @param[in] interpolant     the interpolation type of the data (default lin-lin)
     *  @param[in] normalise       option to indicate whether or not to normalise
     *                             all probability data (default: no normalisation)
     */
    TabulatedAngularDistributions( std::vector< double > grid,
                                   std::vector< TabulatedAngularDistribution > distributions,
                                   InterpolationType interpolant = InterpolationType::LinearLinear,
                                   bool normalise = false ) :
      Parent( std::move( grid ), std::move( distributions ), interpolant ) {

      if ( normalise ) {

        this->normalise();
      }
    }

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
     *
     *  Note: all distributions should have the same integral over their domain
     *        to avoid changing the full distribution (ie the normalisation moves
     *        every distribution up or down by the same amount to avoid changing
     *        the full distribution shape).
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
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     *  @param[in] normalise   option to indicate whether or not to normalise
     *                         all probability data (default: no normalisation)
     */
    TabulatedAngularDistributions linearise( double tolerance = constants::linearisation::tolerance,
                                             bool normalise = false ) const {

      std::vector< TabulatedAngularDistribution > distributions;
      distributions.reserve( this->numberPoints() );
      std::transform( this->distributions().begin(), this->distributions().end(),
                      std::back_inserter( distributions ),
                      [tolerance, normalise]
                        ( auto&& distribution )
                        { return distribution.linearise( tolerance, normalise ); } );
      return TabulatedAngularDistributions( this->grid(), std::move( distributions ),
                                            this->boundaries(), this->interpolants() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedAngularDistributions& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedAngularDistributions& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
