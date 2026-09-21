#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CASEA_CREATECHANNELDATA
#define NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CASEA_CREATECHANNELDATA

// system includes
#include <optional>
#include <utility>
#include <vector>

// other includes
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/id/ChannelID.hpp"
#include "njoy/dryad/resonances/UnresolvedChannel.hpp"
#include "njoy/dryad/resonances/UnresolvedResonanceTable.hpp"
#include "njoy/dryad/resonances/TabulatedAverageWidths.hpp"
#include "njoy/dryad/resonances/TabulatedLevelSpacing.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace urr {
namespace caseA {

  /**
   *  @brief Create the channels and average parameter table for one (l,J)
   *         spin group of energy-independent unresolved resonance parameters
   *         (Case A)
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] incident     the incident particle pair
   *  @param[in] radii        the channel radii
   *  @param[in] numbers      the elastic channel's quantum numbers
   *  @param[in] lower        the lower energy limit of the range (eV)
   *  @param[in] upper        the upper energy limit of the range (eV)
   *  @param[in] amun         the neutron width degrees of freedom (ENDF AMUN)
   *  @param[in] gn           the average neutron width in eV (ENDF GN)
   *  @param[in] gg           the average gamma width in eV (ENDF GG)
   *  @param[in] d            the average level spacing in eV (ENDF D)
   */
  inline std::pair< std::vector< dryad::resonances::UnresolvedChannel >,
                    dryad::resonances::UnresolvedResonanceTable >
  createChannelData(
      const dryad::id::ParticleID& projectile,
      const dryad::id::ParticleID& target,
      const dryad::resonances::ParticlePair& incident,
      const dryad::resonances::ChannelRadii& radii,
      const dryad::resonances::ChannelQuantumNumbers& numbers,
      double lower, double upper,
      int amun, double gn, double gg, double d ) {


    dryad::id::ChannelID elastic_id( dryad::id::ReactionID( projectile, target, 2 ), numbers );
    dryad::resonances::UnresolvedChannel elastic( elastic_id, incident, incident,
                                                  0., std::nullopt, radii, 
                                                  true );
    dryad::resonances::TabulatedAverageWidths elastic_widths( amun, 
                                                              { lower, upper }, 
                                                              { gn, gn } );

    unsigned int elastic_l = numbers.orbitalAngularMomentum();
    double level_J = numbers.totalAngularMomentum();
    short level_parity = ( elastic_l % 2 == 0 ) ? +1 : -1; // (-1)^l
    dryad::resonances::ChannelQuantumNumbers capture_numbers( 0, 0, level_J, level_parity );
    dryad::id::ChannelID capture_id( dryad::id::ReactionID( projectile, target, 102 ), capture_numbers );
    dryad::resonances::ParticlePair capture_pair(
        { dryad::id::ParticleID::photon(), 0., 0., +1 },
        { capture_id.reaction().residual().value(), 0., 0., +1 } );
    dryad::resonances::ChannelRadii zero_radii( 0., 0. );
    dryad::resonances::UnresolvedChannel capture( capture_id, incident, capture_pair,
                                                  0., std::nullopt,
                                                  zero_radii, false );
    dryad::resonances::TabulatedAverageWidths capture_widths( 0, { lower, upper }, { gg, gg } );

    dryad::resonances::TabulatedLevelSpacing spacing(
        std::vector< double >{ lower, upper },
        std::vector< double >{ d, d } );

    std::vector< dryad::id::ChannelID > ids = { elastic_id, capture_id };
    std::vector< dryad::resonances::UnresolvedChannel > channels = { std::move( elastic ),
                                                                     std::move( capture ) };
    std::vector< dryad::resonances::TabulatedAverageWidths > widths = { std::move( elastic_widths ),
                                                                        std::move( capture_widths ) };

    dryad::resonances::UnresolvedResonanceTable table( std::move( ids ), std::move( widths ),
                                                       std::move( spacing ) );

    return { std::move( channels ), std::move( table ) };
  }

} // caseA namespace
} // urr namespace
} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
