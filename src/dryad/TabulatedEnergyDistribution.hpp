#ifndef NJOY_DRYAD_TABULATEDENERGYDISTRIBUTION
#define NJOY_DRYAD_TABULATEDENERGYDISTRIBUTION

// system includes
#include <vector>
#include <optional>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/TabulatedEnergyDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An energy distribution defined by a pdf and cdf using tabulated
   *         data
   *
   *  The pdf is assumed to be normalised to 1 upon construction and the
   *  associated cdf is not calculated upon construction.
   */
  class TabulatedEnergyDistribution {

    /* fields */
    TabulatedEnergyDistributionFunction pdf_;
    std::optional< TabulatedEnergyDistributionFunction > cdf_;

  public:

    /* type aliases */

    using XType = TabulatedEnergyDistributionFunction::XType;
    using YType = TabulatedEnergyDistributionFunction::XType;

    /* constructor */

    #include "dryad/TabulatedEnergyDistribution/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    const TabulatedEnergyDistributionFunction& pdf() const {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const std::optional< TabulatedEnergyDistributionFunction >& cdf() const {

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
     *  @brief Return the average energy defined by the distribution
     */
    double averageEnergy() const { return this->pdf().mean(); }

    /**
     *  @brief Return a linearised energy distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedEnergyDistribution linearise( ToleranceConvergence tolerance = {} ) const {

      // no need to normalise the resulting pdf, the TabulatedEnergyDistribution ctor
      // will take care of normalisation

      TabulatedEnergyDistributionFunction pdf = this->pdf().linearise( tolerance );
      return TabulatedEnergyDistribution( std::move( pdf ) );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedEnergyDistribution& right ) const {

      return this->pdf() == right.pdf() && this->cdf() == right.cdf();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedEnergyDistribution& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
