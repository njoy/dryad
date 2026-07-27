#ifndef NJOY_DRYAD_THERMAL_INCOHERENTELASTICANGULARDISTRIBUTION
#define NJOY_DRYAD_THERMAL_INCOHERENTELASTICANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "njoy/dryad/thermal/IncoherentElasticAngularPdf.hpp"
#include "njoy/dryad/thermal/IncoherentElasticAngularCdf.hpp"
#include "njoy/dryad/TabulatedAngularDistribution.hpp"
#include "njoy/dryad/TabulatedAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Incoherent elastic thermal scattering angular distribution
   *         defined by an analytical pdf and cdf
   */
  class IncoherentElasticAngularDistribution {

    /* fields */
    IncoherentElasticAngularPdf pdf_;
    IncoherentElasticAngularCdf cdf_;

    /* auxiliary functions */

  public:

    /* type aliases */

    using XType = IncoherentElasticAngularPdf::XType;
    using YType = IncoherentElasticAngularPdf::XType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    IncoherentElasticAngularDistribution() = default;

    IncoherentElasticAngularDistribution( const IncoherentElasticAngularDistribution& ) = default;
    IncoherentElasticAngularDistribution( IncoherentElasticAngularDistribution&& ) = default;

    IncoherentElasticAngularDistribution& operator=( const IncoherentElasticAngularDistribution& ) = default;
    IncoherentElasticAngularDistribution& operator=( IncoherentElasticAngularDistribution&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] incident              the incident energy
     *  @param[in] debyeWallerIntegral   the Debye-Waller integral value
     */
    IncoherentElasticAngularDistribution( double incident,
                                          double debyeWallerIntegral ) :
        pdf_( incident, debyeWallerIntegral ), cdf_( incident, debyeWallerIntegral ) {}

    /* methods */

    /**
     *  @brief Return the incident energy value
     */
    double incidentEnergy() const {

      return this->pdf().incidentEnergy();
    }

    /**
     *  @brief Return the Debye-Waller integral value
     */
    double debyeWallerIntegral() const {

      return this->pdf().debyeWallerIntegral();
    }

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    const IncoherentElasticAngularPdf& pdf() const {

      return this->pdf_;
    }

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    IncoherentElasticAngularPdf& pdf() {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const IncoherentElasticAngularCdf& cdf() const {

      return this->cdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    IncoherentElasticAngularCdf& cdf() {

      return this->cdf_;
    }

    /**
     *  @brief Evaluate the pdf of the distribution for a cosine value
     *
     *  @param[in] cosine   the value to be evaluated
     */
    double operator()( double cosine ) const {

      return this->pdf()( cosine );
    }

    /**
     *  @brief Normalise the distribution
     */
    void normalise() {

      // nothing to do here, the pdf is already normalised
    }

    /**
     *  @brief Return the average cosine defined by the distribution
     */
    double averageCosine() const {

      return this->pdf().mean();
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
    bool operator==( const IncoherentElasticAngularDistribution& right ) const {

      return std::tie( this->pdf(), this->cdf() ) ==
             std::tie( right.pdf(), right.cdf() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const IncoherentElasticAngularDistribution& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
