#ifndef NJOY_DRYAD_RESONANCES_HARDSPHERESHIFTFACTOR
#define NJOY_DRYAD_RESONANCES_HARDSPHERESHIFTFACTOR

// system includes

// other includes
#include "scion/math/PolynomialSeriesRatio.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Hard sphere shift factor functions
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class HardSphereShiftFactor :
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

        case 0 : return { { 0 } };
        case 1 : return { { -1 }, { 1, 0, 1 } };
        case 2 : return { { -18, 0, -3 }, { 9, 0, 3, 0, 1 } };
        case 3 : return { { -675, 0, -90, 0, -6 }, { 225, 0, 45, 0, 6, 0, 1 } };
        case 4 : return { { -44100, 0, -4725, 0, -270, 0, -10 }, { 11025, 0, 1575, 0, 135, 0, 10, 0, 1 } };
        case 5: return  { { -4465125, 0, -396900, 0, -18900, 0, -630, 0, -15 }, { 893025, 0, 99225, 0, 6300, 0, 315, 0, 15, 0, 1 } };
        default : {

          Log::error( "Cannot handle wave functions with l above 5, got \'{}\', "
                      "contact dryad developers", l );
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
    HardSphereShiftFactor( PolynomialSeriesRatio< double, double > ratio ) :
      PolynomialSeriesRatio( std::move( ratio ) ) {}

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    HardSphereShiftFactor() = default;

    HardSphereShiftFactor( const HardSphereShiftFactor& ) = default;
    HardSphereShiftFactor( HardSphereShiftFactor&& ) = default;

    HardSphereShiftFactor& operator=( const HardSphereShiftFactor& ) = default;
    HardSphereShiftFactor& operator=( HardSphereShiftFactor&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param orbitalAngularMomentum   the value of the orbital angular momentum
     */
    HardSphereShiftFactor( unsigned int orbitalAngularMomentum ) :
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
    friend bool operator==( const HardSphereShiftFactor& left,
                            const HardSphereShiftFactor& right ) {

      return left.orbitalAngularMomentum() == right.orbitalAngularMomentum();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const HardSphereShiftFactor& left,
                            const HardSphereShiftFactor& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
