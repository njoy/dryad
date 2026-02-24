#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFRESONCHANNELS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFRESONCHANNELS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/resonances/moveCaptureToFront.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createBoundaryCondition.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createChannelData.hpp"
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
  inline auto createEndfResonanceChannels( const dryad::resonances::SpinGroup& group, ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs& ppairs ) {
    
    //! @todo parity is duplicated (both in AJ and Pi)
    double parity = group.parity();
    double aj = group.totalAngularMomentum() * parity;

    int nchannels = group.channels().size();
    
    std::vector< unsigned int > ppi(nchannels);
    std::vector< unsigned int > l(nchannels);
    std::vector< double > s(nchannels);
    std::vector< double > b(nchannels);
    std::vector< double > ape(nchannels);
    std::vector< double > apt(nchannels);
    int kbk = 0;
    int kps = 0;

    auto get_radius= tools::overload{

      [] ( double radius ) { return radius; },
      [] ( const auto& ) -> double {
        Log::error( "Tabulated Radii not compatible" );
        throw std::exception(); 
      }
    };

    for (size_t i = 0; i < group.channels().size(); i++) {

      auto& channel = group.channels()[i];

      // By construction, the MT number of this channel must already be in ppairs.MT(), ppi is its index in this vector
      ppi[i] = std::distance(ppairs.MT().begin(), std::find(ppairs.MT().begin(), ppairs.MT().end(), channel.reaction().mt())) + 1; // make a one-based index
      l[i]   = channel.quantumNumbers().orbitalAngularMomentum();
      s[i]   = channel.quantumNumbers().spin();
      b[i]   = channel.boundaryCondition().value_or(0.0);
      // The effect radius can be either a double or a list
      ape[i] = std::visit(get_radius, channel.channelRadii().penetrabilityRadius());
      // The true radius is optionnal, and can be either a double or a list
      apt[i] = std::visit( get_radius, channel.channelRadii().phaseShiftRadius().value_or(0.0));
      
      if ( channel.background().has_value() ) {
        kbk++;
      }

    }

    return ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ResonanceChannels( aj, parity, 
                                                                               std::move( ppi ), std::move( l ),
                                                                               std::move( s ), std::move( b ),
                                                                               std::move( apt ), std::move( ape ),
                                                                               kbk, kps );
  }


} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
