#ifndef NJOY_DRYAD_RESONANCES_HARDSPHEREPENETRABILITY
#define NJOY_DRYAD_RESONANCES_HARDSPHEREPENETRABILITY

// system includes

// other includes
#include "scion/math/PolynomialSeriesRatio.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Hard sphere penetrability functions
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class HardSpherePenetrability :
      protected scion::math::PolynomialSeriesRatio< double, double > {

    /* fields */

    unsigned int orbital_momentum_;

    /* auxiliary functions */

    /**
     *  @brief Generate the polynomial ratio for a given l
     *
     *  @param l   the value of the orbital angular momentum
     */
    static PolynomialSeriesRatio generateFunction( unsigned int l ) {

      // see Table D.1 from the ENDF manual
      // ENDF-6 Formats Manual, CSEWG Document ENDF-102, NNDC, Brookhaven National Laboratory
      // https://www.nndc.bnl.gov/endf
      switch ( l ) {

        case 0 : return { { 0, 1 } };
        case 1 : return { { 0, 0, 0, 1 }, { 1, 0, 1 } };
        case 2 : return { { 0, 0, 0, 0, 0, 1 }, { 9, 0, 3, 0, 1 } };
        case 3 : return { { 0, 0, 0, 0, 0, 0, 0, 1 }, { 225, 0, 45, 0, 6, 0, 1 } };
        case 4 : return { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 11025, 0, 1575, 0, 135, 0, 10, 0, 1 } };
        case 5:  return { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, { 893025, 0, 99225, 0, 6300, 0, 315, 0, 15, 0, 1 } };
        default : {

          Log::error( "Cannot handle wave functions with l above 5, got \'{}\', "
                      "contact njoy developers", l );
          throw std::exception();
        }
      }
    }

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param table   the interpolation table
     */
    HardSpherePenetrability( PolynomialSeriesRatio< double, double > ratio ) :
      PolynomialSeriesRatio( std::move( ratio ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    HardSpherePenetrability() = default;

    HardSpherePenetrability( const HardSpherePenetrability& ) = default;
    HardSpherePenetrability( HardSpherePenetrability&& ) = default;

    HardSpherePenetrability& operator=( const HardSpherePenetrability& ) = default;
    HardSpherePenetrability& operator=( HardSpherePenetrability&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param orbitalAngularMomentum   the value of the orbital angular momentum
     */
    HardSpherePenetrability( unsigned int orbitalAngularMomentum ) :
      PolynomialSeriesRatio( generateFunction( orbitalAngularMomentum ) ),
      orbital_momentum_( orbitalAngularMomentum ) {}

    /* methods */

    /**
     *  @brief Return the value of the orbital angular momentum
     */
    unsigned int orbitalAngularMomentum() const {

      return this->orbital_momentum_;
    }

    using PolynomialSeriesRatio::operator();

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const HardSpherePenetrability& left,
                            const HardSpherePenetrability& right ) {

      return left.orbitalAngularMomentum() == right.orbitalAngularMomentum();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const HardSpherePenetrability& left,
                            const HardSpherePenetrability& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
