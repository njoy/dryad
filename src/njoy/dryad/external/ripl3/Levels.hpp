#ifndef NJOY_DRYAD_EXTERNAL_RIPL3_LEVELS
#define NJOY_DRYAD_EXTERNAL_RIPL3_LEVELS

// system includes
#include <map>
#include <stdexcept>

// other includes
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

    static inline std::map< id::ParticleID, LevelEntry > levels_ = {

      { id::ParticleID::photon(), { id::ParticleID::photon(), std::nullopt, 1.0, -1, std::nullopt } },
      { id::ParticleID::neutron(), { id::ParticleID::neutron(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::proton(), { id::ParticleID::proton(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::deuteron(), { id::ParticleID::deuteron(), std::nullopt, 1.0, 1, std::nullopt } },
      { id::ParticleID::triton(), { id::ParticleID::triton(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::helion(), { id::ParticleID::helion(), std::nullopt, 0.5, 1, std::nullopt } },
      { id::ParticleID::alpha(), { id::ParticleID::alpha(), std::nullopt, 0.0, 1, std::nullopt } }
    };

    /* auxiliary functions */

  public:

    /* methods */

    /**
     *  @brief Retrieve a level entry for a given particle
     *
     *  @param[in] id   the particle identifier
     */
    static const LevelEntry& level( const id::ParticleID& id ) {

      auto it = Levels::levels_.find( id );
      if ( it == Levels::levels_.end() ) {

        throw std::out_of_range( "Particle not found in RIPL-3 levels database" );
      }
      return it->second;
    }
  };

} // ripl3 namespace
} // external namespace
} // dryad namespace
} // njoy namespace

#endif