#ifndef NJOY_DRYAD_RESONANCES_UNRESOLVEDCHANNEL
#define NJOY_DRYAD_RESONANCES_UNRESOLVEDCHANNEL

#include <cmath>
#include <tuple>
#include <variant>
#include <optional>

#include "tools/overload.hpp"
#include "njoy/dryad/resonances/Channel.hpp"
#include "njoy/dryad/resonances/ReducedWidthConversion.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  class UnresolvedChannel : protected Channel {

    public:

      using ConversionFactor = std::variant< double,
                                             ReducedWidthConversion >;
      using Background = Channel::Background;

      using Channel::reaction;
      using Channel::identifier;
      using Channel::quantumNumbers;
      using Channel::background;
      using Channel::waveNumber;
      using Channel::outgoingParticlePair;
      using Channel::incidentParticlePair;
      using Channel::channelRadii;

    private:

      ConversionFactor conversion_factor_;
      double reference_energy_;

      /* auxiliary functions */
      #include "njoy/dryad/resonances/UnresolvedChannel/src/selectWidthConversion.hpp"



    public: 
      #include "njoy/dryad/resonances/UnresolvedChannel/src/ctor.hpp"

      const double referenceEnergy() const {

        return this->reference_energy_;
      }

      /**
       *  @brief Returns the conversion factor strategy to be applied to the given width
       *
       */
      const ConversionFactor& conversionFactorStrategy() const {

        return this->conversion_factor_;
      }

      /**
       *  @brief Calculate the conversion factor for a width
       *
       *  @param[in] energy   the energy (given in eV)
       */
      const double widthConversionFactor( double energy ) const {

        tools::overload visitor{

          []  ( const double ) -> double {

            return 1.0;
          },
          [&] ( const ReducedWidthConversion& function ) -> double {

            double rho = this->Channel::waveNumber( energy ) * this->channelRadii().calculatePenetrabilityRadius( energy );
            return function.calculateConversionFactor( rho, energy);

          }
        };

        return std::visit( visitor, this->conversion_factor_);
      }

      /**
       *  @brief Equality comparison
       *
       *  @param[in]  left    the object on the left hand side
       *  @param[in]  right   the object on the right hand side
       */
      friend bool operator==( const UnresolvedChannel& left,
                              const UnresolvedChannel& right ) {

        return static_cast< const Channel& >( left ) == static_cast< const Channel& >( right ) &&
               std::tie( left.conversion_factor_, left.reference_energy_ ) ==
               std::tie( right.conversion_factor_, right.reference_energy_ );
      }

      /**
       *  @brief Inequality comparison
       *
       *  @param[in]  left    the object on the left hand side
       *  @param[in]  right   the object on the right hand side
       */
      friend bool operator!=( const UnresolvedChannel& left,
                              const UnresolvedChannel& right ) {

        return ! ( left == right );
      }
  };
   
} // namespace resonances
} // namespace dryad
} // namespace njoy

#endif
