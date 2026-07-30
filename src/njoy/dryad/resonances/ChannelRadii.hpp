#ifndef NJOY_DRYAD_RESONANCES_CHANNELRADII
#define NJOY_DRYAD_RESONANCES_CHANNELRADII

// system includes
#include <optional>
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/TabulatedRadius.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief Channel radii used in wave function calculations
   *
   *  The penetrability P, shift factor S and phase shift phi require knowledge
   *  of the channel radius in their calculation. The ChannelRadii class provides
   *  these radii for each one of these.
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class ChannelRadii {

    /* alias */

    using Radius = std::variant< double, TabulatedRadius >;

    /* fields */

    Radius penetrability_;
    std::optional< Radius > shift_factor_;
    std::optional< Radius > phase_shift_;

    /* auxiliary functions */

    static double radius( double energy, const Radius& radius ) {

      return std::visit(
               tools::overload{ [] ( double radius )
                                   { return radius; },
                                [&] ( const TabulatedRadius& table )
                                    { return table( energy ); } },
               radius );
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ChannelRadii() = default;

    ChannelRadii( const ChannelRadii& ) = default;
    ChannelRadii( ChannelRadii&& ) = default;

    ChannelRadii& operator=( const ChannelRadii& ) = default;
    ChannelRadii& operator=( ChannelRadii&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] radius   the channel radius to be used for P, S and phi
     */
    ChannelRadii( Radius radius ) :
        penetrability_( std::move( radius ) ),
        shift_factor_( std::nullopt ),
        phase_shift_( std::nullopt ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] trueRadius        the channel radius to be used for P and S
     *  @param[in] effectiveRadius   the channel radius to be used for phi
     */
    ChannelRadii( Radius trueRadius,
                  Radius effectiveRadius ) :
        penetrability_( std::move( trueRadius ) ),
        shift_factor_( std::nullopt ),
        phase_shift_( std::move( effectiveRadius ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] penetrabilityRadius   the channel radius to be used for P
     *  @param[in] shiftFactorRadius     the channel radius to be used for S
     *  @param[in] phaseShiftRadius      the channel radius to be used for phi
     */
    ChannelRadii( Radius penetrabilityRadius,
                  Radius shiftFactorRadius,
                  Radius phaseShiftRadius ) :
        penetrability_( std::move( penetrabilityRadius ) ),
        shift_factor_( std::move( shiftFactorRadius ) ),
        phase_shift_( std::move( phaseShiftRadius ) ) {}

    /**
     *  @brief Return whether or not a shift factor radius is defined
     */
    bool hasShiftFactorRadius() const {

      return this->shift_factor_.has_value();
    }

    /**
     *  @brief Return whether or not a phase shift radius is defined
     */
    bool hasPhaseShiftRadius() const {

      return this->phase_shift_.has_value();
    }

    /**
     *  @brief Return the penetrability radius
     */
    const Radius& penetrabilityRadius() const {

      return this->penetrability_;
    }

    /**
     *  @brief Return the shift factor radius
     */
    const std::optional< Radius >& shiftFactorRadius() const {

      return this->shift_factor_;
    }

    /**
     *  @brief Return the phase shift radius
     */
    const std::optional< Radius >& phaseShiftRadius() const {

      return this->phase_shift_;
    }

    /**
     *  @brief Set the penetrability radius
     *
     *  @param[in] radius  the radius
     */
    void penetrabilityRadius( Radius radius ) {

      this->penetrability_ = std::move( radius );
    }

    /**
     *  @brief Set the shift factor radius
     *
     *  @param[in] radius  the radius
     */
    void shiftFactorRadius( std::optional< Radius > radius ) {

      this->shift_factor_ = std::move( radius );
    }

    /**
     *  @brief Set the phase shift radius
     *
     *  @param[in] radius  the radius
     */
    void phaseShiftRadius( std::optional< Radius > radius ) {

      this->phase_shift_ = std::move( radius );
    }

    /**
     *  @brief Return the channel radius for the penetrability P
     *
     *  @param[in] energy   the energy for which the radius must be given
     */
    double calculatePenetrabilityRadius( double energy ) const {

      return radius( energy, this->penetrabilityRadius() );
    }

    /**
     *  @brief Return the channel radius for the shift factor S
     *
     *  @param[in] energy   the energy for which the radius must be given
     */
    double calculateShiftFactorRadius( double energy ) const {

      return this->hasShiftFactorRadius()
               ? radius( energy, this->shiftFactorRadius().value() )
               : this->calculatePenetrabilityRadius( energy );
    }

    /**
     *  @brief Return the channel radius for the phase shift phi
     *
     *  @param[in] energy   the energy for which the radius must be given
     */
    double calculatePhaseShiftRadius( double energy ) const {

      return this->hasPhaseShiftRadius()
               ? radius( energy, this->phaseShiftRadius().value() )
               : this->calculatePenetrabilityRadius( energy );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const ChannelRadii& left, const ChannelRadii& right ) {

      return std::tie( left.penetrabilityRadius(), left.shiftFactorRadius(), left.phaseShiftRadius() ) ==
             std::tie( right.penetrabilityRadius(), right.shiftFactorRadius(), right.phaseShiftRadius() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const ChannelRadii& left, const ChannelRadii& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
