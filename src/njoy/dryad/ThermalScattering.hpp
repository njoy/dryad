#ifndef NJOY_DRYAD_THERMALSCATTERING
#define NJOY_DRYAD_THERMALSCATTERING

// system includes
#include <optional>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Documentation.hpp"
#include "njoy/dryad/thermal/IncoherentElasticScattering.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Thermal scattering data
   */
  class ThermalScattering {

    /* fields */
    Documentation documentation_;

    std::optional< thermal::IncoherentElasticScattering > incoherent_elastic_;

    /* auxiliary functions */

  public:

    /* constructor */

    #include "njoy/dryad/ThermalScattering/src/ctor.hpp"

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
     *  @brief Return whether or not there is coherent elastic scattering
     */
    bool hasCoherentElasticScattering() const {

      return false;
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
     *  @brief Return whether or not there is inelastic scattering
     */
    bool hasInelasticScattering() const {

      return false;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ThermalScattering& right ) const {

      return this->incoherentElasticScattering() == right.incoherentElasticScattering();
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
