#ifndef NJOY_DRYAD_EXTERNAL_COMPTONPROFILES
#define NJOY_DRYAD_EXTERNAL_COMPTONPROFILES

// system includes
#include <vector>
#include <vector>

// other includes
#include "tools/overload.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/TabulatedComptonProfile.hpp"

namespace njoy {
namespace dryad {
namespace external {

  /**
   *  @class
   *  @brief Compton profile models
   *
   *  Compton profiles are currently not available in standard evaluated nuclear data
   *  files. The ComptonProfiles class is basically going to contain factory functions
   *  to produce Compton profiles for a given atom, either based on external data or
   *  possibly model calculations.
   *
   *  Currently we only have tabulated data based on Biggs, Mendelsohn and Mann
   *  calculated profiles from the following reference:
   *    F. Biggs, L. B. Mendelsohn, J. B. Mann,
   *    Hartree-Fock Compton profiles for the elements,
   *    Atomic data and nuclear data table, 16, 201-309 (1975)
   */
  class ComptonProfiles {

    /* static fields */

    #include "njoy/dryad/external/ComptonProfiles/src/biggs_mendelsohn_mann.hpp"

  public:

    /* constructor */

    /* methods */

    /**
     *  @brief Return the electron subshell identifiers for a given z number
     *         for which Biggs, Mendelsohn and Mann Compton profiles are available
     *
     *  @param[in] z   the z number of the atom
     */
    static std::vector< id::ElectronSubshellID >
    biggsMendelsohnMannSubshellIdentifiers( unsigned int z ) {

      return biggs_mendelsohn_mann_shells.at( z );
    }

    /**
     *  @brief Return Biggs, Mendelsohn and Mann Compton profiles for a given z number
     *
     *  @param[in] z           the z number of the atom
     *  @param[in] normalise   option to indicate whether or not to normalise
     *                         all probability data (default: no normalisation)
     */
    static std::vector< TabulatedComptonProfile >
    biggsMendelsohnMannProfiles( unsigned int z,
                                 bool normalise = false ) {

      if ( z > 0 && z < 103 ) {

        // temporary code since we don't have all profiles yet
        if ( biggs_mendelsohn_mann_data.at( z ).front().size() == 0 ) {

          throw std::runtime_error( "Compton profiles for z = " + std::to_string( z ) +
                                    " not available yet, contact a developer" );
        }

        std::vector< TabulatedComptonProfile > profiles;

        std::vector< id::ElectronSubshellID > shells = biggs_mendelsohn_mann_shells.at( z );
        std::vector< double > momentum = biggs_mendelsohn_mann_momentum;
        std::vector< std::vector< double > > data = biggs_mendelsohn_mann_data.at( z );
        for ( unsigned int i = 0; i < shells.size(); ++i ) {

          profiles.emplace_back( shells[i], momentum, std::move( data[i] ),
                                 InterpolationType::LinearLinear, normalise );
        }

        return profiles;
      }
      else {

        throw std::out_of_range( "The z number must be between 1 and 102 for Biggs, Mendelsohn "
                                 "and Mann Compton profiles" );
      }
    }

    /**
     *  @brief Apply Compton profiles to a ProjectileTarget instance
     *
     *  @param[in,out] pt      the projectile-target data to be modified
     *  @param[in] normalise   option to indicate whether or not to normalise
     *                         all probability data (default: no normalisation)
     */
    static void apply( ProjectileTarget& pt,
                       bool normalise = false ) {

      if ( pt.interactionType() == dryad::InteractionType::Atomic &&
           pt.projectileIdentifier() == dryad::id::ParticleID::photon() ) {

        decltype(auto) projectile = pt.projectileIdentifier();
        decltype(auto) target = pt.targetIdentifier();
        dryad::id::ReactionID incoherent_id( projectile, target, dryad::id::ReactionType( "incoherent" ) );

        decltype(auto) incoherent = pt.reaction( incoherent_id );
        decltype(auto) photon = incoherent.product( dryad::id::ParticleID::photon() ).distributionData().value();

        auto updateComptonProfiles = tools::overload{

          [&] ( dryad::IncoherentDistributionData& data ) {

            data.comptonProfiles( ComptonProfiles::biggsMendelsohnMannProfiles( target.z(), normalise ) );
          },
          [] ( auto&& ) {

            throw std::runtime_error( "This should be unreachable code, contact a developer" );
          }
        };

        std::visit( updateComptonProfiles, photon );
      }
      else {

        throw std::runtime_error( "The projectile-target is not photoatomic, cannot apply "
                                  "Compton profiles" );
      }
    }
  };

} // external namespace
} // dryad namespace
} // njoy namespace

#endif
