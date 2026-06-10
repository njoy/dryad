#ifndef NJOY_DRYAD_EXTERNAL_AME_MASSES
#define NJOY_DRYAD_EXTERNAL_AME_MASSES

// system includes
#include <map>

#if __has_include(<filesystem>) && (__cplusplus >= 201703L)
#include <filesystem>
namespace filesystem = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace filesystem = std::experimental::filesystem;
#endif

// other includes
#include "tools/Log.hpp"
#include "tools/disco.hpp"
#include "njoy/configuration.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/external/ame/MassEntry.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace external {
namespace ame {

  /**
   *  @class
   *  @brief Atomic mass data from AME2020
   *
   *  The Masses class allows a user to interact with the AME2020 mass data.
   */
  class Masses {

    /* fields */

    static inline std::map< id::ParticleID, MassEntry > masses_;

    /* auxiliary functions */

    #include "njoy/dryad/external/ame/Masses/src/iterator.hpp"
    #include "njoy/dryad/external/ame/Masses/src/loadData.hpp"

  public:

    /* methods */

    /**
     *  @brief Return the current size of the AME2020 mass data
     */
    static std::size_t size() {

      return Masses::masses_.size();
    }

    /**
     *  @brief Verify whether or not a given particle is present
     *
     *  @param[in] id   the particle identifier
     */
    static bool hasEntry( const id::ParticleID& id ) {

      return iterator( id ) != Masses::masses_.end();
    }

    /**
     *  @brief Retrieve a mass entry for a given particle
     *
     *  @param[in] id   the particle identifier
     */
    static const MassEntry& entry( const id::ParticleID& id ) {

      auto iter = iterator( id );
      if ( iter == Masses::masses_.end() ) {

        throw std::out_of_range( "Particle not found in the AME2020 masses" );
      }
      return iter->second;
    }
  };

} // ripl3 namespace
} // external namespace
} // dryad namespace
} // njoy namespace

#endif
