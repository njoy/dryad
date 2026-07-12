#ifndef NJOY_DRYAD_THERMALSCATTERING
#define NJOY_DRYAD_THERMALSCATTERING

// system includes
#include <optional>
#include <tuple>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Documentation.hpp"
#include "njoy/dryad/thermal/CoherentElasticScattering.hpp"
#include "njoy/dryad/thermal/IncoherentElasticScattering.hpp"
#include "njoy/dryad/thermal/IncoherentInelasticScattering.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Thermal scattering data
   */
  class ThermalScattering {

    /* fields */

    Documentation documentation_;

    std::optional< thermal::CoherentElasticScattering > coherent_elastic_;
    std::optional< thermal::IncoherentElasticScattering > incoherent_elastic_;
    std::optional< thermal::IncoherentInelasticScattering > incoherent_inelastic_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ThermalScattering() = default;

    ThermalScattering( const ThermalScattering& ) = default;
    ThermalScattering( ThermalScattering&& ) = default;

    ThermalScattering& operator=( const ThermalScattering& ) = default;
    ThermalScattering& operator=( ThermalScattering&& ) = default;

    /**
     *  @brief Constructor with documentation
     *
     *  @param[in] documentation         the documentation
     *  @param[in] coherentElastic       the coherent elastic scattering data (default: none)
     *  @param[in] incoherentElastic     the incoherent elastic scattering data (default: none)
     *  @param[in] incoherentInelastic   the incoherent inelastic scattering data (default: none)
     */
    ThermalScattering( Documentation documentation,
                       std::optional< thermal::CoherentElasticScattering > coherentElastic = std::nullopt,
                       std::optional< thermal::IncoherentElasticScattering > incoherentElastic = std::nullopt,
                       std::optional< thermal::IncoherentInelasticScattering > incoherentInelastic = std::nullopt ) :
        documentation_( std::move( documentation ) ),
        coherent_elastic_( std::move( coherentElastic ) ),
        incoherent_elastic_( std::move( incoherentElastic ) ),
        incoherent_inelastic_( std::move( incoherentInelastic ) ) {}

    /**
     *  @brief Constructor without documentation
     *
     *  @param[in] coherentElastic       the coherent elastic scattering data (default: none)
     *  @param[in] incoherentElastic     the incoherent elastic scattering data (default: none)
     *  @param[in] incoherentInelastic   the incoherent inelastic scattering data (default: none)
     */
    ThermalScattering( std::optional< thermal::CoherentElasticScattering > coherentElastic = std::nullopt,
                       std::optional< thermal::IncoherentElasticScattering > incoherentElastic = std::nullopt,
                       std::optional< thermal::IncoherentInelasticScattering > incoherentInelastic = std::nullopt ) :
        documentation_(),
        coherent_elastic_( std::move( coherentElastic ) ),
        incoherent_elastic_( std::move( incoherentElastic ) ),
        incoherent_inelastic_( std::move( incoherentInelastic ) ) {}

    /* methods */

    /**
     *  @brief Return the documentation
     */
    const Documentation& documentation() const {

      return this->documentation_;
    }

    /**
     *  @brief Return the documentation
     */
    Documentation& documentation() {

      return this->documentation_;
    }

    /**
     *  @brief Set the documentation
     *
     *  @param[in] documentation   the documentation
     */
    void documentation( Documentation documentation ) {

      this->documentation_ = std::move( documentation );
    }

    /**
     *  @brief Return the coherent elastic data
     */
    const std::optional< thermal::CoherentElasticScattering >&
    coherentElasticScattering() const {

      return this->coherent_elastic_;
    }

    /**
     *  @brief Return the coherent elastic data
     */
    std::optional< thermal::CoherentElasticScattering >&
    coherentElasticScattering() {

      return this->coherent_elastic_;
    }

    /**
     *  @brief Set the coherent elastic data
     *
     *  @param[in] coherent   the coherent elastic data
     */
    void coherentElasticScattering(
           std::optional< thermal::CoherentElasticScattering > coherent ) {

      this->coherent_elastic_ = std::move( coherent );
    }

    /**
     *  @brief Return the incoherent elastic data
     */
    const std::optional< thermal::IncoherentElasticScattering >&
    incoherentElasticScattering() const {

      return this->incoherent_elastic_;
    }

    /**
     *  @brief Return the incoherent elastic data
     */
    std::optional< thermal::IncoherentElasticScattering >&
    incoherentElasticScattering() {

      return this->incoherent_elastic_;
    }

    /**
     *  @brief Set the incoherent elastic data
     *
     *  @param[in] element   the element identifier
     */
    void incoherentElasticScattering(
           std::optional< thermal::IncoherentElasticScattering > incoherent ) {

      this->incoherent_elastic_ = std::move( incoherent );
    }

    /**
     *  @brief Return the incoherent inelastic data
     */
    const std::optional< thermal::IncoherentInelasticScattering >&
    incoherentInelasticScattering() const {

      return this->incoherent_inelastic_;
    }

    /**
     *  @brief Return the incoherent inelastic data
     */
    std::optional< thermal::IncoherentInelasticScattering >&
    incoherentInelasticScattering() {

      return this->incoherent_inelastic_;
    }

    /**
     *  @brief Set the incoherent inelastic data
     *
     *  @param[in] inelastic   the incoherent inelastic data
     */
    void incoherentInelasticScattering(
           std::optional< thermal::IncoherentInelasticScattering > inelastic ) {

      this->incoherent_inelastic_ = std::move( inelastic );
    }

    /**
     *  @brief Return whether or not there is coherent elastic scattering
     */
    bool hasCoherentElasticScattering() const {

      return this->coherentElasticScattering().has_value();
    }

    /**
     *  @brief Return whether or not there is incoherent elastic scattering
     */
    bool hasIncoherentElasticScattering() const {

      return this->incoherentElasticScattering().has_value();
    }

    /**
     *  @brief Return whether or not there is elastic scattering (coherent and/or incoherent)
     */
    bool hasElasticScattering() const {

      return this->hasCoherentElasticScattering() || this->hasIncoherentElasticScattering();
    }

    /**
     *  @brief Return whether or not there is incoherent elastic scattering
     */
    bool hasIncoherentInelasticScattering() const {

      return this->incoherentInelasticScattering().has_value();
    }

    /**
     *  @brief Return whether or not there is inelastic scattering
     */
    bool hasInelasticScattering() const {

      return this->hasIncoherentInelasticScattering();
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ThermalScattering& right ) const {

      return std::tie( this->coherentElasticScattering(), this->incoherentElasticScattering(),
                       this->incoherentInelasticScattering() ) ==
             std::tie( right.coherentElasticScattering(), right.incoherentElasticScattering(),
                       right.incoherentInelasticScattering() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ThermalScattering& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
