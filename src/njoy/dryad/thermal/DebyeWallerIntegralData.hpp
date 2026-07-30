#ifndef NJOY_DRYAD_THERMAL_DEBYEWALLERINTEGRALDATA
#define NJOY_DRYAD_THERMAL_DEBYEWALLERINTEGRALDATA

// system includes
#include <algorithm>
#include <vector>
#include <tuple>

// other includes
#include "tools/Log.hpp"
#include "njoy/utility/find_closest.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief A Debye-Waller integral data
   *
   *  Temperature values are assumed to be in K and the integral values are
   *  assumed to be in 1/eV.
   *
   *  There currently is not possibility for interpolation on these values.
   */
  class DebyeWallerIntegralData {

    /* fields */

    std::vector< double > temperatures_;
    std::vector< double > integrals_;

    /* auxiliary functions */

    /**
     *  @brief Return an iterator for a given temperature (within a given tolerance)
     *
     *  @param[in] temperature   the temperature
     *  @param[in] tolerance     the tolerance
     */
    auto iterator( double temperature, double tolerance ) const {

      auto iter = utility::find_closest( this->temperatures().begin(),
                                         this->temperatures().end(),
                                         temperature, tolerance );
      if ( iter != this->temperatures().end() ) {

        return std::next( this->values().begin(),
                          std::distance( this->temperatures().begin(), iter ) );
      }

      return this->values().end();
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    DebyeWallerIntegralData() = default;

    DebyeWallerIntegralData( const DebyeWallerIntegralData& ) = default;
    DebyeWallerIntegralData( DebyeWallerIntegralData&& ) = default;

    DebyeWallerIntegralData& operator=( const DebyeWallerIntegralData& ) = default;
    DebyeWallerIntegralData& operator=( DebyeWallerIntegralData&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] temperatures   the temperatures values
     *  @param[in] values         the integral values
     */
    DebyeWallerIntegralData( std::vector< double > temperatures,
                             std::vector< double > values ) :
      temperatures_( std::move( temperatures ) ),
      integrals_( std::move( values ) ) {}

    /* methods */

    /**
     *  @brief Return the temperature values
     */
    const std::vector< double >& temperatures() const {

      return this->temperatures_;
    }

    /**
     *  @brief Return the temperature values
     */
    std::vector< double >& temperatures() {

      return this->temperatures_;
    }

    /**
     *  @brief Return the integral values
     */
    const std::vector< double >& values() const {

      return this->integrals_;
    }

    /**
     *  @brief Return the integral values
     */
    std::vector< double >& values() {

      return this->integrals_;
    }

    /**
     *  @brief Return whether or not there is a Debye Waller integral value for a given
     *         moderator temperature
     *
     *  @param[in] temperature   the moderator temperature
     */
    bool hasValue( double temperature ) const {

      // get the closest temperature within 0.001 K
      auto iter = this->iterator( temperature, 0.001 );
      return iter != this->values().end();
    }

    /**
     *  @brief Return the Debye Waller integral value for a given moderator temperature
     *
     *  @param[in] temperature   the moderator temperature
     */
    double value( double temperature ) const {

      // get the closest temperature within 0.001 K
      auto iter = this->iterator( temperature, 0.001 );
      if ( iter != this->values().end() ) {

        return *iter;
      }
      else {

        Log::error( "No Debye Waller integral value with moderator temperature equal to {} K "
                    "could not be found", temperature );
        throw std::exception();
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const DebyeWallerIntegralData& right ) const {

      return std::tie( this->temperatures(), this->values() ) ==
             std::tie( right.temperatures(), right.values() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const DebyeWallerIntegralData& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
