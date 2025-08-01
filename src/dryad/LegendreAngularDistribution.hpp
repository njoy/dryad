#ifndef NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION
#define NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>
#include <optional>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/LegendreAngularDistributionFunction.hpp"
#include "dryad/TabulatedAngularDistribution.hpp"
#include "dryad/TabulatedAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An angular distribution defined by a pdf and cdf using a Legendre
   *         series expansion
   *
   *  The pdf is normalised to 1 upon construction and the associated cdf is
   *  calculated upon construction (after the pdf has been normalised).
   */
  class LegendreAngularDistribution {

    /* fields */
    LegendreAngularDistributionFunction pdf_;
    LegendreAngularDistributionFunction cdf_;

  public:

    /* type aliases */

    using XType = LegendreAngularDistributionFunction::XType;
    using YType = LegendreAngularDistributionFunction::XType;

    /* constructor */

    #include "dryad/LegendreAngularDistribution/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    const LegendreAngularDistributionFunction& pdf() const {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const LegendreAngularDistributionFunction& cdf() const {

      return this->cdf_;
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

      return this->pdf().order() == 0 ? 0. : this->pdf().mean();
    }

    /**
     *  @brief Return a linearised angular distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedAngularDistribution linearise( ToleranceConvergence tolerance = {} ) const {

      // no need to normalise the resulting pdf, the TabulatedAngularDistribution ctor
      // will take care of normalisation

      TabulatedAngularDistributionFunction pdf = this->pdf().linearise( std::move( tolerance ) );
      return TabulatedAngularDistribution( std::move( pdf ) );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const LegendreAngularDistribution& right ) const {

      return this->pdf() == right.pdf() && this->cdf() == right.cdf();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const LegendreAngularDistribution& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
