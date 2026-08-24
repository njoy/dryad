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
   *  scattering function and the atomic relaxation data are consistent.
   *
   *  When the Compton profile data contains a subshell that is not present
   *  in the atomic relaxation data, that profile is removed.
   *
   *  When the atomic relaxation data contains subshells that are not present
   *  in the Compton profiles, then an appropriate Compton profile for the
   *  missing subshell is selected based on the available subshells. That
   *  subshell is selected based on the quantum numbers of the missing subshell
   *  (n, l, l + m with m = +1/2 or -1/2), whichever is found first:
   *    - the shell with the same n and l but the other m
   *    - the shell with the same n, l - 1 and the same m
   *    - the shell with the same n, l - 1 and the other m
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

        // helper function to retrieve an iterator to a given profile id
        auto iterator = [] ( auto&& profiles , auto&& id ) {

          auto compare = [] ( auto&& profile, auto&& id ) { return profile.subshellIdentifier() < id; };
          return std::lower_bound( profiles.begin(), profiles.end(), id, compare );
        };

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

            std::vector< dryad::TabulatedComptonProfile > new_profiles = profiles;
            auto iter = std::remove_if( new_profiles.begin(), new_profiles.end(), remove_if );
            new_profiles.erase( iter, new_profiles.end() );

            // assign the profiles
            distribution.comptonProfiles( std::move( new_profiles ) );
          }
          else if ( relaxation.numberSubshells() > profiles.size() ) {

            // there are more subshells in the relaxation data than in the Compton profiles

            std::vector< dryad::TabulatedComptonProfile > new_profiles = profiles;
            for ( const auto& subshell : relaxation.subshells() ) {

              decltype(auto) id = subshell.identifier();
              auto iter = iterator( profiles, id );
              if ( iter == profiles.end() || iter->subshellIdentifier() != id ) {

                // determine if the angular value is ell + 1/2
                bool magnetic = id.totalAngularMomentum() == id.azimuthalQuantumNumber() + 0.5;

                // alternate shell: same principal, azimuthal, other angular
                dryad::id::ElectronSubshellID
                alternate( id.principalQuantumNumber(), id.azimuthalQuantumNumber(),
                           magnetic ? id.azimuthalQuantumNumber() - 0.5
                                    : id.azimuthalQuantumNumber() + 0.5 );

                auto copy = iterator( profiles, alternate );
                if ( copy == profiles.end() || copy->subshellIdentifier() != alternate ) {

                  // no luck, try alternate shell: same principal, azimuthal - 1, same magnetic spin
                  alternate =
                  dryad::id::ElectronSubshellID( id.principalQuantumNumber(), id.azimuthalQuantumNumber() - 1,
                                                 magnetic ? id.azimuthalQuantumNumber() - 0.5
                                                          : id.azimuthalQuantumNumber() - 1.5 );
                  copy = iterator( profiles, alternate );
                  if ( copy == profiles.end() || copy->subshellIdentifier() != alternate ) {

                    // no luck, try alternate shell: same principal, azimuthal - 1, other magnetic spin
                    alternate =
                    dryad::id::ElectronSubshellID( id.principalQuantumNumber(), id.azimuthalQuantumNumber() - 1,
                                                   magnetic ? id.azimuthalQuantumNumber() - 1.5
                                                            : id.azimuthalQuantumNumber() - 0.5 );
                    copy = iterator( profiles, alternate );
                  }
                }

                if ( copy != profiles.end() && copy->subshellIdentifier() == alternate ) {

                  Log::info( "Copying Compton profile for the {} subshell to the {} subshell",
                             alternate.symbol(), id.symbol() );
                  new_profiles.emplace_back( id,
                                             copy->momentum(), copy->values(),
                                             copy->boundaries(), copy->interpolants() );
                }
                else {

                  // still no luck, but this should never happen

                  throw std::runtime_error( "Could not find a Compton profile to copy, contact a developer" );
                }
              }
            }

            // assign the profiles
            distribution.comptonProfiles( std::move( new_profiles ) );
          }
        }
      }
    }
  }

} // medic namespace
} // njoy namespace

#endif
