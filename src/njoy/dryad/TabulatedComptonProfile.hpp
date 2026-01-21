#ifndef NJOY_DRYAD_TABULATEDCOMPTONPROFILE
#define NJOY_DRYAD_TABULATEDCOMPTONPROFILE

// system includes
#include <vector>

// other includes
#include "njoy/dryad/type-aliases.hpp"
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

    /* auxiliary functions */

    #include "njoy/dryad/TabulatedComptonProfile/src/calculateCdf.hpp"

  public:

    /* constructor */

    #include "njoy/dryad/TabulatedComptonProfile/src/ctor.hpp"

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
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const TabulatedComptonProfileFunction& cdf() const {

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
     *  @brief Return the average momentum defined by the distribution
     */
    double averageMomentum() const { return this->pdf().mean(); }

    /**
     *  @brief Return a linearised angular distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance
     *  @param[in] normalise   option to indicate whether or not to normalise
     *                         all probability data (default: no normalisation)
     */
    TabulatedComptonProfile linearise( ToleranceConvergence tolerance = {},
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
