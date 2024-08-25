#ifndef NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION
#define NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>
#include <optional>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/LegendreAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An angular distribution defined by a pdf and cdf using Legendre
   *         expansions
   *
   *  The pdf is normalised to 1 upon construction and the associated cdf is
   *  calculated upon construction.
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
    const LegendreAngularDistributionFunction& pdf() const noexcept {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const LegendreAngularDistributionFunction& cdf() const noexcept {

      return this->cdf_;
    }

    /**
     *  @brief Return whether or not the cumulative distribution function (cdf) is defined
     */
    static constexpr bool hasCdf() { return true; }

    /**
     *  @brief Evaluate the pdf of the distribution for a cosine value
     *
     *  @param cosine   the value to be evaluated
     */
    double operator()( double cosine ) const noexcept {

      return this->pdf()( cosine );
    }

    /**
     *  @brief Return the average cosine defined by the distribution
     */
    double averageCosine() const noexcept {

      return this->pdf().order() == 0
             ? 0.
             : this->pdf().coefficients()[1];
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
