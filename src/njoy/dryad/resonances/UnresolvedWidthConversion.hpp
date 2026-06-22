#ifndef NJOY_DRYAD_RESONANCES_UNRESOLVEDWIDTHCONVERSION
#define NJOY_DRYAD_RESONANCES_UNRESOLVEDWIDTHCONVERSION

namespace njoy {
namespace dryad {
namespace resonances {
  /**
   *  @struct
   *  @brief Tag type for channels whose width has no energy dependence
   *
   *  Used for capture and fission channels. The "reduced" width stored for
   *  these channels is the physical width.
   */
  struct ConstantWidthConversion {

    friend bool operator==( const ConstantWidthConversion&,
        const ConstantWidthConversion& ) noexcept {

      return true;
    }

    friend bool operator!=( const ConstantWidthConversion& left,
        const ConstantWidthConversion& right ) noexcept {

      return ! ( left == right );
    }
  };

  /**
   *  @struct
   *  @brief Tag type for channels whose width carries the standard
   *         reduced neutron width energy dependence
   *
   *  The conversion applied is
   *
   *      Gamma(E) = reduced * ( P_l(E) / P_l(E_ref) ) * sqrt( E / E_ref )
   *
   *  where P_l is the orbital-angular-momentum-dependent penetrability of
   *  the underlying channel and E_ref is the reference energy (typically 1 eV).
   *
   *  This is applied to the reduced elastic neutron widths.
   */
  struct NeutronWidthConversion {

    friend bool operator==( const NeutronWidthConversion&, 
                            const NeutronWidthConversion& ) noexcept {

      return true;
    }

    friend bool operator!=( const NeutronWidthConversion& left,
                            const NeutronWidthConversion& right ) noexcept {

      return ! ( left == right );
    }
  };
  
}
}
}
