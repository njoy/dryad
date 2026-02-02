#ifndef NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION
#define NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>
#include <optional>

// other includes
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/dryad/LegendreAngularDistributionFunction.hpp"
#include "njoy/dryad/TabulatedAngularDistribution.hpp"
#include "njoy/dryad/TabulatedAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An angular distribution defined by a pdf and cdf using a Legendre
   *         series expansion
   */
  class LegendreAngularDistribution {

    /* fields */
    LegendreAngularDistributionFunction pdf_;
    LegendreAngularDistributionFunction cdf_;

    /* auxiliary functions */

    #include "njoy/dryad/LegendreAngularDistribution/src/calculateCdf.hpp"

  public:

    /* type aliases */

    using XType = LegendreAngularDistributionFunction::XType;
    using YType = LegendreAngularDistributionFunction::XType;

    /* constructor */

    #include "njoy/dryad/LegendreAngularDistribution/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the coefficients of the distribution
     */
    const std::vector< double > coefficients() const {

      return this->pdf().coefficients();
    }

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
     *  @brief Normalise the distribution
     */
    void normalise() {

      this->pdf_.normalise();
      this->calculateCdf();
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
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     *  @param[in] normalise   option to indicate whether or not to normalise
     *                         all probability data (default: no normalisation)
     */
    TabulatedAngularDistribution linearise( double tolerance = constants::linearisation::tolerance,
                                            bool normalise = false ) const {

      TabulatedAngularDistributionFunction pdf = this->pdf().linearise( tolerance );
      return TabulatedAngularDistribution( std::move( pdf ), normalise );
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
