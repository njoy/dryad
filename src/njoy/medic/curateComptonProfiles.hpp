#ifndef NJOY_MEDIC_CURATECOMPTONPROFILES
#define NJOY_MEDIC_CURATECOMPTONPROFILES

// system includes
#include <algorithm>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"

namespace njoy {
namespace medic {

  /**
   *  @brief Curate the Compton profile data
   *
   *  This function ensures that the Compton profile data in the incoherent
   *  scattering function and the atomic relaxation data are consistent. The
   *  following operations are performed on the Compton profile data:
   *    - when the Compton profile data contains a subshell that is not present
   *      in the atomic relaxation data, that profile is removed
   *    - when the atomic relaxation data contains subshells that are not present
   *      in the Compton profiles, then the Compton profile for the missing subshell
   *      is set to the one with the same principal and azimuthal quantum number
   *      that is already present
   *
   *  @param[in,out] photoatomic   the photoatomic projectile-target data
   *  @param[in]     relaxation    the atomic relaxation data
   */
  inline void curateComptonProfiles( dryad::ProjectileTarget& photoatomic,
                                     const dryad::AtomicRelaxation& relaxation ) {

    if ( photoatomic.interactionType() == dryad::InteractionType::Atomic &&
         photoatomic.projectileIdentifier() == dryad::id::ParticleID::photon() ) {

      decltype(auto) projectile = photoatomic.projectileIdentifier();
      decltype(auto) target = photoatomic.targetIdentifier();
      dryad::id::ReactionID incoherent_id( projectile, target, dryad::id::ReactionType( "incoherent" ) );

      decltype(auto) incoherent = photoatomic.reaction( incoherent_id );
      decltype(auto) photon = incoherent.product( dryad::id::ParticleID::photon() ).distributionData().value();

      if ( ! std::holds_alternative< dryad::IncoherentDistributionData >( photon ) ) {

        throw std::runtime_error( "Expected incoherent scattering data, found something else" );
      }
      decltype(auto) distribution = std::get< dryad::IncoherentDistributionData >( photon );

      if ( distribution.hasComptonProfiles() ) {

        // get the profiles
        decltype(auto) profiles = distribution.comptonProfiles().value();

        // determine the type of Compton profile: relativistic or non-relativistic
        auto is_relativistic = [] ( auto&& profile ) {

          return profile.subshellIdentifier().isRelativistic();
        };
        bool relativistic = std::all_of( profiles.begin(), profiles.end(), is_relativistic );

        // currently we only curate relativistic Compton profiles
        if ( relativistic ) {

          if ( relaxation.numberSubshells() < profiles.size() ) {

            // there are less subshells in the relaxation data than in the Compton profiles

            auto remove_if = [&] ( auto&& profile ) {

              Log::info( "Removing Compton profile for the {} subshell", profile.subshellIdentifier().symbol() );
              return ! relaxation.hasSubshell( profile.subshellIdentifier() );
            };

            auto iter = std::remove_if( profiles.begin(), profiles.end(), remove_if );
            profiles.erase( iter, profiles.end() );
          }
          else if ( relaxation.numberSubshells() > profiles.size() ) {

            // there are more subshells in the relaxation data than in the Compton profiles

            auto compare = [] ( auto&& profile, auto&& id ) { return profile.subshellIdentifier() < id; };
            auto compare_quantum_numbers = [] ( auto&& profile, auto&& id ) {

              auto id_principal = id.principalQuantumNumber();
              auto id_azimuthal = id.azimuthalQuantumNumber();
              auto principal = profile.subshellIdentifier().principalQuantumNumber();
              auto azimuthal = profile.subshellIdentifier().azimuthalQuantumNumber();
              return std::tie( principal, azimuthal ) < std::tie( id_principal, id_azimuthal );
            };

            for ( const auto& subshell : relaxation.subshells() ) {

              decltype(auto) id = subshell.identifier();
              auto iter = std::lower_bound( profiles.begin(), profiles.end(), id, compare );
              if ( iter == profiles.end() || iter->subshellIdentifier() != id ) {

                auto find_similar = [] ( auto&& profile, auto&& id ) {

                  auto principal = id.principalQuantumNumber();
                  auto azimuthal = id.azimuthalQuantumNumber();
                  return profile.subshellIdentifier() < id;
                };
                auto copy = std::lower_bound( profiles.begin(), profiles.end(), id, compare_quantum_numbers );
                if ( copy != profiles.end() &&
                     copy->subshellIdentifier().principalQuantumNumber() == id.principalQuantumNumber() &&
                     copy->subshellIdentifier().azimuthalQuantumNumber() == id.azimuthalQuantumNumber() ) {

                  Log::info( "Copying Compton profile for the {} subshell to the {} subshell",
                             copy->subshellIdentifier().symbol(), id.symbol() );
                  profiles.emplace( iter, id,
                                    copy->momentum(), copy->values(),
                                    copy->boundaries(), copy->interpolants() );
                }
                else {

                  throw std::runtime_error( "Could not find a Compton profile to copy" );
                }
              }
            }
          }
        }
      }
    }
  }

} // medic namespace
} // njoy namespace

#endif
