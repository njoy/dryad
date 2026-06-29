#ifndef NJOY_DRYAD_MIXEDANGULARDISTRIBUTION
#define NJOY_DRYAD_MIXEDANGULARDISTRIBUTION

// system includes
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/IsotropicAngularDistributionFunction.hpp"
#include "njoy/dryad/LegendreAngularDistributionFunction.hpp"
#include "njoy/dryad/TabulatedAngularDistributionFunction.hpp"
#include "njoy/dryad/TabulatedAngularDistribution.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An angular distribution defined by a pdf that is an isotropic,
   *         legendre or tabulated distribution function
   */
  class MixedAngularDistribution {

  public:

    /* type aliases */

    using MixedDistributionFunction = std::variant< IsotropicAngularDistributionFunction,
                                                    LegendreAngularDistributionFunction,
                                                    TabulatedAngularDistributionFunction >;

  private:

    /* fields */

    MixedDistributionFunction pdf_;
    MixedDistributionFunction cdf_;

    /* auxiliary functions */

    /**
     *  @brief Calculate the cdf from the pdf
     */
    MixedDistributionFunction deriveCdf( bool set_cdf_to_one = false ) {

      auto calculate = tools::overload{

        [&] ( const TabulatedAngularDistributionFunction& function ) -> MixedDistributionFunction {

          return function.cdf( set_cdf_to_one );
        },
        [] ( auto&& function ) -> MixedDistributionFunction {

          return function.cdf();
        }
      };

      return std::visit( calculate, this->pdf() );
    }

  public:

    /* type aliases */

    using XType = double;
    using YType = double;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    MixedAngularDistribution() = default;

    MixedAngularDistribution( const MixedAngularDistribution& ) = default;
    MixedAngularDistribution( MixedAngularDistribution&& ) = default;

    MixedAngularDistribution& operator=( const MixedAngularDistribution& ) = default;
    MixedAngularDistribution& operator=( MixedAngularDistribution&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param function   the distribution function
     */
    MixedAngularDistribution( MixedDistributionFunction function,
                              bool normalise = false ) :
        pdf_( std::move( function ) ),
        cdf_() {

      if ( normalise ) {

        this->normalise();
      }
      else {

        this->cdf_ = this->deriveCdf();
      }
    }

    /* methods */

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    const MixedDistributionFunction& pdf() const {

      return this->pdf_;
    }

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    MixedDistributionFunction& pdf() {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const MixedDistributionFunction& cdf() const {

      return this->cdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    MixedDistributionFunction& cdf() {

      return this->cdf_;
    }

    /**
     *  @brief Evaluate the pdf of the distribution for a cosine value
     *
     *  @param cosine   the value to be evaluated
     */
    double operator()( double cosine ) const {

      return std::visit( [&] ( auto&& function ) { return function( cosine ); }, this->pdf() );
    }

    /**
     *  @brief Normalise the distribution
     */
    void normalise() {

      std::visit( [] ( auto&& function ) { return function.normalise(); }, this->pdf() );
      this->cdf_ = this->deriveCdf( true );
    }

    /**
     *  @brief Return the average cosine defined by the distribution
     */
    double averageCosine() const {

      return std::visit( [&] ( auto&& function ) { return function.mean(); },
                         this->pdf() );
    }

    /**
     *  @brief Return a linearised angular distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     *  @param[in] normalise   option to indicate whether or not to normalise
     *                         all probability data (default: no normalisation)
     */
    TabulatedAngularDistribution linearise( double tolerance = constants::linearisation::tolerance,
                                            bool normalise = false ) const {

      auto linearise = [&] ( auto&& function ) { return function.linearise( tolerance ); };
      TabulatedAngularDistributionFunction pdf = std::visit( linearise, this->pdf() );
      return TabulatedAngularDistribution( std::move( pdf ), normalise );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const MixedAngularDistribution& right ) const {

      return this->pdf() == right.pdf() && this->cdf() == right.cdf();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const MixedAngularDistribution& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
