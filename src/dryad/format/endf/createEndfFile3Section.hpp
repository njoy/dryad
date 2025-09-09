#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEENDFFILE3SECTION
#define NJOY_DRYAD_FORMAT_ENDF_CREATEENDFFILE3SECTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/Reaction.hpp"
#include "dryad/format/endf/createEndfInterpolants.hpp"
#include "dryad/format/endf/createEndfBoundaries.hpp"
#include "ENDFtk/section/3.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create an ENDF MF3 section object from a Reaction object
   *
   *  @param[in] reaction   the reaction data
   */
  ENDFtk::section::Type< 3 >
  createEndfFile3Section( double awr,
                          const dryad::Reaction& reaction ) {

    auto projectile = reaction.identifier().projectile();
    auto target = reaction.identifier().target();

    auto adjust_scatter_level = [&projectile, &target] ( int mt ) {

      int elastic = id::ReactionID( projectile, target, 2 ).reactionType().mt().value();
      if ( target.e() > 0 && projectile != id::ParticleID::photon() ) {

        int ground = id::ReactionID( projectile, id::ParticleID( target.za() ), 2 ).reactionType().mt().value();
        if ( mt >= ground && mt < elastic ) {

          return mt + 1;
        }
      }

      if ( mt == elastic ) {

        mt = 2;
      }

      return mt;
    };

    int mt = adjust_scatter_level( reaction.identifier().reactionType().mt().value() );
    double qm = reaction.massDifferenceQValue().has_value()
                ? reaction.massDifferenceQValue().value()
                : 0;
    double qi = reaction.reactionQValue().has_value()
                ? reaction.reactionQValue().value()
                : 0;
    long lr = 0;
    std::vector< long > boundaries = createEndfBoundaries( reaction.crossSection().boundaries() );
    std::vector< long > interpolants = createEndfInterpolants( reaction.crossSection().interpolants() );
    std::vector< double > energies = reaction.crossSection().energies();
    std::vector< double > xs = reaction.crossSection().values();

    //! @todo clean up jumps in the boundaries?

    return ENDFtk::section::Type< 3 >( mt, target.za(), awr, qm, qi, lr,
                                      std::move( boundaries ),
                                      std::move( interpolants ),
                                      std::move( energies ),
                                      std::move( xs ) );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
