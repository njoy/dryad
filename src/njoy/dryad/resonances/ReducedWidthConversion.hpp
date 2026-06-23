#ifndef NJOY_DRYAD_RESONANCES_REDUCEDWIDTHCONVERSION
#define NJOY_DRYAD_RESONANCES_REDUCEDWIDTHCONVERSION

//system includes
#include <cmath>

//other includes
#include "njoy/dryad/resonances/Channel.hpp"
#include "njoy/dryad/resonances/HardSpherePenetrability.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief determines the factor used to convert reduced neutron width to full neutron width
   */
  class ReducedWidthConversion {

    private:

      /* fields */
      HardSpherePenetrability penetrability_;
      double reference_energy_;
      unsigned int orbital_angular_momentum_;

    public:

      #include "njoy/dryad/resonances/ReducedWidthConversion/src/ctor.hpp"

      /**
       *  @brief Return the orbital angular momentum of the channel
       */
      unsigned int orbitalAngularMomentum() const {

        return this->orbital_angular_momentum_;
      }

      /**
       *  @brief Return the reference energy at which the reduced neutron width is defined
       */
      double referenceEnergy() const {

        return this->reference_energy_;
      }

      /**
       *  @brief Calculate the width conversion factor
       *
       *  The factor is (P_l(E)/P_0(E)) * sqrt( E / E_ref), in which 
       *  P_0(E) = rho.
       *
       *  @param[in] rho    the dimensionless quantity k * a at the given energy
       *  @param[in] energy the energy in eV
       */
      double calculateConversionFactor( double rho, double energy ) const {

        return ( this->penetrability_( rho ) / rho ) * std::sqrt( energy / this->reference_energy_ );
      }
      /**
       *  @brief Equality comparison
       *
       *  @param[in] left    the object on the left hand side
       *  @param[in] right   the object on the right hand side
       */
      friend bool operator==( const ReducedWidthConversion& left,
                              const ReducedWidthConversion& right ) {

        return ( left.penetrability_ == right.penetrability_ )
          && ( left.reference_energy_ == right.reference_energy_ );
      }

      /**
       *  @brief Inequality comparison
       *
       *  @param[in] left    the object on the left hand side
       *  @param[in] right   the object on the right hand side
       */
      friend bool operator!=( const ReducedWidthConversion& left,
                              const ReducedWidthConversion& right ) {

        return ! ( left == right );
      }

  };

} // namespace resonances
} // namespace dryad
} // namespace njoy

#endif
