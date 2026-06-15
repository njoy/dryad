#ifndef NJOY_DRYAD_EXTERNAL_RIPL3_LEVELENTRY
#define NJOY_DRYAD_EXTERNAL_RIPL3_LEVELENTRY

// system includes
#include <optional>
#include <tuple>

// other includes
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace external {
namespace ripl3 {

  /**
   *  @class
   *  @brief Level entry information from RIPL-3
   *
   *  The LevelEntry class contains information for a nuclear level entry:
   *    - a particle identifier
   *    - an optional energy value
   *    - an optional spin value
   *    - an optional parity (which is either + or -)
   *    - an optional half-life value
   *
   *  The data is stored in the following units:
   *    - energy values are in eV
   *    - half-life values are in seconds
   */
  class LevelEntry {

    /* fields */

    id::ParticleID identifier_;
    std::optional< double > energy_;
    std::optional< double > spin_;
    std::optional< short > parity_;
    std::optional< double > half_life_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    LevelEntry() = default;

    LevelEntry( const LevelEntry& ) = default;
    LevelEntry( LevelEntry&& ) = default;

    LevelEntry& operator=( const LevelEntry& ) = default;
    LevelEntry& operator=( LevelEntry&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] id          the particle identifier
     *  @param[in] energy      the level energy (default is none)
     *  @param[in] spin        the level spin (default is none)
     *  @param[in] parity      the parity (default is none)
     *  @param[in] halfLife    the half-life (default is none)
     */
    LevelEntry( id::ParticleID id,
                std::optional< double > energy = std::nullopt,
                std::optional< double > spin = std::nullopt,
                std::optional< short > parity = std::nullopt,
                std::optional< double > halfLife = std::nullopt ) :
      identifier_( std::move( id ) ),
      energy_( std::move( energy ) ),
      spin_( std::move( spin ) ),
      parity_( std::move( parity ) ),
      half_life_( std::move( halfLife ) ) {}

    /* methods */

    /**
     *  @brief Return the particle identifier
     */
    const id::ParticleID& identifier() const {

      return this->identifier_;
    }

    /**
     *  @brief Set the particle identifier
     *
     *  @param id  the particle identifier
     */
    void identifier( id::ParticleID id ) {

      this->identifier_ = std::move( id );
    }

    /**
     *  @brief Return the level energy
     */
    const std::optional< double >& energy() const {

      return this->energy_;
    }

    /**
     *  @brief Set the level energy
     *
     *  @param energy  the level energy
     */
    void energy( std::optional< double > energy ) {

      this->energy_ = std::move( energy );
    }

    /**
     *  @brief Return the spin of the level
     */
    const std::optional< double >& spin() const {

      return this->spin_;
    }

    /**
     *  @brief Set the spin of the level
     *
     *  @param spin  the level spin
     */
    void spin( std::optional< double > spin ) {

      this->spin_ = std::move( spin );
    }

    /**
     *  @brief Return the level spin parity
     */
    const std::optional< short >& parity() const {

      return this->parity_;
    }

    /**
     *  @brief Set the level spin parity
     *
     *  @param parity  the level parity
     */
    void parity( std::optional< short > parity ) {

      this->parity_ = std::move( parity );
    }

    /**
     *  @brief Return the half-life of the level
     */
    const std::optional< double >& halfLife() const {

      return this->half_life_;
    }

    /**
     *  @brief Set the half-life of the level
     *
     *  @param halfLife  the half-life
     */
    void halfLife( std::optional< double > halfLife ) {

      this->half_life_ = std::move( halfLife );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const LevelEntry& left, const LevelEntry& right ) {

      return std::tie( left.identifier(), left.energy(), left.spin(),
                       left.parity(), left.halfLife() ) ==
             std::tie( right.identifier(), right.energy(), right.spin(),
                       right.parity(), right.halfLife() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const LevelEntry& left, const LevelEntry& right ) {

      return ! ( left == right );
    }
  };

} // ripl3 namespace
} // external namespace
} // dryad namespace
} // njoy namespace

#endif
