#ifndef NJOY_DRYAD_RESONANCES_PARTICLEPAIR
#define NJOY_DRYAD_RESONANCES_PARTICLEPAIR

// system includes
#include <tuple>

// other includes
#include "njoy/dryad/Particle.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Particle pair information for resonance reconstruction
   *
   *  A ParticlePair represents the two particles involved in a entrance or exit
   *  reaction channel (we assume that the reaction is a two-body reaction). The
   *  pair consists of a "light" incident or outgoing particle (e.g. a neutron,
   *  photon, alpha, etc.) and a "heavy" target or residual nucleus (e.g. H1,
   *  He4, U235, etc.).
   *
   *  The ParticlePair class gives us access to information related to the
   *  pair of particles such as the mass ratio and the reduced mass.
   */
  class ParticlePair {

    /* fields */

    Particle light_particle_;
    Particle heavy_particle_;

    double reduced_mass_;
    double mass_ratio_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ParticlePair() = default;

    ParticlePair( const ParticlePair& ) = default;
    ParticlePair( ParticlePair&& ) = default;

    ParticlePair& operator=( const ParticlePair& ) = default;
    ParticlePair& operator=( ParticlePair&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] lightParticle   the light particle
     *  @param[in] heavyParticle   the heavy particle
     */
    ParticlePair( Particle lightParticle, Particle heavyParticle ) :
        light_particle_( std::move( lightParticle ) ),
        heavy_particle_( std::move( heavyParticle ) ) {

      const auto ma = this->lightParticle().mass().has_value()
                      ? this->lightParticle().mass().value()
                      : 0.;
      const auto mb = this->heavyParticle().mass().has_value()
                      ? this->heavyParticle().mass().value()
                      : 0.;
      this->reduced_mass_ = ma * mb / ( ma + mb );
      this->mass_ratio_ = mb / ( ma + mb );
    }

    /**
     *  @brief Return the light particle in the particle pair
     */
    const Particle& lightParticle() const { return this->light_particle_; }

    /**
     *  @brief Return the heavy particle in the particle pair
     */
    const Particle& heavyParticle() const { return this->heavy_particle_; }

    /**
     *  @brief Return the reduced mass of the particle pair (in atomic mass units)
     *
     *  The reduced mass mu of the two particles is defined as follows:
     *     mu = ma * mb / ( ma + mb )
     *  in which ma and mb are the atomic mass values of the particles in the
     *  particle pair.
     */
    double reducedMass() const { return this->reduced_mass_; }

    /**
     *  @brief Return the mass ratio of the particle pair (dimensionless)
     *
     *  The mass ratio of the two particles is defined as follows:
     *     ratio = mb / ( ma + mb )
     *  in which ma and mb are the atomic mass values of the particles
     *  in the particle pair.
     */
    double massRatio() const { return this->mass_ratio_; }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const ParticlePair& left, const ParticlePair& right ) {

      return std::tie( left.lightParticle(), left.heavyParticle() ) ==
             std::tie( right.lightParticle(), right.heavyParticle() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const ParticlePair& left, const ParticlePair& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
