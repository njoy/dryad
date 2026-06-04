#ifndef NJOY_DRYAD_EXTERNAL_RIPL3_LEVELS
#define NJOY_DRYAD_EXTERNAL_RIPL3_LEVELS

// system includes
#include <filesystem>
#include <map>
#include <stdexcept>

// other includes
#include "njoy/configuration.hpp"
#include "njoy/dryad/external/ripl3/LevelEntry.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace external {
namespace ripl3 {

  /**
   *  @class
   *  @brief RIPL-3 level data
   *
   *  The Levels class allows a user to interact with the  nuclear levels part of the RIPL-3
   *  database.
   */
  class Levels {

    /* fields */

    static std::optional< std::string > ripl3_levels_datapath_;

    static inline std::map< id::ParticleID, LevelEntry > levels_ = {

      { id::ParticleID::photon(), { id::ParticleID::photon(), std::nullopt, 1.0, -1, std::nullopt } },
      { id::ParticleID::electron(), { id::ParticleID::electron(), std::nullopt, std::nullopt, std::nullopt, std::nullopt } },
      { id::ParticleID::positron(), { id::ParticleID::positron(), std::nullopt, std::nullopt, std::nullopt, std::nullopt } },
      { id::ParticleID::neutron(), { id::ParticleID::neutron(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::proton(), { id::ParticleID::proton(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::deuteron(), { id::ParticleID::deuteron(), std::nullopt, 1.0, 1, std::nullopt } },
      { id::ParticleID::triton(), { id::ParticleID::triton(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::helion(), { id::ParticleID::helion(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::alpha(), { id::ParticleID::alpha(), std::nullopt, 0.0, 1, std::nullopt } }
    };

    /* auxiliary functions */

    static void insertData( int z ) {

      if ( ! ripl3_levels_datapath_.has_value() ) {

        auto& config = configuration();
        ripl3_levels_datapath_ = config.get( "ripl3_levels" );
      }

      std::filesystem::path path( ripl3_levels_datapath_.value() );
    }

  public:

    /* methods */

    /**
     *  @brief Retrieve a level entry for a given particle
     *
     *  @param[in] id   the particle identifier
     */
    static const LevelEntry& level( const id::ParticleID& id ) {

      auto iter = Levels::levels_.find( id );
      if ( iter == Levels::levels_.end() ) {

        if ( id.a() != 0 ) {

          //
        }

        throw std::out_of_range( "Particle not found in RIPL-3 levels database" );
      }
      return iter->second;
    }
  };

} // ripl3 namespace
} // external namespace
} // dryad namespace
} // njoy namespace

#endif
