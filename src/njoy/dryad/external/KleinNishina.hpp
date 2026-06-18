#ifndef NJOY_DRYAD_EXTERNAL_KLEINNISHINA
#define NJOY_DRYAD_EXTERNAL_KLEINNISHINA

// system includes

// other includes
#include "njoy/constants.hpp"

namespace njoy {
namespace dryad {
namespace external {

  /**
   *  @class
   *  @brief The Klein-Nishina cross section formula
   */
  class KleinNishina {

    /* fields */

    /* auxiliary functions */

  public:

    /* methods */

    /**
     *  @brief Return the cosine value for a given incident and outgoing energy
     *
     *  Since kprime = k / ( 1 + k ( 1 - mu ) ) then mu = 1 - 1 / kprime + 1 / k
     *
     *  @param[in] incident_energy   the incident energy (given in eV)
     *  @param[in] outgoing_energy   the outgoing energy (given in eV)
     */
    static double cosine( double incident_energy, double outgoing_energy ) {

      double k = incident_energy / constants::electron_rest_mass;
      double kprime = outgoing_energy / constants::electron_rest_mass;

      return 1. + 1. / k - 1. / kprime;
    }

    /**
     *  @brief Return the outgoing energy value for a given incident energy and cosine
     *
     *  kprime = k / ( 1 + k ( 1 - mu ) )
     *
     *  @param[in] incident_energy   the incident energy (given in eV)
     *  @param[in] cosine            the outgoing cosine
     */
    static double outgoingEnergy( double incident_energy, double cosine ) {

      double k = incident_energy / constants::electron_rest_mass;

      return k / ( 1. + k * ( 1. - cosine ) ) * constants::electron_rest_mass;
    }

    /**
     *  @brief Return the lower limit of the outgoing energy value for a given incident energy
     *
     *  @param[in] incident_energy   the incident energy (given in eV)
     */
    static double lowerOutgoingEnergyLimit( double incident_energy ) {

      // this corresponds to the outgoing energy with cosine = -1

      return outgoingEnergy( incident_energy, -1 );
    }

    /**
     *  @brief Return the upper limit of the outgoing energy value for a given incident energy
     *
     *  @param[in] incident_energy   the incident energy (given in eV)
     */
    static double upperOutgoingEnergyLimit( double incident_energy ) {

      // this corresponds to the outgoing energy with cosine = +1

      return incident_energy;
    }

    /**
     *  @brief Return the differential cross section value with respect to cosine
     *         for a given incident energy, outgoing energy and cosine value
     *
     *  @param[in] incident_energy   the incident energy (given in eV)
     *  @param[in] outgoing_energy   the outgoing energy (given in eV)
     *  @param[in] cosine            the outgoing cosine
     */
    static double differentialCrossSectionToCosine( double incident_energy, double outgoing_energy, double cosine ) {

      constexpr double constant = constants::pi * constants::electron_radius * constants::electron_radius *
                                  constants::m2_to_barn ;

      double k = incident_energy / constants::electron_rest_mass;
      double kprime = outgoing_energy / constants::electron_rest_mass;

      return constant * kprime * kprime / k / k * ( 1. + cosine * cosine + k * kprime * ( 1. - cosine ) * ( 1. - cosine ) );
    }

    /**
     *  @brief Return the differential cross section value with respect to outgoing energy
     *         for a given incident energy, outgoing energy and cosine value
     *
     *  @param[in] incident_energy   the incident energy (given in eV)
     *  @param[in] outgoing_energy   the outgoing energy (given in eV)
     *  @param[in] cosine            the outgoing cosine
     */
    static double differentialCrossSectionToOutgoingEnergy( double incident_energy, double outgoing_energy, double cosine ) {

      constexpr double constant = constants::pi * constants::electron_radius * constants::electron_radius *
                                  constants::m2_to_barn ;

      double k = incident_energy / constants::electron_rest_mass;
      double kprime = outgoing_energy / constants::electron_rest_mass;

      return constant * ( 1. + cosine * cosine + k * kprime * ( 1. - cosine ) * ( 1. - cosine ) );
    }
  };

} // external namespace
} // dryad namespace
} // njoy namespace

#endif
