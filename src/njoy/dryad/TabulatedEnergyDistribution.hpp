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
    TabulatedEnergyDistribution(
        TabulatedEnergyDistributionFunction pdf,
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
     *  @param[in] curate         flag to indicate whether or not to curate the data (default: false)
     */
    TabulatedEnergyDistribution(
        std::vector< double > energies,
        std::vector< double > values,
        std::vector< std::size_t > boundaries,
        std::vector< InterpolationType > interpolants,
        bool normalise = false,
        bool curate = false ) :
      TabulatedEnergyDistribution(
          TabulatedEnergyDistributionFunction(
              std::move( energies ),
              std::move( values ),
              std::move( boundaries ),
              std::move( interpolants ),
              curate ),
          normalise ) {}

    /**
     *  @brief Constructor for an energy distribution using a single interpolation zone
     *
     *  @param[in] energies       the energy values
     *  @param[in] values         the probability values
     *  @param[in] interpolant    the interpolation type of the data (default lin-lin)
     *  @param[in] normalise      option to indicate whether or not to normalise
     *                            all probability data (default: no normalisation)
     *  @param[in] curate         flag to indicate whether or not to curate the data (default: false)
     */
    TabulatedEnergyDistribution(
        std::vector< double > energies,
        std::vector< double > values,
        InterpolationType interpolant = InterpolationType::LinearLinear,
        bool normalise = false,
        bool curate = false ) :
      TabulatedEnergyDistribution(
          TabulatedEnergyDistributionFunction(
              std::move( energies ),
              std::move( values ),
              std::move( interpolant ),
              curate ),
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
     *  @brief Evaluate the pdf of the distribution for an energy value
     *
     *  @param[in] energy   the value to be evaluated
     */
    double operator()( double energy ) const {

      return this->pdf()( energy );
    }

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return this->pdf().lowerLimit();
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return this->pdf().upperLimit();
    }

    /**
     *  @brief Return the x values of the table
     */
    const std::vector< double >& x() const {

      return this->pdf().x();
    }

    /**
     *  @brief Return the y values of the table
     */
    const std::vector< double >& y() const {

      return this->pdf().y();
    }

    /**
     *  @brief Return the lower limit of the domain
     */
    double lowerLimit() const {

      return this->pdf().lowerLimit();
    }

    /**
     *  @brief Return the upper limit of the domain
     */
    double upperLimit() const {

      return this->pdf().upperLimit();
    }

    /**
     *  @brief Normalise the distribution
     */
    void normalise() {

      this->pdf_.normalise();
      this->cdf() = this->pdf().calculateCdf( true );
    }

    /**
     *  @brief Return whether or not the distribution is curated
     */
    bool isCurated() const {

      return this->pdf().isCurated() && this->cdf().isCurated();
    }

    /**
     *  @brief Curate the distribution
     */
    void curate() {

      this->pdf().curate();
      this->cdf().curate();
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
