#ifndef NJOY_DRYAD_TABULATEDCOMPTONPROFILE
#define NJOY_DRYAD_TABULATEDCOMPTONPROFILE

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/dryad/id/ElectronSubshellID.hpp"
#include "njoy/dryad/TabulatedComptonProfileFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A Compton profile for an electron subshell defined by a pdf and cdf using
   *         tabulated data
   *
   *  Compton profiles are not available in standard evaluated nuclear data files.
   *  They are used for photoatomic transport data in Monte Carlo codes like MCNP,
   *  which currently get this data form external sources.
   */
  class TabulatedComptonProfile {

    /* fields */
    id::ElectronSubshellID id_;

    TabulatedComptonProfileFunction pdf_;
    TabulatedComptonProfileFunction cdf_;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedComptonProfile() = default;

    TabulatedComptonProfile( const TabulatedComptonProfile& ) = default;
    TabulatedComptonProfile( TabulatedComptonProfile&& ) = default;

    TabulatedComptonProfile& operator=( const TabulatedComptonProfile& ) = default;
    TabulatedComptonProfile& operator=( TabulatedComptonProfile&& ) = default;

    /**
     *  @brief Constructor using a pdf
     *
     *  @param identifier   the electron subshell identifier
     *  @param pdf          the pdf of the distribution
     *  @param normalise    option to indicate whether or not to normalise
     *                      all probability data (default: no normalisation)
     */
    TabulatedComptonProfile(
        id::ElectronSubshellID identifier,
        TabulatedComptonProfileFunction pdf,
        bool normalise = false ) :
      id_( std::move( identifier ) ),
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
     *  @param identifier     the electron subshell identifier
     *  @param momentum       the momentum values
     *  @param values         the probability values
     *  @param boundaries     the boundaries of the interpolation regions
     *  @param interpolants   the interpolation types of the interpolation regions
     *  @param normalise      option to indicate whether or not to normalise
     *                        all probability data (default: no normalisation)
     */
    TabulatedComptonProfile(
        id::ElectronSubshellID identifier,
        std::vector< double > momentum,
        std::vector< double > values,
        std::vector< std::size_t > boundaries,
        std::vector< InterpolationType > interpolants,
        bool normalise = false ) :
      TabulatedComptonProfile(
          std::move( identifier ) ,
          TabulatedComptonProfileFunction( std::move( momentum ), std::move( values ),
                                           std::move( boundaries ), std::move( interpolants ) ),
          normalise ) {}

    /**
     *  @brief Constructor for a pdf using a single interpolation zone
     *
     *  @param identifier     the electron subshell identifier
     *  @param momentum       the momentum values
     *  @param values         the probability values
     *  @param interpolant    the interpolation type of the data (default lin-lin)
     *  @param normalise      option to indicate whether or not to normalise
     *                        all probability data (default: no normalisation)
     */
    TabulatedComptonProfile(
        id::ElectronSubshellID identifier,
        std::vector< double > momentum,
        std::vector< double > values,
        InterpolationType interpolant = InterpolationType::LinearLinear,
        bool normalise = false ) :
      TabulatedComptonProfile(
          std::move( identifier ) ,
          TabulatedComptonProfileFunction( std::move( momentum ), std::move( values ),
                                           std::move( interpolant ) ),
          normalise ) {}

    /**
     *  @brief Constructor using a pdf and cdf
     *
     *  @param identifier   the electron subshell identifier
     *  @param pdf          the pdf of the distribution
     *  @param cdf          the cdf of the distribution
     */
    TabulatedComptonProfile(
        id::ElectronSubshellID identifier,
        TabulatedComptonProfileFunction pdf,
        TabulatedComptonProfileFunction cdf ) :
      id_( std::move( identifier ) ),
      pdf_( std::move( pdf ) ), cdf_( std::move( cdf ) ) {}

    /* methods */

    /**
     *  @brief Return the electron subshell identifier
     */
    const id::ElectronSubshellID& subshellIdentifier() const {

      return this->id_;
    }

    /**
     *  @brief Return the momentum values
     */
    const std::vector< double >& momentum() const {

      return this->pdf().momentum();
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
    const TabulatedComptonProfileFunction& pdf() const {

      return this->pdf_;
    }

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    TabulatedComptonProfileFunction& pdf() {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const TabulatedComptonProfileFunction& cdf() const {

      return this->cdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    TabulatedComptonProfileFunction& cdf() {

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

      this->pdf().normalise();
      this->cdf() = this->pdf().calculateCdf();
    }

    /**
     *  @brief Return the average momentum defined by the distribution
     */
    double averageMomentum() const {

      return this->pdf().mean();
    }

    /**
     *  @brief Return a linearised Compton profile table
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     *  @param[in] normalise   option to indicate whether or not to normalise
     *                         all probability data (default: no normalisation)
     */
    TabulatedComptonProfile linearise( double tolerance = constants::linearisation::tolerance,
                                       bool normalise = false ) const {

      TabulatedComptonProfileFunction pdf = this->pdf().linearise( tolerance );
      return TabulatedComptonProfile( this->subshellIdentifier(), std::move( pdf ), normalise );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedComptonProfile& right ) const {

      return this->pdf() == right.pdf() && this->cdf() == right.cdf();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedComptonProfile& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
