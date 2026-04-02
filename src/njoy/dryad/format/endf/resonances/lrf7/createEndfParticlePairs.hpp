#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFPPAIR
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFPPAIR

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/CompoundSystem.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the particle pair informatin for LRF7 resonance parameters
   *
   *  @param[in] compound   the compound system
   */
  inline ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs
  createEndfParticlePairs( const dryad::resonances::CompoundSystem& compound ) {

    std::vector< double > ma, mb, za, zb, ia, ib, q, pa, pb;
    std::vector< int > pnt, shf, mt;

    auto incident = compound.spinGroups().front().channels().front().incidentParticlePair().lightParticle().identifier();

    for( const auto& group : compound.spinGroups() ) {

      for ( const auto& channel : group.channels() ) {

        if ( ! channel.reaction().mt().has_value() ) {

          Log::error( "Found a channel without an MT number, this is not ENDF compatible" );
          throw std::exception();
        }

        int mt_number = channel.reaction().reactionType() == id::ReactionType::elastic( incident )
                          ? 2
                          : channel.reaction().mt().value();

        // add the particle pair only if we do not have the mt number yet
        if ( std::find( mt.begin(), mt.end(), mt_number ) == mt.end() ) {

          decltype(auto) outgoing = channel.outgoingParticlePair();

          mt.push_back( mt_number );

          ma.push_back( outgoing.has_value() ? outgoing.value().lightParticle().mass() : 0. );
          mb.push_back( outgoing.has_value() ? outgoing.value().heavyParticle().mass() : 0. );
          za.push_back( outgoing.has_value() ? outgoing.value().lightParticle().charge() : 0. );
          zb.push_back( outgoing.has_value() ? outgoing.value().heavyParticle().charge() : 0. );
          ia.push_back( outgoing.has_value() ? outgoing.value().lightParticle().spin() *
                                               outgoing.value().lightParticle().parity()
                                             : 0. );
          ib.push_back( outgoing.has_value() ? outgoing.value().heavyParticle().spin() *
                                               outgoing.value().heavyParticle().parity()
                                             : 0. );
          q.push_back( channel.qValue() );
          pa.push_back( outgoing.has_value() ? ia.back() == 0. ? outgoing.value().lightParticle().parity() : 0. : 0. );
          pb.push_back( outgoing.has_value() ? ib.back() == 0. ? outgoing.value().heavyParticle().parity() : 0. : 0. );

          // if fission (no outgoing) or capture (photon in outgoing pp), then PNT=-1
          pnt.push_back( outgoing.has_value()
                           ? outgoing.value().lightParticle().identifier() == id::ParticleID::photon()
                               ? -1
                               : +1
                           : -1 );

          // when the boundary condition elminates shift, set the SHF flag to 0
          shf.push_back( group.boundaryCondition() != dryad::resonances::BoundaryCondition::ShiftFactor );
        }
      }
    }

    // transform mass values from amu to neutron mass units
    auto convert_mass = [&] ( auto&& value ) { return value / constants::neutron_mass; };
    std::transform( ma.begin(), ma.end(), ma.begin(), convert_mass );
    std::transform( mb.begin(), mb.end(), mb.begin(), convert_mass );

    using ParticlePairs = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs;
    return ParticlePairs( std::move( ma ), std::move( mb ), std::move( za ), std::move( zb ),
                          std::move( ia ), std::move( ib ), std::move( pa ), std::move( pb ),
                          std::move( q ), std::move( pnt ), std::move( shf ), std::move( mt ) );
  }


} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
