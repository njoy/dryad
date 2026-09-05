#ifndef NJOY_DRYAD_RESONANCES_RESONANCEPARAMETERS
#define NJOY_DRYAD_RESONANCES_RESONANCEPARAMETERS

// system includes
#include <variant>
#include <vector>
#include <optional>
#include <tuple>

// other includes
#include "njoy/dryad/resonances/CompoundSystem.hpp"
#include "njoy/dryad/resonances/UnresolvedCompoundSystem.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief The resonance parameter data
   *
   *  Note: this is currently a placeholder
   */
  class ResonanceParameters {

    /* fields */

    std::vector< CompoundSystem > resolved_;
    std::optional< UnresolvedCompoundSystem > unresolved_;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ResonanceParameters() = default;

    ResonanceParameters( const ResonanceParameters& ) = default;
    ResonanceParameters( ResonanceParameters&& ) = default;

    ResonanceParameters& operator=( const ResonanceParameters& ) = default;
    ResonanceParameters& operator=( ResonanceParameters&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] resolved     the resolved resonance compound systems
     *  @param[in] unresolved   the unresolved resonance compound systems
     */
    ResonanceParameters( std::vector< CompoundSystem > resolved,
                         std::optional< UnresolvedCompoundSystem > unresolved=std::nullopt ) :
        resolved_( std::move( resolved ) ),
        unresolved_( std::move( unresolved ) ) {}

    /* methods */

    /**
     *  @brief Return the compound systems that make up the resolved resonance data
     */
    const std::vector< CompoundSystem >& resolved() const {

      return this->resolved_;
    }

    /**
     *  @brief Return the compound systems that make up the resolved resonance data
     */
    std::vector< CompoundSystem >& resolved() {

      return this->resolved_;
    }

    /**
     *  @brief Set the compound systems that make up resolved resonance data
     *
     *  @param[in] resolved   the resolved resonance compound systems
     */
    void resolved( std::vector< CompoundSystem > resolved ) {

      this->resolved_ = std::move( resolved );
    }

    /**
     *  @brief Return the compound systems that make up the unresolved resonance data
     */
    const std::optional< UnresolvedCompoundSystem >& unresolved() const {

      return this->unresolved_;
    }

    /**
     *  @brief Return the compound systems that make up the unresolved resonance data
     */
    std::optional< UnresolvedCompoundSystem >& unresolved() {

      return this->unresolved_;
    }

    /**
     *  @brief Set the compound systems that make up unresolved resonance data
     *
     *  @param[in] unresolved   the unresolved resonance compound systems
     */
    void unresolved(  UnresolvedCompoundSystem unresolved ) {

      this->unresolved_ = std::move( unresolved );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const ResonanceParameters& left, const ResonanceParameters& right ) {

      return  std::tie( left.resolved(), left.unresolved() ) ==
              std::tie( right.resolved(), right.unresolved() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const ResonanceParameters& left, const ResonanceParameters& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
