#ifndef NJOY_DRYAD_INCOHERENTDISTRIBUTIONDATA
#define NJOY_DRYAD_INCOHERENTDISTRIBUTIONDATA

// system includes
#include <algorithm>
#include <optional>
#include <map>
#include <variant>

// other includes
#include "njoy/dryad/DistributionDataType.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"
#include "njoy/dryad/TabulatedScatteringFunction.hpp"
#include "njoy/dryad/TabulatedComptonProfile.hpp"
#include "njoy/dryad/external/KleinNishina.hpp"
#include "scion/integration/AdaptiveGaussLobatto.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The distribution data for incoherent scattering in photoatomic interactions
   *
   *  This representation is only available for a photoatomic ProjectileTarget.
   *
   *  In this representation, a scattering function S(x,Z) is defined that
   *  together with the Klein-Nishina cross section determines the double
   *  differential cross section.
   *
   *  This corresponds with the incoherent scattering function data given in
   *  MF27 MT504, supplemented with optional external Compton profile data.
   */
  class IncoherentDistributionData {

    /* fields */
    ReferenceFrame frame_;
    TabulatedScatteringFunction scattering_;

    std::optional< std::vector< TabulatedComptonProfile > > profiles_;

    /* auxiliary functions */

    #include "njoy/dryad/IncoherentDistributionData/src/sort.hpp"

  public:

    /* constructor */

    #include "njoy/dryad/IncoherentDistributionData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the distribution data type
     */
    static constexpr DistributionDataType type() {

      return DistributionDataType::Incoherent;
    }

    /**
     *  @brief Return the reference frame
     */
    const ReferenceFrame& frame() const {

      return this->frame_;
    }

    /**
     *  @brief Set the reference frame
     *
     *  @param[in] frame   the reference frame of the distribution data
     */
    void frame( ReferenceFrame frame ) {

      this->frame_ = std::move( frame );
    }

    /**
     *  @brief Return the scattering function
     */
    const TabulatedScatteringFunction& scatteringFunction() const {

      return this->scattering_;
    }

    /**
     *  @brief Set the scattering function
     *
     *  @param[in] scattering   the scattering function
     */
    void scatteringFunction( TabulatedScatteringFunction scattering ) {

      this->scattering_ = std::move( scattering );
    }

    /**
     *  @brief Calculate the average outgoing energy for a given energy
     *
     *  @param[in] energy      the incident energy
     *  @param[in] tolerance   the integration tolerance (default: 1e-8)
     */
    double averageEnergy( double energy,
                          double tolerance = constants::integration::tolerance ) const {

      auto xs = [&] ( double outgoing_energy ) {

        using namespace external;
        double cosine = KleinNishina::cosine( energy, outgoing_energy );
        double scatter = this->scatteringFunction()( energy, cosine );
        return scatter * KleinNishina::differentialCrossSectionToOutgoingEnergy( energy, outgoing_energy, cosine );
      };
      auto mean = [&] ( double outgoing_energy ) {

        return outgoing_energy * xs( outgoing_energy );
      };

      double min = external::KleinNishina::lowerOutgoingEnergyLimit( energy );
      double max = external::KleinNishina::upperOutgoingEnergyLimit( energy );

      scion::integration::AdaptiveGaussLobatto< double, double > integrator;
      return integrator( mean, min, max, tolerance ) / integrator( xs, min, max, tolerance );
    }

    /**
     *  @brief Calculate the average outgoing energy for a set of energies
     *
     *  @param[in] energies    the incident energies
     *  @param[in] tolerance   the integration tolerance (default: 1e-8)
     */
    std::vector< double > averageEnergy( const std::vector< double >& energies,
                                         double tolerance = constants::integration::tolerance ) const {

      std::vector< double > values( energies.size() );
      std::transform( energies.begin(), energies.end(), values.begin(),
                      [&] ( auto&& energy ) { return this->averageEnergy( energy, tolerance ); } );
      return values;
    }

    /**
     *  @brief Return the Compton profiles
     */
    const std::optional< std::vector< TabulatedComptonProfile > >&
    comptonProfiles() const {

      return this->profiles_;
    }

    /**
     *  @brief Return the Compton profiles
     */
    std::optional< std::vector< TabulatedComptonProfile > >&
    comptonProfiles() {

      return this->profiles_;
    }

    /**
     *  @brief Set the Compton profiles
     *
     *  @param[in] profiles   the Compton profiles
     */
    void comptonProfiles( std::optional< std::vector< TabulatedComptonProfile > > profiles ) {

      this->profiles_ = std::move( profiles );
      if ( this->profiles_.has_value() && this->profiles_.value().size() == 0 ) {

        this->profiles_ = std::nullopt;
      }
      else if ( this->profiles_.has_value() ) {

        this->sort();
      }
    }

    /**
     *  @brief Return whether or not Compton profiles are defined
     */
    bool hasComptonProfiles() const {

      return this->comptonProfiles().has_value();
    }

    /**
     *  @brief Normalise the distribution data
     *
     *  For incoherent data, this only affects the Compton profiles if they are
     *  defined.
     */
    void normalise() {

      if ( this->comptonProfiles().has_value() ) {

        for ( auto& profile : this->comptonProfiles().value() ) {

          profile.normalise();
        }
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const IncoherentDistributionData& right ) const {

      return std::tie( this->frame(), this->scatteringFunction(), this->comptonProfiles() ) ==
             std::tie( right.frame(), right.scatteringFunction(), right.comptonProfiles() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const IncoherentDistributionData& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
