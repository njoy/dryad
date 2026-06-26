#ifndef NJOY_DRYAD_THERMAL_INCOHERENTELASTICSCATTERING
#define NJOY_DRYAD_THERMAL_INCOHERENTELASTICSCATTERING

// system includes
#include <optional>
#include <variant>

// other includes
#include "njoy/dryad/thermal/DebyeWallerIntegralData.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Incoherent elastic thermal scattering data
   *
   *  @todo add a function to retrieve the cross section (interpolation type is 1/E)
   *        and the angular distribution or the discrete cosines
   */
  class IncoherentElasticScattering {

    /* fields */

    double bound_xs_;
    DebyeWallerIntegralData debye_waller_;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    IncoherentElasticScattering() = default;

    IncoherentElasticScattering( const IncoherentElasticScattering& ) = default;
    IncoherentElasticScattering( IncoherentElasticScattering&& ) = default;

    IncoherentElasticScattering& operator=( const IncoherentElasticScattering& ) = default;
    IncoherentElasticScattering& operator=( IncoherentElasticScattering&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param xs                    the bound atom cross section
     *  @param debyeWallerIntegral   the Debye-Waller integral data
     */
    IncoherentElasticScattering( double xs,
                                 DebyeWallerIntegralData debyeWallerIntegral ) :
      bound_xs_( xs ),
      debye_waller_( std::move( debyeWallerIntegral ) ) {}

    /* methods */

    /**
     *  @brief Return the number of moderator temperatures for which data is available
     */
    std::size_t numberModeratorTemperatures() const {

      return this->moderatorTemperatures().size();
    }

    /**
     *  @brief Return the moderator temperature values
     */
    const std::vector< double >& moderatorTemperatures() const {

      return this->debyeWallerIntegral().temperatures();
    }

    /**
     *  @brief Return the bound atom cross section value
     */
    double boundCrossSection() const {

      return this->bound_xs_;
    }

    /**
     *  @brief Set the bound atom cross section value
     *
     *  @param xs   the reaction product identifier
     */
    void boundCrossSection( double xs ) {

      this->bound_xs_ = xs;
    }

    /**
     *  @brief Return the Debye-Waller integral data
     */
    const DebyeWallerIntegralData& debyeWallerIntegral() const {

      return this->debye_waller_;
    }

    /**
     *  @brief Set the Debye-Waller integral data
     *
     *  @param debyeWaller   the Debye-Waller integral data
     */
    void debyeWallerIntegral( DebyeWallerIntegralData debyeWaller ) {

      this->debye_waller_ = std::move( debyeWaller );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const IncoherentElasticScattering& right ) const {

      return std::tie( this->bound_xs_, this->debyeWallerIntegral() ) ==
             std::tie( right.bound_xs_, right.debyeWallerIntegral() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const IncoherentElasticScattering& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
