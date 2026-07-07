#ifndef NJOY_DRYAD_RESONANCES_REDUCEDWIDTHCONVERSION
#define NJOY_DRYAD_RESONANCES_REDUCEDWIDTHCONVERSION

//system includes
#include <cmath>
#include <tuple>

//other includes
#include "njoy/dryad/resonances/Channel.hpp"
#include "njoy/dryad/resonances/HardSpherePenetrability.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Hard sphere width conversion functions
   */
  class ReducedWidthConversion {

    /* fields */

    HardSpherePenetrability penetrability_;
    double reference_energy_;

  public:

    /* constructors */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ReducedWidthConversion() = default;

    ReducedWidthConversion( const ReducedWidthConversion& ) = default;
    ReducedWidthConversion( ReducedWidthConversion&& ) = default;

    ReducedWidthConversion& operator=( const ReducedWidthConversion& ) = default;
    ReducedWidthConversion& operator=( ReducedWidthConversion&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] orbitalAngularMomentum   the value of the orbital angular momentum
     *  @param[in] reference_energy         the reference energy at which the reduced width is
     *                                      defined (typically 1 eV)
     */
    ReducedWidthConversion( unsigned int orbitalAngularMomentum,
                            double reference_energy ) :
      penetrability_( orbitalAngularMomentum ),
      reference_energy_( reference_energy ) {}

    /* methods */

    /**
     *  @brief Return the underlying penetrability function
     */
    const HardSpherePenetrability& penetrability() const {

      return this->penetrability_;
    }

    /**
     *  @brief Return the value of the orbital angular momentum
     */
    unsigned int orbitalAngularMomentum() const {

      return this->penetrability().orbitalAngularMomentum();
    }

    /**
     *  @brief Return the reference energy at which the reduced neutron width is defined
     */
    double referenceEnergy() const {

      return this->reference_energy_;
    }

    /**
     *  @brief Evaluate the width conversion factor for a given ratio value
     *
     *  The factor is P_l(E) / P_0(E) * sqrt( E / E_ref), in which P_0(E) = rho.
     *
     *  @param[in] ratio    the ratio rho = k*a (wave number times channel radius)
     *  @param[in] energy   the energy in eV
     */
    double calculateConversionFactor( double ratio, double energy ) const {

      return ( this->penetrability()( ratio ) / ratio ) * std::sqrt( energy / this->referenceEnergy() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ReducedWidthConversion& right ) const {

      return std::tie( this->penetrability(), this->reference_energy_ ) ==
             std::tie( right.penetrability(), right.reference_energy_ );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ReducedWidthConversion& right ) const {

      return ! this->operator==( right );
    }
  };

} // namespace resonances
} // namespace dryad
} // namespace njoy

#endif
