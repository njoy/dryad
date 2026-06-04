#ifndef NJOY_DRYAD_EXTERNAL_RIPL3_LEVELS
#define NJOY_DRYAD_EXTERNAL_RIPL3_LEVELS

// system includes
#include <filesystem>
#include <map>
#include <stdexcept>
#include <iostream>

// other includes
#include "tools/Log.hpp"
#include "tools/disco.hpp"
#include "njoy/configuration.hpp"
#include "njoy/constants.hpp"
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

    static inline std::optional< std::string > ripl3_levels_datapath_;

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

    #include "njoy/dryad/external/ripl3/Levels/src/iterator.hpp"
    #include "njoy/dryad/external/ripl3/Levels/src/insertData.hpp"

  public:

    /* methods */

    /**
     *  @brief Return the current size of the RIPL-3 levels data
     */
    static std::size_t size() {

      return Levels::levels_.size();
    }

    /**
     *  @brief Verify whether or not a given particle is present
     *
     *  @param[in] id   the particle identifier
     */
    static bool hasParticle( const id::ParticleID& id ) {

      return iterator( id ) == Levels::levels_.end();
    }

    /**
     *  @brief Retrieve a level entry for a given particle
     *
     *  @param[in] id   the particle identifier
     */
    static const LevelEntry& level( const id::ParticleID& id ) {

      auto iter = iterator( id );
      if ( iter == Levels::levels_.end() ) {

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
