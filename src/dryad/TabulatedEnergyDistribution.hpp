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
   */
  class TabulatedEnergyDistribution {

    /* fields */
    TabulatedEnergyDistributionFunction pdf_;
    mutable std::optional< TabulatedEnergyDistributionFunction > cdf_;

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
    const TabulatedEnergyDistributionFunction& pdf() const noexcept {

      return this->pdf_;
    }

    /**
     *  @brief Return whether or not the  cumulative distribution function (cdf) is defined
     */
    bool hasCdf() const {

      return this->cdf_.has_value();
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const TabulatedEnergyDistributionFunction& cdf() const {

      if ( this->cdf_.has_value() ) {

        return this->cdf_.value();
      }
      else {

        Log::error( "The calculation of the cdf is not implemented yet" );
        throw std::bad_optional_access();
      }
    }

    /**
     *  @brief Evaluate the pdf of the distribution for a cosine value
     *
     *  @param cosine   the value to be evaluated
     */
    double operator()( double cosine ) const {

      return this->pdf()( cosine );
    }

//    /**
//     *  @brief Return a linearised angular distribution table
//     *
//     *  @param[in] tolerance   the linearisation tolerance
//     */
//    TabulatedEnergyDistribution linearise( ToleranceConvergence tolerance = {} ) const {
//
//    }
  };

} // dryad namespace
} // njoy namespace

#endif
