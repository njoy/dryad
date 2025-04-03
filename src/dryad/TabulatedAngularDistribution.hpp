#ifndef NJOY_DRYAD_TABULATEDANGULARDISTRIBUTION
#define NJOY_DRYAD_TABULATEDANGULARDISTRIBUTION

// system includes
#include <vector>
#include <optional>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/TabulatedAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An angular distribution defined by a pdf and cdf using tabulated
   *         data
   *
   *  The pdf is assumed to be normalised to 1 upon construction and the
   *  associated cdf is not calculated upon construction.
   */
  class TabulatedAngularDistribution {

    /* fields */
    TabulatedAngularDistributionFunction pdf_;
    std::optional< TabulatedAngularDistributionFunction > cdf_;

  public:

    /* type aliases */

    using XType = TabulatedAngularDistributionFunction::XType;
    using YType = TabulatedAngularDistributionFunction::XType;

    /* constructor */

    #include "dryad/TabulatedAngularDistribution/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    const TabulatedAngularDistributionFunction& pdf() const noexcept {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const TabulatedAngularDistributionFunction& cdf() const {

      if ( this->cdf_.has_value() ) {

        return this->cdf_.value();
      }
      else {

        Log::error( "The calculation of the cdf is not implemented yet" );
        throw std::bad_optional_access();
      }
    }

    /**
     *  @brief Return whether or not the cumulative distribution function (cdf) is defined
     */
    bool hasCdf() const {

      return this->cdf_.has_value();
    }

    /**
     *  @brief Evaluate the pdf of the distribution for a cosine value
     *
     *  @param cosine   the value to be evaluated
     */
    double operator()( double cosine ) const {

      return this->pdf()( cosine );
    }

    /**
     *  @brief Return the average cosine defined by the distribution
     */
    double averageCosine() const {

      Log::error( "The calculation of the average cosine is not implemented yet" );
      throw std::exception();
    }

//    /**
//     *  @brief Return a linearised angular distribution table
//     *
//     *  @param[in] tolerance   the linearisation tolerance
//     */
//    TabulatedAngularDistribution linearise( ToleranceConvergence tolerance = {} ) const {
//
//    }
  };

} // dryad namespace
} // njoy namespace

#endif
