#ifndef NJOY_DRYAD_PARTICLEDATABASE
#define NJOY_DRYAD_PARTICLEDATABASE

// system includes
#include <unordered_map>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/Particle.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The particle database
   */
  class ParticleDatabase {

    /* fields */
    std::unordered_map< id::ParticleID, Particle > particles_;

    /* auxiliary functions */

    #include "njoy/dryad/ParticleDatabase/src/generateMap.hpp"

  public:

    /* constructor */

    #include "njoy/dryad/ParticleDatabase/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ParticleDatabase& right ) const {

      return this->particles_ == right.particles_;
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ParticleDatabase& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
