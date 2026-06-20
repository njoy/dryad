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

    /**
     *  @brief Calculate the cdf from the pdf
     */
    void calculateCdf( bool set_cdf_to_one = false ) {

      std::vector< double > cdf = this->pdf().cumulativeIntegral();
      if ( set_cdf_to_one ) {

        cdf.back() = 1.;
      }
      this->cdf_ = TabulatedAngularDistributionFunction( this->pdf().cosines(),
                                                         std::move( cdf ),
                                                         this->pdf().boundaries(),
                                                         this->pdf().interpolants() );
    }

  public:

    /* type aliases */

    using XType = TabulatedAngularDistributionFunction::XType;
    using YType = TabulatedAngularDistributionFunction::XType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedAngularDistribution() = default;

    TabulatedAngularDistribution( const TabulatedAngularDistribution& ) = default;
    TabulatedAngularDistribution( TabulatedAngularDistribution&& ) = default;

    TabulatedAngularDistribution& operator=( const TabulatedAngularDistribution& ) = default;
    TabulatedAngularDistribution& operator=( TabulatedAngularDistribution&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param cosines        the cosine values
     *  @param values         the probability values
     *  @param boundaries     the boundaries of the interpolation regions
     *  @param interpolants   the interpolation types of the interpolation regions
     *  @param normalise      option to indicate whether or not to normalise
     *                        all probability data (default: no normalisation)
     */
    TabulatedAngularDistribution(
        std::vector< double > cosines,
        std::vector< double > values,
        std::vector< std::size_t > boundaries,
        std::vector< InterpolationType > interpolants,
        bool normalise = false ) :
      pdf_( std::move( cosines ), std::move( values ),
            std::move( boundaries ), std::move( interpolants ) ),
      cdf_() {

      if ( normalise ) {

        this->normalise();
      }
      else {

        this->calculateCdf();
      }
    }

    /**
     *  @brief Constructor for a pdf using a single interpolation zone
     *
     *  @param cosines        the cosine values
     *  @param values         the probability values
     *  @param interpolant    the interpolation type of the data (default lin-lin)
     *  @param normalise      option to indicate whether or not to normalise
     *                        all probability data (default: no normalisation)
     */
    TabulatedAngularDistribution(
        std::vector< double > cosines,
        std::vector< double > values,
        InterpolationType interpolant = InterpolationType::LinearLinear,
        bool normalise = false ) :
      pdf_( std::move( cosines ), std::move( values ), std::move( interpolant ) ),
      cdf_() {

      if ( normalise ) {

        this->normalise();
      }
      else {

        this->calculateCdf();
      }
    }

    /**
     *  @brief Constructor using a pdf
     *
     *  @param pdf         the pdf of the distribution
     *  @param normalise   option to indicate whether or not to normalise
     *                     all probability data (default: no normalisation)
     */
    TabulatedAngularDistribution( TabulatedAngularDistributionFunction pdf,
                                  bool normalise = false ) :
      pdf_( std::move( pdf ) ), cdf_() {

      if ( normalise ) {

        this->normalise();
      }
      else {

        this->calculateCdf();
      }
    }

    /**
     *  @brief Constructor using a pdf and cdf
     *
     *  @param pdf   the pdf of the distribution
     *  @param cdf   the cdf of the distribution
     */
    TabulatedAngularDistribution( TabulatedAngularDistributionFunction pdf,
                                  TabulatedAngularDistributionFunction cdf ) :
      pdf_( std::move( pdf ) ), cdf_( std::move( cdf ) ) {}

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
