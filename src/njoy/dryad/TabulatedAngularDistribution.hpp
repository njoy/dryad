#ifndef NJOY_DRYAD_TABULATEDANGULARDISTRIBUTION
#define NJOY_DRYAD_TABULATEDANGULARDISTRIBUTION

// system includes
#include <vector>
#include <optional>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/dryad/TabulatedAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An angular distribution defined by a pdf and cdf using tabulated data
   */
  class TabulatedAngularDistribution {

    /* fields */
    TabulatedAngularDistributionFunction pdf_;
    TabulatedAngularDistributionFunction cdf_;

    /* auxiliary functions */

    #include "njoy/dryad/TabulatedAngularDistribution/src/calculateCdf.hpp"

  public:

    /* type aliases */

    using XType = TabulatedAngularDistributionFunction::XType;
    using YType = TabulatedAngularDistributionFunction::XType;

    /* constructor */

    #include "njoy/dryad/TabulatedAngularDistribution/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the cosine values
     */
    const std::vector< double >& cosines() const {

      return this->pdf().cosines();
    }

    /**
     *  @brief Return the probability values
     */
    const std::vector< double >& values() const {

      return this->pdf().values();
    }

    /**
     *  @brief Return the boundaries of the interpolation regions
     */
    const std::vector< std::size_t >& boundaries() const {

      return this->pdf().boundaries();
    }

    /**
     *  @brief Return the interpolation types of the interpolation regions
     */
    const std::vector< InterpolationType >& interpolants() const {

      return this->pdf().interpolants();
    }

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    const TabulatedAngularDistributionFunction& pdf() const {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const TabulatedAngularDistributionFunction& cdf() const {

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
      this->calculateCdf( true );
    }

    /**
     *  @brief Return the average cosine defined by the distribution
     */
    double averageCosine() const { return this->pdf().mean(); }

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
    bool operator==( const TabulatedAngularDistribution& right ) const {

      return this->pdf() == right.pdf() && this->cdf() == right.cdf();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedAngularDistribution& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
