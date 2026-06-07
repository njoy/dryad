#ifndef NJOY_DRYAD_PARTICLEDATABASE
#define NJOY_DRYAD_PARTICLEDATABASE

// system includes
#include <algorithm>
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
    std::vector< Particle > particles_;

    /* auxiliary functions */

    #include "njoy/dryad/ParticleDatabase/src/iterator.hpp"
    #include "njoy/dryad/ParticleDatabase/src/sort.hpp"

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ParticleDatabase() = default;

    ParticleDatabase( const ParticleDatabase& ) = default;
    ParticleDatabase( ParticleDatabase&& ) = default;

    ParticleDatabase& operator=( const ParticleDatabase& ) = default;
    ParticleDatabase& operator=( ParticleDatabase&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] particles   the particle information
     */
    ParticleDatabase( std::vector< Particle > particles ) :
      particles_( std::move( particles ) ) {

      this->sort();
    }

    /* methods */

    /**
     *  @brief Return the number of particles
     */
    std::size_t numberParticles() const {

      return this->particles().size();
    }

    /**
     *  @brief Return the available particles
     */
    const std::vector< Particle >& particles() const {

      return this->particles_;
    }

    /**
     *  @brief Return the available particles
     */
    std::vector< Particle >& particles() {

      return this->particles_;
    }

    /**
     *  @brief Set the available particles
     *
     *  @param[in] particles   the available particles
     */
    void particles( std::vector< Particle > particles ) {

      this->particles_ = std::move( particles );
      this->sort();
    }

    /**
     *  @brief Return whether or not a given particle is present
     *
     *  @param[in] id   the particle identifier
     */
    bool hasParticle( const id::ParticleID& id ) const {

      auto iter = this->iterator( id );
      return iter != this->particles().end() && iter->identifier() == id;
    }

    /**
     *  @brief Return the requested particle
     *
     *  @param[in] id   the particle identifier
     */
    const Particle& particle( const id::ParticleID& id ) const {

      auto iter = this->iterator( id );
      if ( iter != this->particles().end() && iter->identifier() == id ) {

        return *iter;
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

      return this->particles() == right.particles();
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
