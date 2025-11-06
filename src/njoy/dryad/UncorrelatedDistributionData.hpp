#ifndef NJOY_DRYAD_UNCORRELATEDDISTRIBUTIONDATA
#define NJOY_DRYAD_UNCORRELATEDDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "dryad/DistributionDataType.hpp"
#include "dryad/ReferenceFrame.hpp"
#include "dryad/IsotropicAngularDistributions.hpp"
#include "dryad/LegendreAngularDistributions.hpp"
#include "dryad/TabulatedAngularDistributions.hpp"
#include "dryad/MultiEnergyDistributions.hpp"
#include "dryad/TabulatedEnergyDistributions.hpp"
#include "tools/overload.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Uncorrelated energy and angle distribution data for a reaction product
   *
   *  In this representation, there is no correlation given between the outgoing
   *  angle and energy of the reaction product. As a result, the angular and energy
   *  distributions of the reaction product depend only on the incident energy of the
   *  projectile.
   *
   *  For incident neutron data, this is used for reactions that have both MF4 and MF5
   *  data. For reaction products given in MF6, this corresponds to LAW = 1 (continuum
   *  energy-angle distributions) in which the angular dependence is fully isotropic.
   *  This is also the representation for Brehmstrahlung and excitation data in MF26
   *  for electro-atomic interactions.
   */
  class UncorrelatedDistributionData {

  public:

    /* type aliases */
    using AngularDistributions = std::variant< IsotropicAngularDistributions,
                                               LegendreAngularDistributions,
                                               TabulatedAngularDistributions >;
    using EnergyDistributions = std::variant< MultiEnergyDistributions,
                                              TabulatedEnergyDistributions >;

  private:

    /* fields */
    ReferenceFrame frame_;
    AngularDistributions angle_;
    EnergyDistributions energy_;

  public:

    /* constructor */

    #include "dryad/UncorrelatedDistributionData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the distribution data type
     */
    static constexpr DistributionDataType type() {

      return DistributionDataType::Uncorrelated;
    }

    /**
     *  @brief Return the reference frame
     */
    const ReferenceFrame& frame() const {

      return this->frame_;
    }

    /**
     *  @brief Set the reference frame
     *
     *  @param frame   the reference frame of the distribution data
     */
    void frame( ReferenceFrame frame ) {

      this->frame_ = std::move( frame );
    }

    /**
     *  @brief Return the angular distributions
     */
    const AngularDistributions& angle() const {

      return this->angle_;
    }

    /**
     *  @brief Return the angular distributions
     */
    AngularDistributions& angle() {

      return this->angle_;
    }

    /**
     *  @brief Set the angular distributions
     *
     *  @param angle   the angular distributions
     */
    void angle( AngularDistributions angle ) {

      this->angle_ = std::move( angle );
    }

    /**
     *  @brief Return the energy distributions
     */
    const EnergyDistributions& energy() const {

      return this->energy_;
    }

    /**
     *  @brief Return the energy distributions
     */
    EnergyDistributions& energy() {

      return this->energy_;
    }

    /**
     *  @brief Set the energy distributions
     *
     *  @param energy   the energy distributions
     */
    void energy( EnergyDistributions energy ) {

      this->energy_ = std::move( energy );
    }

    /**
     *  @brief Normalise the distribution data
     */
    void normalise() {

      std::visit( tools::overload{

                    [] ( IsotropicAngularDistributions& ) {},
                    [] ( auto&& data ) { data.normalise(); }
                  },
                  this->angle() );
      std::visit( tools::overload{

                    [] ( MultiEnergyDistributions& ) {},
                    [] ( auto&& data ) { data.normalise(); }
                  },
                  this->energy() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const UncorrelatedDistributionData& right ) const {

      return this->frame() == right.frame() && this->angle() == right.angle() &&
             this->energy() == right.energy();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const UncorrelatedDistributionData& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
