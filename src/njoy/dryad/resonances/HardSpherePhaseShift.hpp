#ifndef NJOY_DRYAD_RESONANCES_HARDSPHEREPHASESHIFT
#define NJOY_DRYAD_RESONANCES_HARDSPHEREPHASESHIFT

// system includes
#include <cmath>

// other includes
#include "scion/math/PolynomialSeriesRatio.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Hard sphere phase shift functions
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class HardSpherePhaseShift {

    /* fields */
    scion::math::PolynomialSeriesRatio< double, double > ratio_;
    unsigned int orbital_momentum_;

    /* auxiliary functions */

    /**
     *  @brief Generate the polynomial ratio for a given l
     *
     *  @param l   the value of the orbital angular momentum
     */
    static scion::math::PolynomialSeriesRatio< double, double >
    generateFunction( unsigned int l ) {

      // see Table D.1 from the ENDF manual
      // ENDF-6 Formats Manual, CSEWG Document ENDF-102, NNDC, Brookhaven National Laboratory
      // https://www.nndc.bnl.gov/endf
      switch ( l ) {

        case 0 : return { { 0 } };
        case 1 : return { { 0, 1 } };
        case 2 : return { { 0, 3 }, { 3, 0, -1 } };
        case 3 : return { { 0, 15, 0, -1 }, { 15, 0, -6 } };
        case 4 : return { { 0, 105, 0, -10 }, { 105, 0, -45, 0, 1 } };
        case 5 : return { { 0, 945, 0, -105, 0, 1 }, { 945, 0, -420, 0, 15 } };
        default : {

          Log::error( "Cannot handle wave functions with l above 5, got \'{}\', "
                      "contact dryad developers", l );
          throw std::exception();
        }
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    HardSpherePhaseShift() = default;

    HardSpherePhaseShift( const HardSpherePhaseShift& ) = default;
    HardSpherePhaseShift( HardSpherePhaseShift&& ) = default;

    HardSpherePhaseShift& operator=( const HardSpherePhaseShift& ) = default;
    HardSpherePhaseShift& operator=( HardSpherePhaseShift&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param orbitalAngularMomentum   the value of the orbital angular momentum
     */
    HardSpherePhaseShift( unsigned int orbitalAngularMomentum ) :
      ratio_( generateFunction( orbitalAngularMomentum ) ),
      orbital_momentum_( orbitalAngularMomentum ) {}

    /* methods */

    /**
     *  @brief Return the value of the orbital angular momentum
     */
    unsigned int orbitalAngularMomentum() const {

      return this->orbital_momentum_;
    }

    /**
     *  @brief Evaluate the phase shift for a given ratio value
     *
     *  @param[in] ratio   the ratio value
     */
    double operator()( double ratio ) const {

      return ratio - std::atan( this->ratio_( ratio ) );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const HardSpherePhaseShift& left,
                            const HardSpherePhaseShift& right ) {

      return left.orbitalAngularMomentum() == right.orbitalAngularMomentum();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const HardSpherePhaseShift& left,
                            const HardSpherePhaseShift& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
