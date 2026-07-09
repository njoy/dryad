#ifndef NJOY_DRYAD_RESONANCES_HARDSPHEREPENETRABILITYRATIO
#define NJOY_DRYAD_RESONANCES_HARDSPHEREPENETRABILITYRATIO

// system includes

// other includes
#include "scion/math/PolynomialSeriesRatio.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Hard sphere penetrability ratio functions
   *
   *  This functor represents the ratio of two penetrability functions. The
   *  numerator function can have an orbital angular momentum of 0 to 5 while
   *  it is only coded for an orbital angular momentum of 0 in the denominator.
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class HardSpherePenetrabilityRatio :
      protected scion::math::PolynomialSeriesRatio< double, double > {

    /* fields */
    unsigned int numerator_orbital_momentum_;
    unsigned int denominator_orbital_momentum_;

    /* auxiliary functions */

    /**
     *  @brief Generate the polynomial ratio based on the numerator and denominator
     *         orbital angular momentum values
     *
     *  @param[in] numerator_l     the orbital angular momentum of the numerator
     *  @param[in] denominator_l   the orbital angular momentum of the denominator
     */
    static PolynomialSeriesRatio generateFunction( unsigned int numerator_l,
                                                   unsigned int denominator_l ) {

      // see Table D.1 from the ENDF manual
      // ENDF-6 Formats Manual, CSEWG Document ENDF-102, NNDC, Brookhaven National Laboratory
      // https://www.nndc.bnl.gov/endf

      switch ( denominator_l ) {

        case 0 : {

          switch ( numerator_l ) {

            case 0 : return { { 1 } };
            case 1 : return { { 0, 0, 1 }, { 1, 0, 1 } };
            case 2 : return { { 0, 0, 0, 0, 1 }, { 9, 0, 3, 0, 1 } };
            case 3 : return { { 0, 0, 0, 0, 0, 0, 1 }, { 225, 0, 45, 0, 6, 0, 1 } };
            case 4 : return { { 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 11025, 0, 1575, 0, 135, 0, 10, 0, 1 } };
            case 5:  return { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 893025, 0, 99225, 0, 6300, 0, 315, 0, 15, 0, 1 } };
            default : {

              Log::error( "Cannot handle wave functions with l above 5, got \'{}\', "
                          "contact njoy developers", numerator_l );
              throw std::exception();
            }
          }
        }
        default : {

          if ( denominator_l == numerator_l ) {

            return { { 1 } };
          }
          else {

            Log::error( "Cannot handle denominator wave functions with l above 0, got \'{}\', "
                        "contact njoy developers", denominator_l );
            throw std::exception();
          }
        }
      }
    }

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param table   the interpolation table
     */
    HardSpherePenetrabilityRatio( PolynomialSeriesRatio< double, double > ratio ) :
      PolynomialSeriesRatio( std::move( ratio ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    HardSpherePenetrabilityRatio() = default;

    HardSpherePenetrabilityRatio( const HardSpherePenetrabilityRatio& ) = default;
    HardSpherePenetrabilityRatio( HardSpherePenetrabilityRatio&& ) = default;

    HardSpherePenetrabilityRatio& operator=( const HardSpherePenetrabilityRatio& ) = default;
    HardSpherePenetrabilityRatio& operator=( HardSpherePenetrabilityRatio&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param orbitalAngularMomentum   the value of the orbital angular momentum
     */
    HardSpherePenetrabilityRatio( unsigned int numeratorOrbitalMomentum,
                                  unsigned int denominatorOrbitalMomentum ) :
      PolynomialSeriesRatio( generateFunction( numeratorOrbitalMomentum,
                                               denominatorOrbitalMomentum ) ),
      numerator_orbital_momentum_( numeratorOrbitalMomentum ),
      denominator_orbital_momentum_( denominatorOrbitalMomentum ) {}

    /* methods */

    /**
     *  @brief Return the value of the numerator orbital angular momentum
     */
    unsigned int numeratorOrbitalAngularMomentum() const {

      return this->numerator_orbital_momentum_;
    }

    /**
     *  @brief Return the value of the denominator orbital angular momentum
     */
    unsigned int denominatorOrbitalAngularMomentum() const {

      return this->denominator_orbital_momentum_;
    }

    using PolynomialSeriesRatio::operator();

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const HardSpherePenetrabilityRatio& right ) const {

      return std::tie( this->numerator_orbital_momentum_, this->denominator_orbital_momentum_ ) ==
             std::tie( right.numerator_orbital_momentum_, right.denominator_orbital_momentum_ );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const HardSpherePenetrabilityRatio& right ) const {

      return ! this->operator==( right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
