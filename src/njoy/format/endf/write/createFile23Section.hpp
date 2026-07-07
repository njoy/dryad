#ifndef NJOY_FORMAT_ENDF_WRITE_CREATEFILE23SECTION
#define NJOY_FORMAT_ENDF_WRITE_CREATEFILE23SECTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/format/endf/write/createInterpolants.hpp"
#include "njoy/format/endf/write/createBoundaries.hpp"
#include "ENDFtk/section/23.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {

  /**
   *  @brief Create an ENDF MF23 section object from a Reaction object
   *
   *  @param[in] awr        the atomic weight ratio
   *  @param[in] reaction   the reaction data
   */
  inline ENDFtk::section::Type< 23 >
  createFile23Section( double awr,
                       const dryad::Reaction& reaction ) {

    auto target = reaction.identifier().target();

    int mt = reaction.identifier().reactionType().mt().value();
    double bindingenergy = reaction.reactionQValue().has_value()
                           ? -reaction.reactionQValue().value()
                           : 0;
    std::vector< long > boundaries = createBoundaries( reaction.crossSection().boundaries() );
    std::vector< long > interpolants = createInterpolants( reaction.crossSection().interpolants() );
    std::vector< double > energies = reaction.crossSection().energies();
    std::vector< double > xs = reaction.crossSection().values();

    //! @todo clean up jumps in the boundaries?

    return ENDFtk::section::Type< 23 >( mt, target.za(), awr, bindingenergy, 0.,
                                        std::move( boundaries ),
                                        std::move( interpolants ),
                                        std::move( energies ),
                                        std::move( xs ) );
  }

} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
