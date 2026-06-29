#ifndef NJOY_DRYAD_THERMAL_INCOHERENTELASTICSCATTERING
#define NJOY_DRYAD_THERMAL_INCOHERENTELASTICSCATTERING

// system includes

// other includes
#include "scion/math/compare.hpp"
#include "njoy/utility/find_closest.hpp"
#include "njoy/dryad/thermal/DebyeWallerIntegralData.hpp"
#include "njoy/dryad/thermal/IncoherentElasticScatteringCrossSection.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief Incoherent elastic thermal scattering data
   *
   *  @todo add a function to retrieve the cross section
   *        and the angular distribution or the discrete cosines
   */
  class IncoherentElasticScattering {

    /* fields */

    double lower_;
    double upper_;
    double bound_xs_;
    DebyeWallerIntegralData debye_waller_;

    //! @todo we may need to add natom (number of principle scatterers) for older evaluations

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
     *  @param[in] lower                 the lower energy limit
     *  @param[in] upper                 the upper energy limit
     *  @param[in] xs                    the bound atom cross section
     *  @param[in] debyeWallerIntegral   the Debye-Waller integral data
     */
    IncoherentElasticScattering( double lower,
                                 double upper,
                                 double xs,
                                 DebyeWallerIntegralData debyeWallerIntegral ) :
      lower_( lower ),
      upper_( upper ),
      bound_xs_( xs ),
      debye_waller_( std::move( debyeWallerIntegral ) ) {}

    /* methods */

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return this->lower_;
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return this->upper_;
    }

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
     *  @param[in] xs   the reaction product identifier
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
     *  @param[in] debyeWaller   the Debye-Waller integral data
     */
    void debyeWallerIntegral( DebyeWallerIntegralData debyeWaller ) {

      this->debye_waller_ = std::move( debyeWaller );
    }

    /**
     *  @brief Return the incoherent elastic scattering cross section
     *
     *  @param[in] temperature   the moderator temeprature for which the
     *                           cross section is requested
     */
    IncoherentElasticScatteringCrossSection
    crossSection( double temperature ) {

      // find the closest temperature, within 0.001 K
      auto iter = utility::find_closest( this->moderatorTemperatures().begin(),
                                         this->moderatorTemperatures().end(),
                                         temperature, 0.001 );
      if ( iter == this->moderatorTemperatures().end() ) {

        throw std::runtime_error( "The requested temperature "
                                  + std::to_string( temperature )
                                  + " K is not present" );
      }

      std::size_t index = std::distance( this->moderatorTemperatures().begin(), iter );
      return IncoherentElasticScatteringCrossSection(
                 this->lowerEnergyLimit(),
                 this->upperEnergyLimit(),
                 this->boundCrossSection(),
                 this->debyeWallerIntegral().values()[index] );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const IncoherentElasticScattering& right ) const {

      return std::tie( this->lower_, this->upper_, this->bound_xs_, this->debyeWallerIntegral() ) ==
             std::tie( right.lower_, right.upper_, right.bound_xs_, right.debyeWallerIntegral() );
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
