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
     *  @brief Return the number of particles
     */
    std::size_t numberParticles() const {

      return this->particles_.size();
    }

    /**
     *  @brief Return whether or not a given particle is present
     *
     *  @param[in] id   the particle identifier
     */
    bool hasParticle( const id::ParticleID& id ) const {

      auto iter = this->particles_.find( id );
      return iter != this->particles_.end();
    }

    /**
     *  @brief Return the requested particle
     *
     *  @param[in] id   the particle identifier
     */
    const Particle& particle( const id::ParticleID& id ) const {

      auto iter = this->particles_.find( id );
      if ( iter != this->particles_.end() ) {

        return iter->second;
      }
      else {

        Log::error( "The requested particle \'{}\' could not be found", id.symbol() );
        throw std::exception();
      }
    }

    /**
     *  @brief Return the requested particle
     *
     *  @param[in] id   the particle identifier
     */
    Particle& particle( const id::ParticleID& id ) {

      return const_cast< Particle& >( const_cast< const ParticleDatabase& >( *this ).particle( id ) );
    }

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
