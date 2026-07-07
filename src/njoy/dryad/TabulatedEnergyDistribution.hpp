#ifndef NJOY_DRYAD_TABULATEDENERGYDISTRIBUTION
#define NJOY_DRYAD_TABULATEDENERGYDISTRIBUTION

// system includes
#include <vector>
#include <optional>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/dryad/TabulatedEnergyDistributionFunction.hpp"

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
    TabulatedEnergyDistributionFunction cdf_;

    /* auxiliary functions */

  public:

    /* type aliases */

    using XType = TabulatedEnergyDistributionFunction::XType;
    using YType = TabulatedEnergyDistributionFunction::XType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedEnergyDistribution() = default;

    TabulatedEnergyDistribution( const TabulatedEnergyDistribution& ) = default;
    TabulatedEnergyDistribution( TabulatedEnergyDistribution&& ) = default;

    TabulatedEnergyDistribution& operator=( const TabulatedEnergyDistribution& ) = default;
    TabulatedEnergyDistribution& operator=( TabulatedEnergyDistribution&& ) = default;

    /**
     *  @brief Constructor using a pdf
     *
     *  @param[in] pdf         the pdf of the distribution
     *  @param[in] normalise   option to indicate whether or not to normalise
     *                         all probability data (default: no normalisation)
     */
    TabulatedEnergyDistribution( TabulatedEnergyDistributionFunction pdf,
                                 bool normalise = false ) :
      pdf_( std::move( pdf ) ), cdf_() {

      if ( normalise ) {

        this->normalise();
      }
      else {

        this->cdf() = this->pdf().calculateCdf();
      }
    }

    /**
     *  @brief Constructor
     *
     *  @param[in] energies       the energy values
     *  @param[in] values         the probability values
     *  @param[in] boundaries     the boundaries of the interpolation regions
     *  @param[in] interpolants   the interpolation types of the interpolation regions
     *  @param[in] normalise      option to indicate whether or not to normalise
     *                            all probability data (default: no normalisation)
     */
    TabulatedEnergyDistribution(
        std::vector< double > energies,
        std::vector< double > values,
        std::vector< std::size_t > boundaries,
        std::vector< InterpolationType > interpolants,
        bool normalise = false ) :
      TabulatedEnergyDistribution(
          TabulatedEnergyDistributionFunction( std::move( energies ), std::move( values ),
                                               std::move( boundaries ), std::move( interpolants ) ),
          normalise ) {}

    /**
     *  @brief Constructor for an energy distirbution using a single interpolation zone
     *
     *  @param[in] energies       the energy values
     *  @param[in] values         the probability values
     *  @param[in] interpolant    the interpolation type of the data (default lin-lin)
     *  @param[in] normalise      option to indicate whether or not to normalise
     *                            all probability data (default: no normalisation)
     */
    TabulatedEnergyDistribution(
        std::vector< double > energies,
        std::vector< double > values,
        InterpolationType interpolant = InterpolationType::LinearLinear,
        bool normalise = false ) :
      TabulatedEnergyDistribution(
          TabulatedEnergyDistributionFunction( std::move( energies ), std::move( values ),
                                               std::move( interpolant ) ),
          normalise ) {}

    /**
     *  @brief Constructor using a pdf and cdf
     *
     *  @param[in] pdf         the pdf of the distribution
     *  @param[in] cdf         the cdf of the distribution
     */
    TabulatedEnergyDistribution( TabulatedEnergyDistributionFunction pdf,
                                 TabulatedEnergyDistributionFunction cdf ) :
      pdf_( std::move( pdf ) ), cdf_( std::move( cdf ) ) {}

    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const {

      return this->pdf().energies();
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
    const TabulatedEnergyDistributionFunction& pdf() const {

      return this->pdf_;
    }

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    TabulatedEnergyDistributionFunction& pdf() {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const TabulatedEnergyDistributionFunction& cdf() const {

      return this->cdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    TabulatedEnergyDistributionFunction& cdf() {

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

      this->pdf_.normalise();
      this->cdf() = this->pdf().calculateCdf( true );
    }

    /**
     *  @brief Return the average energy defined by the distribution
     */
    double averageEnergy() const { return this->pdf().mean(); }

    /**
     *  @brief Return a linearised energy distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     *  @param[in] normalise   option to indicate whether or not to normalise
     *                         all probability data (default: no normalisation)
     */
    TabulatedEnergyDistribution linearise( double tolerance = constants::linearisation::tolerance,
                                           bool normalise = false ) const {

      TabulatedEnergyDistributionFunction pdf = this->pdf().linearise( tolerance );
      return TabulatedEnergyDistribution( std::move( pdf ), normalise );
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
