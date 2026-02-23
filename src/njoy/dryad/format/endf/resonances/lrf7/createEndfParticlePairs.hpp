#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFPPAIR
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFPPAIR

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/dryad/resonances/CompoundSystem.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/resonances/moveCaptureToFront.hpp"
// #include "njoy/dryad/format/endf/resonances/lrf7/createBoundaryCondition.hpp"
// #include "njoy/dryad/format/endf/resonances/lrf7/createChannelData.hpp"
#include "njoy/dryad/resonances/BoundaryCondition.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Format a dryad ResonanceChannels object to ENDFtk object
   *  The function takes a spin group (and not only ResonanceChannels) because AJ and PJ are needed. 
   *
   *  @param[in] group   the dryad spin group to format
   */
  inline ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs 
  createEndfParticlePairs( const dryad::resonances::CompoundSystem& compound ) {
    
    std::vector<double> ma, mb, za, zb, ia, ib, q, pa, pb;
    std::vector<int> pnt, shf, mt;

    // How many non-duplicate channels are there across all spin groups of this compound
    for(const auto& sgroup : compound.spinGroups()) {
      for (const auto& channel : sgroup.channels()) {

        if( !channel.reaction().mt().has_value() ) {
          Log::error( "Channel without MT value is not ENDF compatible" );
          throw std::exception(); 
        }
                
        // one mt only is associated to a pp
        if (std::find(mt.begin(), mt.end(), channel.reaction().mt().value()) == mt.end()) {
          
          const auto& outgoing_pp = channel.outgoingParticlePair();

          ma.push_back( !outgoing_pp.has_value() ? 0 : outgoing_pp.value().lightParticle().mass() / constants::neutron_mass );
          mb.push_back( !outgoing_pp.has_value() ? 0 : outgoing_pp.value().heavyParticle().mass() / constants::neutron_mass );
          za.push_back( !outgoing_pp.has_value() ? 0 : outgoing_pp.value().lightParticle().charge() );
          zb.push_back( !outgoing_pp.has_value() ? 0 : outgoing_pp.value().heavyParticle().charge() );
          ia.push_back( !outgoing_pp.has_value() ? 0 : outgoing_pp.value().lightParticle().spin() );
          ib.push_back( !outgoing_pp.has_value() ? 0 : outgoing_pp.value().heavyParticle().spin() );
          q.push_back( channel.qValue() );
          
          // if fission (no outgoing) or capture (photon in outgoing pp), then PNT=-1
          int compute_penetrability = !outgoing_pp.has_value()
                                      ? -1
                                      : outgoing_pp.value().lightParticle().identifier() == id::ParticleID::photon()
                                        ? -1
                                        : 1;
          
          pnt.push_back(compute_penetrability);

          // Shift factor can always be computed (SHF=1), except when the boundary condition cancels it out (SHF=0)
          shf.push_back( sgroup.boundaryCondition() != njoy::dryad::resonances::BoundaryCondition::ShiftFactor );
          
          mt.push_back( channel.reaction().mt().value() );
          pa.push_back( !outgoing_pp.has_value() ? 0 : outgoing_pp.value().lightParticle().parity());
          pb.push_back( !outgoing_pp.has_value() ? 0 : outgoing_pp.value().heavyParticle().parity());
        }
      }
    }

  return ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs( std::move( ma ), std::move( mb ),
                                                                          std::move( za ), std::move( zb ),
                                                                          std::move( ia ), std::move( ib ),
                                                                          std::move( pa ), std::move( pb ),
                                                                          std::move( q ), std::move( pnt ),
                                                                          std::move( shf ), std::move( mt ) );
  }


} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
