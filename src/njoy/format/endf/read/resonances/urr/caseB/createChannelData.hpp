#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CASEB_CREATECHANNELDATA
#define NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CASEB_CREATECHANNELDATA

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
#include "njoy/format/createVector.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace urr {
namespace caseB {

  /**
   *  @brief Create the channels and average parameter table for one (l,J)
   *         spin group of energy-dependent-fission-width unresolved resonance
   *         parameters (Case B)
   *
   *
   *  @param[in] projectile        the projectile identifier
   *  @param[in] target            the target identifier
   *  @param[in] incident          the incident particle pair
   *  @param[in] radii             the channel radii
   *  @param[in] numbers           the elastic channel's quantum numbers
   *  @param[in] lower             the lower energy limit of the range (eV)
   *  @param[in] upper             the upper energy limit of the range (eV)
   *  @param[in] jvalue            the parsed ENDF energy-dependent-fission-width j-value data
   *  @param[in] fissionEnergies   the shared fission width energy grid (eV)
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
      const ENDFtk::section::Type< 2, 151 >::UnresolvedEnergyDependentFissionWidths::JValue& jvalue,
      const std::vector< double >& fissionEnergies ) {

    // the elastic channel: same incident and outgoing particle pair, wave
    // functions are calculated using the channel radii. Its average width is
    // energy independent (flat over the resonance range).
    dryad::id::ChannelID elastic_id( dryad::id::ReactionID( projectile, target, 2 ), numbers );
    dryad::resonances::UnresolvedChannel elastic( elastic_id, incident, incident,
                                                  0., std::nullopt, radii, true );
    dryad::resonances::TabulatedAverageWidths elastic_widths(
        jvalue.AMUN(), { lower, upper }, { jvalue.GN(), jvalue.GN() } );

    unsigned int elastic_l = numbers.orbitalAngularMomentum();
    double level_J = numbers.totalAngularMomentum();
    short level_parity = ( elastic_l % 2 == 0 ) ? +1 : -1; // (-1)^l
    dryad::resonances::ChannelQuantumNumbers level_numbers( 0, 0, level_J, level_parity );
    dryad::resonances::ChannelRadii zero_radii( 0., 0. );

    // the capture channel: photon + residual outgoing pair, no wave function
    // calculation and zero channel radii. Its average width is energy independent.
    dryad::id::ChannelID capture_id( dryad::id::ReactionID( projectile, target, 102 ), level_numbers );
    dryad::resonances::ParticlePair capture_pair(
        { dryad::id::ParticleID::photon(), 0., 0., +1 },
        { capture_id.reaction().residual().value(), 0., 0., +1 } );
    dryad::resonances::UnresolvedChannel capture( capture_id, incident, capture_pair,
                                                  0., std::nullopt, 
                                                  zero_radii, false );
    dryad::resonances::TabulatedAverageWidths capture_widths(
        jvalue.AMUG(), { lower, upper }, { jvalue.GG(), jvalue.GG() } );

    
    dryad::id::ChannelID fission_id( dryad::id::ReactionID( projectile, target, 18 ), level_numbers );
    dryad::resonances::UnresolvedChannel fission( fission_id, 
                                                  incident, std::nullopt,
                                                  0., std::nullopt,
                                                  zero_radii, false );
    dryad::resonances::TabulatedAverageWidths fission_widths( jvalue.AMUF(), fissionEnergies, 
                                                              format::createVector( jvalue.GF() ) );

    dryad::resonances::TabulatedLevelSpacing spacing(
        std::vector< double >{ lower, upper },
        std::vector< double >{ jvalue.D(), jvalue.D() } );

    std::vector< dryad::id::ChannelID > ids = { elastic_id, capture_id, fission_id };
    std::vector< dryad::resonances::UnresolvedChannel > channels = { std::move( elastic ),
                                                                     std::move( capture ),
                                                                     std::move( fission ) };
    std::vector< dryad::resonances::TabulatedAverageWidths > widths = { std::move( elastic_widths ),
                                                                        std::move( capture_widths ),
                                                                        std::move( fission_widths ) };

    dryad::resonances::UnresolvedResonanceTable table( std::move( ids ), std::move( widths ),
                                                       std::move( spacing ) );

    return { std::move( channels ), std::move( table ) };
  }

} // caseB namespace
} // urr namespace
} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
