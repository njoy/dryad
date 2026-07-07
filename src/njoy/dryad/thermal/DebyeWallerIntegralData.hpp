#ifndef NJOY_DRYAD_THERMAL_DEBYEWALLERINTEGRALDATA
#define NJOY_DRYAD_THERMAL_DEBYEWALLERINTEGRALDATA

// system includes
#include <vector>
#include <tuple>

// other includes

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief A Debye-Waller integral data
   *
   *  Temperature values are assumed to be in K and the integral values are
   *  assumed to be in 1/eV.
   */
  class DebyeWallerIntegralData {

    /* fields */

    std::vector< double > temperatures_;
    std::vector< double > integrals_;

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
