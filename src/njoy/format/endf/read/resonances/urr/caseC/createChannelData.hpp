#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CASEC_CREATECHANNELDATA
#define NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CASEC_CREATECHANNELDATA

// system includes
#include <algorithm>
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
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace urr {
namespace caseC {

  /**
   *  @brief Create the channels and average parameter table for one (l,J)
   *         spin group of fully energy-dependent unresolved resonance
   *         parameters (Case C)
   *
   *  Case C always defines an elastic and a capture channel, and additionally
   *  a fission channel (MT 18) and/or a competitive channel (MT 5) when their
   *  average widths are genuinely nonzero. Every average parameter is tabulated
   *  against a single shared energy grid with one interpolation law.
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] incident     the incident particle pair
   *  @param[in] radii        the channel radii
   *  @param[in] numbers      the elastic channel's quantum numbers
   *  @param[in] jvalue       the parsed ENDF fully energy-dependent j-value data
   */
  inline std::pair< std::vector< dryad::resonances::UnresolvedChannel >,
                    dryad::resonances::UnresolvedResonanceTable >
  createChannelData(
      const dryad::id::ParticleID& projectile,
      const dryad::id::ParticleID& target,
      const dryad::resonances::ParticlePair& incident,
      const dryad::resonances::ChannelRadii& radii,
      const dryad::resonances::ChannelQuantumNumbers& numbers,
      const ENDFtk::section::Type< 2, 151 >::UnresolvedEnergyDependent::JValue& jvalue ) {

    // the energy grid and interpolation law shared by every tabulated quantity
    auto energies = format::createVector( jvalue.energies() );
    auto interpolant = read::createInterpolants( jvalue.interpolants() ).front();

    // the elastic channel: same incident and outgoing particle pair, wave
    // functions are calculated using the channel radii
    dryad::id::ChannelID elastic_id( dryad::id::ReactionID( projectile, target, 2 ), numbers );
    dryad::resonances::UnresolvedChannel elastic( elastic_id, incident, incident,
                                                  0., std::nullopt, radii, true );
    dryad::resonances::TabulatedAverageWidths elastic_widths(
        jvalue.AMUN(), energies, format::createVector( jvalue.GN() ), interpolant );

    // the non-elastic channels all share the resonance level's total angular
    // momentum J and parity. The parity of the level is (-1)^l, where l is the
    // elastic channel's orbital angular momentum.
    unsigned int elastic_l = numbers.orbitalAngularMomentum();
    double level_J = numbers.totalAngularMomentum();
    short level_parity = ( elastic_l % 2 == 0 ) ? +1 : -1; // (-1)^l
    dryad::resonances::ChannelQuantumNumbers level_numbers( 0, 0, level_J, level_parity );
    dryad::resonances::ChannelRadii zero_radii( 0., 0. );

    // the capture channel: photon + residual outgoing pair, no wave function
    // calculation and zero channel radii
    dryad::id::ChannelID capture_id( dryad::id::ReactionID( projectile, target, 102 ), level_numbers );
    dryad::resonances::ParticlePair capture_pair(
        { dryad::id::ParticleID::photon(), 0., 0., +1 },
        { capture_id.reaction().residual().value(), 0., 0., +1 } );
    dryad::resonances::UnresolvedChannel capture( capture_id, incident, capture_pair,
                                                  0., std::nullopt, zero_radii, false );
    dryad::resonances::TabulatedAverageWidths capture_widths(
        jvalue.AMUG(), energies, format::createVector( jvalue.GG() ), interpolant );

    // elastic and capture are always present
    std::vector< dryad::id::ChannelID > ids = { elastic_id, capture_id };
    std::vector< dryad::resonances::UnresolvedChannel > channels = { std::move( elastic ),
                                                                     std::move( capture ) };
    std::vector< dryad::resonances::TabulatedAverageWidths > widths = { std::move( elastic_widths ),
                                                                        std::move( capture_widths ) };

    auto is_nonzero = [] ( double value ) { return value != 0.; };

    // the fission channel (MT 18): no defined outgoing pair, added only when
    // the fission width is genuinely nonzero
    auto fission_widths = format::createVector( jvalue.GF() );
    if ( std::any_of( fission_widths.begin(), fission_widths.end(), is_nonzero ) ) {

      dryad::id::ChannelID fission_id( dryad::id::ReactionID( projectile, target, 18 ), level_numbers );
      dryad::resonances::UnresolvedChannel fission( fission_id, incident, std::nullopt,
                                                    0., std::nullopt, zero_radii, false );
      ids.push_back( fission_id );
      channels.push_back( std::move( fission ) );
      widths.emplace_back( jvalue.AMUF(), energies, std::move( fission_widths ), interpolant );
    }

    // the competitive channel (newly defined reaction type "competitive"): 
    // no defined outgoing pair, added only when the competitive width is genuinely nonzero
    auto competitive_widths = format::createVector( jvalue.GX() );
    if ( std::any_of( competitive_widths.begin(), competitive_widths.end(), is_nonzero ) ) {

      dryad::id::ChannelID competitive_id( dryad::id::ReactionID( projectile, target, "competitive" ), level_numbers );
      dryad::resonances::UnresolvedChannel competitive( competitive_id, incident, std::nullopt,
                                                        0., std::nullopt, zero_radii, false );
      ids.push_back( competitive_id );
      channels.push_back( std::move( competitive ) );
      widths.emplace_back( jvalue.AMUX(), energies, std::move( competitive_widths ), interpolant );
    }

    // the level spacing, shared by every channel in this spin group
    dryad::resonances::TabulatedLevelSpacing spacing(
        energies, format::createVector( jvalue.D() ), interpolant );

    dryad::resonances::UnresolvedResonanceTable table( std::move( ids ), std::move( widths ),
                                                       std::move( spacing ) );

    return { std::move( channels ), std::move( table ) };
  }

} // caseC namespace
} // urr namespace
} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
