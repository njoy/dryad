#ifndef NJOY_DRYAD_RESONANCES_SAMMYBACKGROUND
#define NJOY_DRYAD_RESONANCES_SAMMYBACKGROUND

// system includes
#include <array>

// other includes
#include "scion/math/horner.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief A channel background using the SAMMY parametrisation
   *
   *  The SAMMY parametrisation of a channel background is a function
   *  of energy consisting of a quadratic polynomial and a logarithmic
   *  term. It is characterised by 7 parameters:
   *    - 3 coefficients of the polymonial term (R0, R1 and R2)
   *    - 2 constants for the logarithmic term (S0 and S1)
   *    - 2 logarithmic singularity values (Ed and Eu)
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class SammyBackground {

    /* fields */

    std::array< double, 3 > polynomial_coefficients_;
    std::array< double, 2 > logarithmic_coefficients_;
    double lower_singularity_;
    double upper_singularity_;

    /* auxiliary functions */

  public:

    /* constructor */

    #include "njoy/dryad/resonances/SammyBackground/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the coefficients of the polynomial term
     */
    const std::array< double, 3 >& polynomialCoefficients() const {

      return this->polynomial_coefficients_;
    }

    /**
     *  @brief Return the coefficients of the logarithmic term
     */
    const std::array< double, 2 >& logarithmicCoefficients() const {

      return this->logarithmic_coefficients_;
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
    double operator()( double energy ) const {

      double delta = this->upperSingularity() - this->lowerSingularity();
      double log = std::log( ( this->upperSingularity() - energy ) /
                             ( energy - this->lowerSingularity() ) );

      auto polynomial = scion::math::horner< double, double >( this->polynomialCoefficients(), energy );
      auto logarithmic = scion::math::horner< double, double >( this->logarithmicCoefficients(), energy );
      return polynomial - this->logarithmicCoefficients()[1] * delta - logarithmic * log;
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const SammyBackground& left,
                            const SammyBackground& right ) {

      return left.polynomialCoefficients() == right.polynomialCoefficients() &&
             left.logarithmicCoefficients() == right.logarithmicCoefficients() &&
             left.lowerSingularity() == right.lowerSingularity() &&
             left.upperSingularity() == right.upperSingularity();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const SammyBackground& left,
                            const SammyBackground& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
