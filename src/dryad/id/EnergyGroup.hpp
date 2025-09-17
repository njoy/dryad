#ifndef NJOY_DRYAD_ID_ENERGYGROUP
#define NJOY_DRYAD_ID_ENERGYGROUP

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace dryad {
namespace id {

  /**
   *  @class
   *  @brief An energy group defined by two energy values
   */
  class EnergyGroup : protected std::pair< double, double > {

    /* type alias */
    using Parent = std::pair< double, double >;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    EnergyGroup() = default;

    EnergyGroup( const EnergyGroup& ) = default;
    EnergyGroup( EnergyGroup&& ) = default;

    EnergyGroup& operator=( const EnergyGroup& ) = default;
    EnergyGroup& operator=( EnergyGroup&& ) = default;

    /**
     *  @brief Constructor for an energy group
     *
     *  Note: we do not check if lower < upper.
     *
     *  @param[in] lower   the lower energy value of the energy group
     *  @param[in] upper   the upper energy value of the energy group
     */
    EnergyGroup( double lower, double upper ) :
      std::pair< double, double >( lower, upper ) {}

    /* methods */

    /**
     *  @brief Return the lower energy value
     */
    double lowerEnergy() const {

      return this->first;
    }

    /**
     *  @brief Return the upper energy value
     */
    double upperEnergy() const {

      return this->second;
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the group on the left
     *  @param[in] right   the group on the right
     */
    friend auto operator==( const EnergyGroup& left, const EnergyGroup& right ) {

      return static_cast< const Parent& >( left ) == static_cast< const Parent& >( right );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator!=( const EnergyGroup& left, const EnergyGroup& right ) {

      return ! ( left == right );
    }

    /**
     *  @brief Less than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<( const EnergyGroup& left, const EnergyGroup& right ) {

      return static_cast< const Parent& >( left ) < static_cast< const Parent& >( right );
    }

    /**
     *  @brief Greater than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>( const EnergyGroup& left, const EnergyGroup& right ) {

      return right < left;
    }

    /**
     *  @brief Less than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<=( const EnergyGroup& left, const EnergyGroup& right ) {

      return ! ( right < left );
    }

    /**
     *  @brief Greater than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>=( const EnergyGroup& left, const EnergyGroup& right ) {

      return ! ( left < right );
    }
  };

} // id namespace
} // dryad namespace
} // njoy namespace

namespace std {

  // std::hash override for the ReactionType class
  template <>
  struct hash< njoy::dryad::id::EnergyGroup > {

    size_t operator()( const njoy::dryad::id::EnergyGroup& key ) const {

      return std::hash< double >()( key.lowerEnergy() ) ^
             std::hash< double >()( key.upperEnergy() );
    }
  };

} // namespace std

#endif
