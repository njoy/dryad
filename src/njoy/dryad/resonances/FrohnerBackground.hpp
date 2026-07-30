#ifndef NJOY_DRYAD_RESONANCES_FROHNERBACKGROUND
#define NJOY_DRYAD_RESONANCES_FROHNERBACKGROUND

// system includes
#include <cmath>
#include <complex>

// other includes

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief A channel background using the Frohner parametrisation
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class FrohnerBackground {

    /* fields */

    double distant_level_;
    double pole_strength_;
    double average_radiation_width_;
    double lower_singularity_;
    double upper_singularity_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    FrohnerBackground() = default;

    FrohnerBackground( const FrohnerBackground& ) = default;
    FrohnerBackground( FrohnerBackground&& ) = default;

    FrohnerBackground& operator=( const FrohnerBackground& ) = default;
    FrohnerBackground& operator=( FrohnerBackground&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] distantLevelParameter   the distant level parameter
     *  @param[in] poleStrength            the pole strength
     *  @param[in] averageRadiationWidth   the average radiation width
     *  @param[in] lowerSingularity        the lower logarithmic singularity values
     *  @param[in] upperSingularity        the upper logarithmic singularity values
     */
    FrohnerBackground( double distantLevelParameter,
                       double poleStrength,
                       double averageRadiationWidth,
                       double lowerSingularity,
                       double upperSingularity ) :
      distant_level_( distantLevelParameter ),
      pole_strength_( poleStrength ),
      average_radiation_width_( averageRadiationWidth ),
      lower_singularity_( lowerSingularity ),
      upper_singularity_( upperSingularity ) {}

    /* methods */

    /**
     *  @brief Return the distant level parameter
     */
    double distantLevelParameter() const {

      return this->distant_level_;
    }

    /**
     *  @brief Return the pole strength
     */
    double poleStrength() const {

      return this->pole_strength_;
    }

    /**
     *  @brief Return the average radiation width
     */
    double averageRadiationWidth() const {

      return this->average_radiation_width_;
    }

    /**
     *  @brief Return the logarithmic singularity below the energy range
     */
    double lowerSingularity() const {

      return this->lower_singularity_;
    }

    /**
     *  @brief Return the logarithmic singularity above the energy range
     */
    double upperSingularity() const {

      return this->upper_singularity_;
    }

    /**
     *  @brief Evaluate the background function for a given energy
     *
     *  @param[in] energy   the energy (given in eV)
     */
    std::complex< double > operator()( double energy ) const {

      double delta = this->upperSingularity() - this->lowerSingularity();
      double average = 0.5 * ( this->lowerSingularity() + this->upperSingularity() );
      double ratio = 2. * ( energy - average ) / delta;
      double real = std::atanh( ratio );
      double imag = this->averageRadiationWidth() / delta / ( 1. - ratio * ratio );

      return { this->distantLevelParameter() + 2. * this->poleStrength() * real,
               2. * this->poleStrength() * imag };
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const FrohnerBackground& left,
                            const FrohnerBackground& right ) {

      return left.distantLevelParameter() == right.distantLevelParameter() &&
             left.poleStrength() == right.poleStrength() &&
             left.averageRadiationWidth() == right.averageRadiationWidth() &&
             left.lowerSingularity() == right.lowerSingularity() &&
             left.upperSingularity() == right.upperSingularity();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const FrohnerBackground& left,
                            const FrohnerBackground& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
